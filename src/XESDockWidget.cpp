#include "XESDockWidget.h"

#include "XESFramework.h"

struct XESDockWidget::Private
{
	bool _Dirty = false;
	XE::Stack< XE::XESCMD > _Todo;
	XE::Stack< XE::XESCMD > _Undo;
};

XESDockWidget::XESDockWidget( const QString & title, QWidget * parent /*= nullptr*/, Qt::WindowFlags flags /*= Qt::WindowFlags() */ )
	:QDockWidget( title, parent, flags ), _p( new Private )
{
	setAllowedAreas( Qt::DockWidgetArea::BottomDockWidgetArea | Qt::DockWidgetArea::LeftDockWidgetArea | Qt::DockWidgetArea::RightDockWidgetArea );
}

XESDockWidget::XESDockWidget( QWidget * parent /*= nullptr*/, Qt::WindowFlags flags /*= Qt::WindowFlags() */ )
	: QDockWidget( parent, flags ), _p( new Private )
{
	setAllowedAreas( Qt::DockWidgetArea::BottomDockWidgetArea | Qt::DockWidgetArea::LeftDockWidgetArea | Qt::DockWidgetArea::RightDockWidgetArea );
}

XESDockWidget::~XESDockWidget()
{
	delete _p;
}

void XESDockWidget::Save()
{
	_p->_Dirty = false;

	setWindowTitle( windowTitle().replace( " *", "" ) );
}

void XESDockWidget::Execute( XE::XESCMD && cmd )
{
	TodoCMD( std::move( cmd ) );
}

void XESDockWidget::keyPressEvent( QKeyEvent * event )
{
	if ( event->modifiers() == Qt::KeyboardModifier::ControlModifier )
	{
		if( event->key() == Qt::Key_Z )
		{
			if( _p->_Todo.size() )
			{
				auto cmd = _p->_Todo.top();
				_p->_Todo.pop();

				UndoCMD( std::move( cmd ) );
			}
		}
		else if( event->key() == Qt::Key_Y )
		{
			if( _p->_Undo.size() )
			{
				auto cmd = _p->_Undo.top();
				_p->_Undo.pop();

				TodoCMD( std::move( cmd ) );
			}
		}
		else if( event->key() == Qt::Key_S )
		{
			if( _p->_Dirty )
			{
				_p->_Todo = {};
				_p->_Undo = {};

				Save();
			}
		}
	}

	QDockWidget::keyReleaseEvent( event );
}

void XESDockWidget::TodoCMD( XE::XESCMD && cmd )
{
	if( cmd.Todo )
	{
		cmd.Todo();

		if( !_p->_Dirty )
		{
			_p->_Dirty = true;
			setWindowTitle( windowTitle() + " *" );
		}

		_p->_Todo.push( cmd );
	}
}

void XESDockWidget::UndoCMD( XE::XESCMD && cmd )
{
	if( cmd.Undo )
	{
		cmd.Undo();

		if( !_p->_Dirty )
		{
			_p->_Dirty = true;
			setWindowTitle( windowTitle() + " *" );
		}

		_p->_Undo.push( cmd );
	}
}

bool XESDockWidget::event( QEvent * event )
{
	if( event->type() == QEvent::NonClientAreaMouseButtonDblClick )
	{
		if( isFloating() )
		{
			showMaximized();

			return true;
		}
	}

	return QDockWidget::event( event );
}
