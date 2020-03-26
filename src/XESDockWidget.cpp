#include "XESDockWidget.h"

#include "XESDockCmd.h"
#include "XESFramework.h"

struct XESDockWidget::Private
{
	bool _Dirty = false;
	XE::Stack< XESDockCmdPtr > _Todo;
	XE::Stack< XESDockCmdPtr > _Undo;
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
	if( _p->_Dirty )
	{
		_p->_Todo = {};
		_p->_Undo = {};

		_p->_Dirty = false;

		setWindowTitle( windowTitle().replace( " *", "" ) );
	}
}

void XESDockWidget::Execute( const XESDockCmdPtr & cmd )
{
	TodoCMD( cmd );
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

				UndoCMD( cmd );
			}
		}
		else if( event->key() == Qt::Key_Y )
		{
			if( _p->_Undo.size() )
			{
				auto cmd = _p->_Undo.top();
				_p->_Undo.pop();

				TodoCMD( cmd );
			}
		}
		else if( event->key() == Qt::Key_S )
		{
			Save();
		}
	}

	QDockWidget::keyReleaseEvent( event );
}

void XESDockWidget::TodoCMD( const XESDockCmdPtr & cmd )
{
	if( cmd )
	{
		cmd->Todo();

		if( !_p->_Dirty )
		{
			_p->_Dirty = true;
			setWindowTitle( windowTitle() + " *" );
		}

		_p->_Todo.push( cmd );
	}
}

void XESDockWidget::UndoCMD( const XESDockCmdPtr & cmd )
{
	if( cmd )
	{
		cmd->Undo();

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
