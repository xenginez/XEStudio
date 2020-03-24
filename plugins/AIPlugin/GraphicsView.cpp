#include "GraphicsView.h"

#include "GraphicsScene.h"
#include "GraphicsWidget.h"

GraphicsView::GraphicsView( QWidget * parent /*= nullptr */ )
	:QGraphicsView( parent ), _Sacle( 1.0f )
{
	setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOff );
	setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOff );
	setRenderHint( QPainter::Antialiasing );
	setSceneRect( -std::numeric_limits<XE::int32>::min() / 2, -std::numeric_limits<XE::int32>::min() / 2, std::numeric_limits<XE::int32>::max(), std::numeric_limits<XE::int32>::max() );
	centerOn( 0, 0 );
	
	setMouseTracking( true );
}

GraphicsView::~GraphicsView()
{

}

void GraphicsView::wheelEvent( QWheelEvent * event )
{
	qreal delta = 0;

	if( event->delta() > 0 )
	{
		delta = 1.1;
	}
	else if( event->delta() < 0 )
	{
		delta = 0.9;
	}

	if( ( _Sacle * delta ) < 0.5 || ( _Sacle * delta ) > 3.0 )
	{
		return;
	}

	_Sacle *= delta;

	setTransformationAnchor( QGraphicsView::AnchorUnderMouse );

	scale( delta, delta );

	setTransformationAnchor( QGraphicsView::AnchorViewCenter );
}

void GraphicsView::mousePressEvent( QMouseEvent * event )
{
	if( event->button() == Qt::LeftButton )
	{
		_MovePos = event->pos();
	}

	QGraphicsView::mousePressEvent( event );
}

void GraphicsView::mouseMoveEvent( QMouseEvent * event )
{
	if( event->buttons() & Qt::MouseButton::LeftButton )
	{
		if( scene()->selectedItems().size() == 0 )
		{
			QPointF delta = mapToScene( event->pos() ) - mapToScene( _MovePos );
			translate( delta );
			_MovePos = event->pos();
		}
	}

	QGraphicsView::mouseMoveEvent( event );
}

void GraphicsView::mouseReleaseEvent( QMouseEvent * event )
{
	QGraphicsView::mouseReleaseEvent( event );
}

void GraphicsView::translate( QPointF val )
{
	val *= _Sacle;

	setTransformationAnchor( QGraphicsView::AnchorUnderMouse );

	QPoint newCenter( ( viewport()->rect().width() ) / 2 - val.x(), ( viewport()->rect().height() ) / 2 - val.y() );
	centerOn( mapToScene( newCenter ) );

	setTransformationAnchor( QGraphicsView::AnchorViewCenter );
}

GraphicsWidget * GraphicsView::GetGraphicsWidget() const
{
	return _Widget;
}

void GraphicsView::SetGraphicsWidget( GraphicsWidget * val )
{
	_Widget = val;
}
