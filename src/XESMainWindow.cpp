#include "XESMainWindow.h"

#include "XESDockWidget.h"

XESMainWindow::XESMainWindow( QWidget * parent /* = nullptr */ )
	: QMainWindow( parent )
{
	QWidget * p = takeCentralWidget();
	if( p )
	{
		p->deleteLater();
	}

	setDockNestingEnabled( true );


}

XESMainWindow::~XESMainWindow()
{

}

void XESMainWindow::Save()
{
	auto docks = findChildren<XESDockWidget *>();

	for( auto dock : docks )
	{
		dock->Save();
	}
}

void XESMainWindow::ResizeDocks()
{
	auto width = this->geometry().width();
	auto height = this->geometry().height();

	QList<int> h_resize;
	QList<QDockWidget *> h_docks;
	QList<int> v_resize;
	QList<QDockWidget *> v_docks;
	auto docks = findChildren<QDockWidget *>();
	for( auto dock : docks )
	{
		switch( this->dockWidgetArea( dock ) )
		{
		case Qt::DockWidgetArea::LeftDockWidgetArea:
		case Qt::DockWidgetArea::RightDockWidgetArea:
			h_resize.push_back( width * 0.2f );
			h_docks.push_back( dock );
			break;
		case Qt::DockWidgetArea::TopDockWidgetArea:
			v_resize.push_back( height * 0.7f );
			v_docks.push_back( dock );
			break;
		case Qt::DockWidgetArea::BottomDockWidgetArea:
			v_resize.push_back( height * 0.3f );
			v_docks.push_back( dock );
			break;
		default:
			break;
		}
	}

	this->resizeDocks( v_docks, v_resize, Qt::Orientation::Vertical );
	this->resizeDocks( h_docks, h_resize, Qt::Orientation::Horizontal );
}
