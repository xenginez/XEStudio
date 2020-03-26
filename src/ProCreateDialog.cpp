#include "ProCreateDialog.h"
#include "ui_ProCreateDialog.h"

#include "XESFramework.h"

#include <zipper/zipper.h>
#include <zipper/unzipper.h>

ProCreateDialog::ProCreateDialog( QWidget * parent /*= nullptr */ )
	:QDialog( parent ), ui( new Ui::ProCreateDialog )
{
	ui->setupUi( this );

	LoadPackage();

	connect( ui->toolButton, &QToolButton::clicked, this, &ProCreateDialog::OnToolButton );
	connect( ui->pushButtonNo, &QToolButton::clicked, this, &ProCreateDialog::OnPushButtonNo );
	connect( ui->pushButtonYes, &QToolButton::clicked, this, &ProCreateDialog::OnPushButtonYes );

	connect( ui->lineEditName, &QLineEdit::textChanged, [this]( const QString & )
			 {
				 CreateDescription();
			 } );
	connect( ui->lineEditFolder, &QLineEdit::textChanged, [this]( const QString & )
			 {
				 CreateDescription();
			 } );
	connect( ui->listWidget, &QListWidget::itemSelectionChanged, this, &ProCreateDialog::CreateDescription );
}

ProCreateDialog::~ProCreateDialog()
{
	delete ui;
}

const QString & ProCreateDialog::GetPath() const
{
	return _Path;
}

void ProCreateDialog::LoadPackage()
{
	auto path = XE::XESFramework::GetCurrentFramework()->GetPackagePath();

	std::filesystem::directory_iterator end;
	for( std::filesystem::directory_iterator it( path ); it != end; ++it )
	{
		auto item = new QListWidgetItem( ui->listWidget );
		auto p = it->path();
		item->setIcon( QIcon(":/DarkStyle/icon_restore.png") );
		item->setText( it->path().stem().u8string().c_str() );
		item->setData( Qt::UserRole + 1, QString( it->path().u8string().c_str() ) );

		zipper::Unzipper unzip( it->path().u8string() );
		auto entries = unzip.entries();
		QString tooltip;

		for( const auto & entry : entries )
		{
			tooltip += entry.name.c_str();
			tooltip += "\n";
		}

		item->setToolTip( tooltip );

		ui->listWidget->addItem( item );
	}
}

void ProCreateDialog::OnToolButton()
{
	auto str = QFileDialog::getExistingDirectory( this, tr( "Select Directory" ), "/home" );

	if( str != "" )
	{
		ui->lineEditFolder->setText( str );
	}
}

void ProCreateDialog::OnPushButtonYes()
{
	if( ui->lineEditName->text().isEmpty() )
	{
		QMessageBox::warning( this, tr( "warning" ), tr( "project name is empty!" ) );
		return;
	}
	if( ui->lineEditFolder->text().isEmpty() )
	{
		QMessageBox::warning( this, tr( "warning" ), tr( "project path is empty!" ) );
		return;
	}

	_Path = ui->lineEditFolder->text() + "/" + ui->lineEditName->text();

	if( CreateProject() )
	{
		accept();
	}
	else
	{
		_Path = "";
		QMessageBox::warning( this, tr( "warning" ), tr( "create project fail!" ) );
	}
}

void ProCreateDialog::OnPushButtonNo()
{
	reject();
}

bool ProCreateDialog::CreateProject()
{
	auto path = std::filesystem::path( _Path.toUtf8().toStdString() );

	std::error_code code;
	if( !std::filesystem::create_directory( path, code ) )
	{
		std::cout << path << " : " << code.message() << std::endl;
		return false;
	}
	if( !std::filesystem::create_directory( path / "assets", code ) )
	{
		std::cout << path / "assets" << " : " << code.message() << std::endl;
		return false;
	}
	if( !std::filesystem::create_directory( path / "data", code ) )
	{
		std::cout << path / "data" << " : " << code.message() << std::endl;
		return false;
	}
	if( !std::filesystem::create_directory( path / "modules", code ) )
	{
		std::cout << path / "modules" << " : " << code.message() << std::endl;
		return false;
	}
	if( !std::filesystem::create_directory( path / "plugins", code ) )
	{
		std::cout << path / "plugins" << " : " << code.message() << std::endl;
		return false;
	}
	if( !std::filesystem::create_directory( path / "source", code ) )
	{
		std::cout << path / "source" << " : " << code.message() << std::endl;
		return false;
	}


	std::ofstream proj( path / ( path.stem().u8string() + ".xeproj" ) );
	proj << " \
	{\n \
		\"System\" : {\n \
			\"Services\" : \"XE::TimerService,XE::EventService,XE::XESAssetsService,XE::XESPluginService,XE::XESMetaService\"\n \
		}\n \
	}" << std::endl;
	proj.close();

	std::ofstream cmake( path / "source" / "CMakeLists.txt" );
	XE::String str = XE::StringUtils::Format( " \
	cmake_minimum_required( VERSION 3.12 )\n \
	project( \"%1\" )\n \
	if( CMAKE_BUILD_TYPE MATCHES \"Debug\" )\n \
		set( XE_CONFIG debug )\n \
	else ( )\n \
		set( XE_CONFIG release )\n \
	endif()\n \
	if( CMAKE_SYSTEM_NAME MATCHES \"Linux\" )\n \
		set( XE_PLATFORM_PATH linux )\n \
	elseif( CMAKE_SYSTEM_NAME MATCHES \"Windows\" )\n \
		set( XE_PLATFORM_PATH win )\n \
	elseif( CMAKE_SYSTEM_NAME MATCHES \"IOS\" )\n \
		set( XE_PLATFORM_PATH ios )\n \
	elseif( CMAKE_SYSTEM_NAME MATCHES \"Android\" )\n \
		set( XE_PLATFORM_PATH android )\n \
	elseif( CMAKE_SYSTEM_NAME MATCHES \"Darwin\" )\n \
		set( XE_PLATFORM_PATH mac )\n \
	else ( )\n \
		message( FATAL_ERROR ${ CMAKE_SYSTEM_NAME }\" Other\" )\n \
	endif()\n \
	set( CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${ CMAKE_CURRENT_SOURCE_DIR }/ ../modules/%1 )\n \
	set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${ CMAKE_CURRENT_SOURCE_DIR }/ ../modules/%1 )\n \
	set( CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${ CMAKE_CURRENT_SOURCE_DIR }/../modules/%1 )\n \
	set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${ CMAKE_CURRENT_SOURCE_DIR }/../modules/%1 )\n \
	include_directories(\n \
		${ CMAKE_CURRENT_SOURCE_DIR }\n \
		%2/../include\n \
		%2/../include/XE\n \
		%2/../include/XEStudio\n \
	)\n \
	link_directories(\n \
		%2\n \
	)\n \
	FILE( GLOB_RECURSE SRC_FILES *.cpp )\n \
	add_library( %1 SHARED ${ SRC_FILES } )\n \
	target_link_libraries( %1 PRIVATE XE )",
	ui->lineEditName->text().toUtf8().toStdString(), XE::XESFramework::GetCurrentFramework()->GetApplicationPath().u8string() );
	cmake << str.ToStdString() << std::endl;
	cmake.close();

	auto items = ui->listWidget->selectedItems();
	for( const auto & item : items )
	{
		std::filesystem::path package_path = item->data( Qt::UserRole + 1 ).toString().toUtf8().toStdString();

		if( std::filesystem::exists( package_path ) )
		{
			zipper::Unzipper unzip( package_path.u8string() );

			auto entries = unzip.entries();

			for( const auto & entry : entries )
			{
				auto p = path / entry.name;

				if( entry.compressedSize == 0 )
				{
					std::error_code code;
					if( !std::filesystem::create_directory( p, code ) )
					{
						std::cout << p << " : " << code.message() << std::endl;
					}
				}
				else
				{
					if( std::filesystem::exists( p ) )
					{
						if( QMessageBox::warning( this, "warning", QString( p.u8string().c_str() ) + tr( " already exists, do you want to replace it?" ), QMessageBox::StandardButton::Yes, QMessageBox::StandardButton::No ) == QMessageBox::StandardButton::Yes )
						{
							std::ofstream ofs( p );

							unzip.extractEntryToStream( entry.name, ofs );

							ofs.close();
						}
					}
				}
			}
		}
	}

	return true;
}

void ProCreateDialog::CreateDescription()
{ 
	QString str = "Project Name: %1\n\nProject Path: %2\n\nPackages:\n";
	str = str.arg( ui->lineEditName->text() ).arg( ui->lineEditFolder->text() );

	auto items = ui->listWidget->selectedItems();
	for( const auto & item : items )
	{
		str += "\t" + item->text() + "\n";
	}

	ui->labelDescription->setText( str );
}
