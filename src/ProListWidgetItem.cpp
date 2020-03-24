#include "ProListWidgetItem.h"
#include "ui_ProListWidgetItem.h"

ProListWidgetItem::ProListWidgetItem( const QString & path, QWidget * parent /*= nullptr */ )
	:QWidget( parent ), ui( new Ui::ProListWidgetItem ), _Path( path )
{
	ui->setupUi( this );

	QFileInfo info( path );

	ui->labelTitle->setText( info.baseName() );
	ui->labelPath->setText( _Path );
	ui->labelIcon->setPixmap( QPixmap(":/DarkStyle/new.png") );
}

ProListWidgetItem::~ProListWidgetItem()
{
	delete ui;
}

const QString & ProListWidgetItem::GetPath() const
{
	return _Path;
}

void ProListWidgetItem::enterEvent( QEvent * event )
{
	setStyleSheet( "background-color: rgb(100, 100, 100);" );
}

void ProListWidgetItem::leaveEvent( QEvent * event )
{
	setStyleSheet( "background-color: rgb(53, 53, 53);" );
}

void ProListWidgetItem::mouseDoubleClickEvent( QMouseEvent * event )
{
	QFileInfo info( _Path );

	if (info.exists())
	{
		DoubleClicked( _Path );
	}
	else
	{
		QMessageBox::warning( nullptr, tr( "warning" ), tr( "the project no longer exists" ) );
		DeleteItem();
	}
}
