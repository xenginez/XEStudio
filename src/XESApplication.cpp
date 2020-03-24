#include "XESApplication.h"

#include "XESFramework.h"

XESApplication::XESApplication( int & argc, char ** argv )
	:QApplication(argc, argv )
{

}

XESApplication::~XESApplication()
{

}

bool XESApplication::notify( QObject * obj, QEvent * event )
{
	if( event->type() == QEvent::KeyRelease )
	{
		QKeyEvent * keyEvent = static_cast< QKeyEvent * >( event );

		if( keyEvent->modifiers() == ( Qt::KeyboardModifier::ControlModifier | Qt::KeyboardModifier::ShiftModifier ) )
		{
			if( keyEvent->key() == Qt::Key_S )
			{
				XE::XESFramework::GetCurrentFramework()->Save();
			}
		}
	}

	return QApplication::notify( obj, event );
}
