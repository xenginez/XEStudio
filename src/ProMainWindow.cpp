#include "ProMainWindow.h"
#include "ui_ProMainWindow.h"

#include <QDesktopWidget>

#include "XESFramework.h"
#include "ProCreateDialog.h"
#include "ProListWidgetItem.h"

ProMainWindow::ProMainWindow( QWidget * parent /*= nullptr*/, Qt::WindowFlags flags /*= Qt::WindowFlags() */ )
	:QMainWindow( parent, flags ), ui( new Ui::ProMainWindow )
{
	ui->setupUi( this );

	setWindowFlags( Qt::FramelessWindowHint );

	int width = QApplication::desktop()->width();
	int height = QApplication::desktop()->height();
	 
	setMinimumSize( width / 2, height / 2 );
	setMaximumSize( width / 2, height / 2 );
	 
	_Close.load( ":/DarkStyle/icon_close.png" );
	_Close2.load( ":/DarkStyle/icon_close2.png" );

	ui->labelClose->setPixmap( _Close );
	ui->labelOpenImage->setPixmap( QPixmap( ":/DarkStyle/open.png" ) );
	ui->labelCreateImage->setPixmap( QPixmap( ":/DarkStyle/new.png" ) );
	 
	move( width / 4, height / 4 );

	ui->labelClose->installEventFilter( this );
	ui->widgetOpen->installEventFilter( this );
	ui->widgetCreate->installEventFilter( this );

	LoadRecents();
}

ProMainWindow::~ProMainWindow()
{
	delete ui;
}

bool ProMainWindow::eventFilter( QObject * obj, QEvent * event )
{
	if( obj == ui->labelClose )
	{
		if( event->type() == QEvent::Type::Enter )
		{
			ui->labelClose->setPixmap( _Close2 );
		}
		else if( event->type() == QEvent::Type::Leave )
		{
			ui->labelClose->setPixmap( _Close );
		}
		else if( event->type() == QEvent::Type::MouseButtonRelease )
		{
			close();
		}
	}
	else if( obj == ui->widgetOpen )
	{
		if( event->type() == QEvent::Type::Enter )
		{
			ui->widgetOpen->setStyleSheet( "background-color: rgb(100, 100, 100);" );
		}
		else if( event->type() == QEvent::Type::Leave )
		{
			ui->widgetOpen->setStyleSheet( "background-color: rgb(53, 53, 53);" );
		}
		else if( event->type() == QEvent::Type::MouseButtonRelease )
		{
			auto str = QFileDialog::getOpenFileName( this, tr( "Open Project" ),
													 "/home",
													 tr( "Project (*.xeproj)" ) );

			if( str != "" )
			{
				QFileInfo info( str );

				XE::XESFramework::GetCurrentFramework()->SetProjectName( info.baseName().toUtf8().toStdString() );
				XE::XESFramework::GetCurrentFramework()->SetProjectPath( info.path().toUtf8().toStdString() );

				auto list = ReadProjectJson();
				for( auto it = list.begin(); it != list.end(); ++it )
				{
					if( str == *it )
					{
						list.erase( it );
						break;
					}
				}
				list.push_front( str );
				WriteProjectJson( list );

				close();
			}
		}
	}
	else if( obj == ui->widgetCreate )
	{
		if( event->type() == QEvent::Type::Enter )
		{
			ui->widgetCreate->setStyleSheet( "background-color: rgb(100, 100, 100);" );
		}
		else if( event->type() == QEvent::Type::Leave )
		{
			ui->widgetCreate->setStyleSheet( "background-color: rgb(53, 53, 53);" );
		}
		else if( event->type() == QEvent::Type::MouseButtonRelease )
		{
			ProCreateDialog dialog( this );

			if( dialog.exec() == QDialog::Accepted )
			{
				QFileInfo info( dialog.GetPath() );

				XE::XESFramework::GetCurrentFramework()->SetProjectName( info.baseName().toUtf8().toStdString() );
				XE::XESFramework::GetCurrentFramework()->SetProjectPath( info.path().toUtf8().toStdString() );

				auto list = ReadProjectJson();
				for( auto it = list.begin(); it != list.end(); ++it )
				{
					if( dialog.GetPath() == *it )
					{
						list.erase( it );
						break;
					}
				}
				list.push_front( dialog.GetPath() );
				WriteProjectJson( list );

				close();
			}
		}
	}

	return QMainWindow::eventFilter( obj, event );
}

void ProMainWindow::LoadRecents()
{

	auto arr = ReadProjectJson();

	for( const auto & path : arr )
	{
		auto widget = new ProListWidgetItem( path, ui->listWidget );

		auto item = new QListWidgetItem( ui->listWidget );
		item->setFlags( Qt::ItemFlag::NoItemFlags );
		item->setSizeHint( widget->sizeHint() );
		ui->listWidget->addItem( item );
		ui->listWidget->setItemWidget( item, widget );

		connect( widget, &ProListWidgetItem::DoubleClicked, [this, widget]()
				 {
					 QFileInfo info( widget->GetPath() );

					 XE::XESFramework::GetCurrentFramework()->SetProjectName( info.baseName().toUtf8().toStdString() );
					 XE::XESFramework::GetCurrentFramework()->SetProjectPath( info.path().toUtf8().toStdString() );

					 auto list = ReadProjectJson();
					 for( auto it = list.begin(); it != list.end(); ++it )
					 {
						 if( widget->GetPath() == *it )
						 {
							 list.erase( it );
							 break;
						 }
					 }
					 list.push_front( widget->GetPath() );
					 WriteProjectJson( list );

					 close();
				 } );
		connect( widget, &ProListWidgetItem::DeleteItem, [this, item, widget]()
				 {
					 auto list = ReadProjectJson();
					 for( auto it = list.begin(); it != list.end(); ++it )
					 {
						 if( *it == widget->GetPath() )
						 {
							 list.erase( it );
							 break;
						 }
					 }
					 WriteProjectJson( list );

					 ui->listWidget->removeItemWidget( item );
					 delete ui->listWidget->takeItem( ui->listWidget->row( item ) );
				 } );
	}
}

QStringList ProMainWindow::ReadProjectJson() const
{
	QStringList list;

	auto path = XE::XESFramework::GetCurrentFramework()->GetApplicationPath() / "projects.json";

	QFile file( QString::fromUtf8( path.u8string().c_str() ) );
	if( file.open( QIODevice::ReadOnly ) )
	{
		QJsonParseError error;
		auto doc = QJsonDocument::fromJson( file.readAll(), &error );
		if( error.error == QJsonParseError::NoError )
		{
			auto arr = doc.array();
			for( const auto & it : arr )
			{
				list.push_back( it.toString() );
			}
		}
	}

	return list;
}

void ProMainWindow::WriteProjectJson( const QStringList & val ) const
{
	auto list = val;

	if( list.size() > 10 )
	{
		list.erase( list.begin() + 10, list.end() );
	}

	auto path = XE::XESFramework::GetCurrentFramework()->GetApplicationPath() / "projects.json";

	QFile file( QString::fromUtf8( path.u8string().c_str() ) );
	if( file.open( QIODevice::WriteOnly ) )
	{
		QJsonParseError error;
		auto doc = QJsonDocument::fromJson( "[]", &error );
		if( error.error == QJsonParseError::NoError )
		{
			auto arr = QJsonArray::fromStringList( list );

			doc.setArray( arr );

			file.write( doc.toJson() );
		}
	}
}
