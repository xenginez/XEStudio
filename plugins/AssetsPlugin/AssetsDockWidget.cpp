#include "AssetsDockWidget.h"
#include "ui_AssetsDockWidget.h"


AssetsDockWidget::AssetsDockWidget( QWidget * parent /*= nullptr*/, Qt::WindowFlags flags /*= Qt::WindowFlags() */ )
	: XESDockWidget( "assets", parent, flags )
	, ui( new Ui::AssetsDockWidget )
{
	auto widget = new QWidget( this );
	setWidget( widget );
	ui->setupUi( widget );
	
	setAllowedAreas( Qt::DockWidgetArea::BottomDockWidgetArea );

	setFeatures( QDockWidget::DockWidgetFeature::DockWidgetClosable );

	ui->splitter->setStretchFactor( 0, 1 );
	ui->splitter->setStretchFactor( 1, 4 );

	Init();
}

AssetsDockWidget::~AssetsDockWidget()
{
	delete ui;
}

void AssetsDockWidget::Init()
{
	_EditTreeItem = nullptr;
	_EditListItem = nullptr;

	// init treeWidgetFolder
	auto path = XE::XESFramework::GetCurrentFramework()->GetAssetsPath();
	_CurrentPath = path.u8string().c_str();

	auto item = new QTreeWidgetItem();
	auto font = item->font( 0 );
	font.setBold( true );
	font.setPointSize( 14 );
	item->setFont( 0, font );
	item->setText( 0, "assets" );
	item->setIcon( 0, QIcon( ":/icons/folder.png" ) );
	item->setData( 0, Qt::UserRole + 1, path.u8string().c_str() );

	ui->treeWidgetFolder->addTopLevelItem( item );

	AddTreeWidgetFolder( _CurrentPath, item );

	ui->treeWidgetFolder->setItemSelected( item, true );

	connect( ui->treeWidgetFolder, &QTreeWidget::itemChanged, this, &AssetsDockWidget::OnTreeWidgetFolderItemChanged );
	connect( ui->treeWidgetFolder, &QTreeWidget::itemClicked, this, &AssetsDockWidget::OnTreeWidgetFolderItemClicked );

	ui->treeWidgetFolder->installEventFilter( this );

	// init listWidgetItem
	ResetListWidgetItem( _CurrentPath );

	connect( ui->listWidgetItem, &QListWidget::itemDoubleClicked, this, &AssetsDockWidget::OnListWidgetItemItemDoubleClicked );
	ui->listWidgetItem->installEventFilter( this );

	// init comboBoxFilter
	connect( ui->listWidgetItem, &QListWidget::itemChanged, this, &AssetsDockWidget::OnListWidgetItemItemChanged );
	connect( ui->comboBoxFilter, &QComboBox::currentTextChanged, this, &AssetsDockWidget::OnComboBoxFilterCurrentTextChanged );

	// init AssetImporter
	XE::AssetImporter::GetMetaClassStatic()->VisitDerivedClass( [this]( const XE::IMetaClassPtr & cls )
																{
																	if( !cls->IsAbstract() )
																	{
																		auto importer = cls->ConstructPtr().Value< std::shared_ptr< XE::AssetImporter > >();
																		auto support = importer->GetSupport();
																		support.replace( " ", "" );
																		support = support.toLower();

																		auto list = support.split( "," );
																		for( const auto & str : list )
																		{
																			_Supports.insert( str, importer );
																		}

																		_SuffixIcon.insert( importer->GetSuffix(), importer->GetIcon() );
																	}
																} );
}

bool AssetsDockWidget::eventFilter( QObject * obj, QEvent * event )
{
	if( obj == ui->treeWidgetFolder && event->type() == QEvent::Type::ContextMenu )
	{
		OnTreeWidgetFolderContextMenuEvent( (QContextMenuEvent * )event );
		return true;
	}
	else if( obj == ui->listWidgetItem && event->type() == QEvent::Type::ContextMenu )
	{
		OnListWidgetItemContextMenuEvent( (QContextMenuEvent * )event );
		return true;
	}

	return XESDockWidget::eventFilter( obj, event );
}

void AssetsDockWidget::OnComboBoxFilterCurrentTextChanged( const QString & text )
{
	auto item = ui->treeWidgetFolder->currentItem();
	if( item != nullptr )
	{
		ResetListWidgetItem( item->data( 0, Qt::UserRole + 1 ).toString() );
	}
}

void AssetsDockWidget::OnTreeWidgetFolderContextMenuEvent( QContextMenuEvent * event )
{
	auto item = ui->treeWidgetFolder->itemAt( event->pos() );

	auto menu = new QMenu();
	if( item != nullptr )
	{
		auto create_action = menu->addAction( tr( "create folder" ) );
		connect( create_action, &QAction::triggered, [item]()
				 {
					 auto path = std::filesystem::u8path( item->data( 0, Qt::UserRole + 1 ).toString().toUtf8().toStdString() ) / "new folder";
					 if( std::filesystem::create_directory( path ) )
					 {
						 auto sub = new QTreeWidgetItem( item );

						 auto font = sub->font( 0 );
						 font.setPointSize( 12 );
						 sub->setFont( 0, font );
						 sub->setText( 0, tr( "new folder" ) );
						 item->setToolTip( 0, tr( "new folder" ) );
						 sub->setIcon( 0, QIcon( ":/icons/folder.png" ) );
						 sub->setFlags( item->flags() | Qt::ItemFlag::ItemIsEditable );

						 sub->setData( 0, Qt::UserRole + 1, path.u8string().c_str() );
					 }
				 } );
		auto delete_action = menu->addAction( tr( "delete folder" ) );
		connect( delete_action, &QAction::triggered, [item]()
				 {
					 auto path = std::filesystem::u8path( item->data( 0, Qt::UserRole + 1 ).toString().toUtf8().toStdString() );
					 if( std::filesystem::remove( path ) )
					 {
						 item->parent()->removeChild( item );
					 }
				 } );
		auto rename_action = menu->addAction( tr( "rename folder" ) );
		connect( rename_action, &QAction::triggered, [this, item]()
				 {
					 _EditTreeItem = item;
					 ui->treeWidgetFolder->editItem( item, 0 );
				 } );
		auto export_action = menu->addAction( tr( "export folder" ) );
		connect( export_action, &QAction::triggered, [item]()
				 {
					 QString dir = QFileDialog::getExistingDirectory( nullptr, tr( "export to directory" ),
																	  "/home",
																	  QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks );
					 if( !dir.isEmpty() )
					 {
						 auto from_path = std::filesystem::u8path( item->data( 0, Qt::UserRole + 1 ).toString().toUtf8().toStdString() );
						 auto to_path = std::filesystem::u8path( dir.toUtf8().toStdString() ) / from_path.stem();

						 std::filesystem::copy( from_path, to_path, std::filesystem::copy_options::recursive );
					 }
				 } );
	}
	else
	{
		auto collapse_action = menu->addAction( tr( "collapse all" ) );
		connect( collapse_action, &QAction::triggered, [this]()
				 {
					 ui->treeWidgetFolder->collapseAll();
				 } );
		auto expand_action = menu->addAction( tr( "expand all" ) );
		connect( expand_action, &QAction::triggered, [this]()
				 {
					 ui->treeWidgetFolder->expandAll();
				 } );
	}
	menu->exec( QCursor::pos() );
}

void AssetsDockWidget::OnListWidgetItemContextMenuEvent( QContextMenuEvent * event )
{
	auto item = ui->listWidgetItem->itemAt( event->pos() );

	auto menu = new QMenu();
	if( item != nullptr )
	{
		auto delete_action = menu->addAction( tr( "delete asset" ) );
		connect( delete_action, &QAction::triggered, [this, item]()
				 {
					 auto path = std::filesystem::u8path( item->data( Qt::UserRole + 1 ).toString().toUtf8().toStdString() );
					 if( QMessageBox::information( nullptr, tr( "delete asset" ),
												   tr( "are you sure to delete the \'" ) + path.u8string().c_str() + tr( "\' resource?" ),
												   QMessageBox::StandardButton::Yes, QMessageBox::StandardButton::No ) == QMessageBox::StandardButton::Yes )
					 {
						 if( std::filesystem::remove( path ) )
						 {
							 ResetListWidgetItem( path.parent_path().u8string().c_str() );
						 }
					 }
				 } );
		auto rename_action = menu->addAction( tr( "rename asset" ) );
		connect( rename_action, &QAction::triggered, [this, item]()
				 {
					 _EditListItem = item;
					 ui->listWidgetItem->editItem( item );
				 } );
		auto editor_action = menu->addAction( tr( "editor asset" ) );
		connect( rename_action, &QAction::triggered, [this, item]()
				 {
					 OnListWidgetItemItemDoubleClicked( item );
				 } );
		auto export_action = menu->addAction( tr( "export asset" ) );
		connect( export_action, &QAction::triggered, [item]()
				 {
					 QString dir = QFileDialog::getExistingDirectory( nullptr, tr( "export to directory" ),
																	  "/home",
																	  QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks );
					 if( !dir.isEmpty() )
					 {
						 auto from_path = std::filesystem::u8path( item->data( Qt::UserRole + 1 ).toString().toUtf8().toStdString() );
						 auto to_path = std::filesystem::u8path( dir.toUtf8().toStdString() ) / from_path.filename();

						 std::filesystem::copy( from_path, to_path );
					 }
				 } );
	}
	else
	{
		auto update_action = menu->addAction( tr( "update" ) );
		connect( update_action, &QAction::triggered, [this]()
				 {
					 ResetListWidgetItem( _CurrentPath );
				 } );
		auto import_action = menu->addAction( tr( "import asset" ) );
		connect( import_action, &QAction::triggered, [this]()
				 {
					 QString fileName = QFileDialog::getOpenFileName( this, tr( "Open File" ), "/home", tr( "Asset (*.*)" ) );
					 if( !fileName.isEmpty() )
					 {
						 ImportAsset( fileName );
					 }
				 } );
		menu->addSeparator();
		auto create_menu = menu->addMenu( tr( "create asset" ) );
	}
	menu->exec( QCursor::pos() );
}

void AssetsDockWidget::OnTreeWidgetFolderItemChanged( QTreeWidgetItem * item, int column )
{
	if( item != nullptr && item == _EditTreeItem )
	{
		_EditTreeItem = nullptr;

		item->setToolTip( column, item->text( column ) );

		auto old_path = std::filesystem::u8path( item->data( 0, Qt::UserRole + 1 ).toString().toUtf8().toStdString() );
		auto new_path = old_path.parent_path() / std::filesystem::u8path( item->text( column ).toUtf8().toStdString() );
		if( old_path != new_path )
		{
			std::filesystem::rename( old_path, new_path );
			item->setData( column, Qt::UserRole + 1, new_path.u8string().c_str() );
		}
	}
}

void AssetsDockWidget::OnListWidgetItemItemChanged( QListWidgetItem * item )
{
	if( item != nullptr && item == _EditListItem )
	{
		_EditListItem = nullptr;

		auto old_path = std::filesystem::u8path( item->data( Qt::UserRole + 1 ).toString().toUtf8().toStdString() );
		auto new_path = old_path.parent_path() / std::filesystem::u8path( item->text().toUtf8().toStdString() + old_path.extension().u8string() );
		if( old_path != new_path )
		{
			item->setToolTip( item->text() + old_path.extension().u8string().c_str() );

			std::filesystem::rename( old_path, new_path );
			item->setData( Qt::UserRole + 1, new_path.u8string().c_str() );
		}
	}
}

void AssetsDockWidget::OnTreeWidgetFolderItemClicked( QTreeWidgetItem * item, int column )
{
	_CurrentPath = item->data( column, Qt::UserRole + 1 ).toString();
	ResetListWidgetItem( _CurrentPath );
}

void AssetsDockWidget::OnListWidgetItemItemDoubleClicked( QListWidgetItem * item )
{
	auto path = item->data( Qt::UserRole + 1 ).toString();
	;
	auto event = XE::MakeShared<XE::Event>(
		XE::OPEN_ASSET_UNKNOWN,
		nullptr,
		nullptr,
		":" + std::filesystem::relative( path.toStdString(), XE::XESFramework::GetCurrentFramework()->GetAssetsPath() ).u8string() );

	QFileInfo info( path );

	if( info.suffix() == "ai" )
	{
		event->handle = XE::OPEN_ASSET_AI;
	}
	else if( info.suffix() == "anim" )
	{
		event->handle = XE::OPEN_ASSET_ANIM;
	}
	else if( info.suffix() == "mesh" )
	{
		event->handle = XE::OPEN_ASSET_MESH;
	}
	else if( info.suffix() == "world" )
	{
		event->handle = XE::OPEN_ASSET_WORLD;
	}
	else if( info.suffix() == "sound" )
	{
		event->handle = XE::OPEN_ASSET_SOUND;
	}
	else if( info.suffix() == "texture" )
	{
		event->handle = XE::OPEN_ASSET_TEXTURE;
	}
	else if( info.suffix() == "shader" )
	{
		event->handle = XE::OPEN_ASSET_SHADER;
	}
	else if( info.suffix() == "prefab" )
	{
		event->handle = XE::OPEN_ASSET_PREFAB;
	}
	else if( info.suffix() == "skeleton" )
	{
		event->handle = XE::OPEN_ASSET_SKELETON;
	}
	else if( info.suffix() == "material" )
	{
		event->handle = XE::OPEN_ASSET_MATERIAL;
	}

	XE::XESFramework::GetCurrentFramework()->GetServiceT<XE::IEventService>()->PostEvent( event );
}

void AssetsDockWidget::AddTreeWidgetFolder( const QString & path, QTreeWidgetItem * parent )
{
	QDir dir( path );
	if( !dir.exists() )
	{
		return;
	}
	dir.setFilter( QDir::Dirs );
	QFileInfoList list = dir.entryInfoList();

	for( const auto & info : list )
	{
		if( info.fileName() == "." || info.fileName() == ".." )
		{
			continue;
		}

		auto item = new QTreeWidgetItem( parent );

		auto font = item->font( 0 );
		font.setPointSize( 12 );
		item->setFont( 0, font );
		item->setText( 0, info.fileName() );
		item->setToolTip( 0, info.fileName() );
		item->setIcon( 0, QIcon( ":/icons/folder.png" ) );
		item->setData( 0, Qt::UserRole + 1, info.absoluteFilePath().toUtf8() );
		item->setFlags( item->flags() | Qt::ItemFlag::ItemIsEditable );

		AddTreeWidgetFolder( info.absoluteFilePath(), item );
	}
}

void AssetsDockWidget::ResetListWidgetItem( const QString & path )
{
	ui->listWidgetItem->clear();

	QDir dir( path );
	if( !dir.exists() )
	{
		return;
	}
	dir.setFilter( QDir::Files );
	QFileInfoList list = dir.entryInfoList();

	for( const auto & info : list )
	{
		if( ui->comboBoxFilter->currentText() != "" )
		{
			if( ui->comboBoxFilter->currentText() == "unknown" )
			{
				bool continued = false;
				for( int i = 0; i < ui->comboBoxFilter->count(); ++i )
				{
					if( ui->comboBoxFilter->itemText( i ) == info.suffix() )
					{
						continued = true;
						break;
					}
				}
				if( continued )
				{
					continue;
				}
			}
			else if( ui->comboBoxFilter->currentText() != info.suffix() )
			{
				continue;
			}
		}

		auto item = new QListWidgetItem( ui->listWidgetItem );

		item->setText( info.baseName() );
		item->setToolTip( info.fileName() );
		item->setIcon( QIcon( SuffixToIcon( info.suffix() ) ) );
		item->setData( Qt::UserRole + 1, info.absoluteFilePath().toUtf8() );
		item->setFlags( item->flags() | Qt::ItemFlag::ItemIsEditable );

		ui->listWidgetItem->addItem( item );
	}
}

void AssetsDockWidget::ImportAsset( const QString & path )
{
	QFileInfo info( path );

	auto it = _Supports.find( info.suffix() );
	if( it != _Supports.end() )
	{
		it.value()->Importer( path, _CurrentPath );
	}
}

QString AssetsDockWidget::SuffixToIcon( const QString & suffix ) const
{
	auto it = _SuffixIcon.find( suffix );
	if( it != _SuffixIcon.end() )
	{
		return it.value();
	}

	static QMap<QString, QString> icon_map = {
		{ "ai", ":/icons/ai.png" },
		{ "mesh", ":/icons/mesh.png" },
		{ "anim", ":/icons/anim.png" },
		{ "sound", ":/icons/sound.png" },
		{ "world", ":/icons/world.png" },
		{ "prefab", ":/icons/prefab.png" },
		{ "shader", ":/icons/shader.png" },
		{ "texture", ":/icons/texture.png" },
		{ "skeleton", ":/icons/skeleton.png" },
		{ "material", ":/icons/material.png" }
	};

	auto it2 = icon_map.find( suffix );
	if( it2 != icon_map.end() )
	{
		return it2.value();
	}

	return ":/icons/unknown.png";
}
