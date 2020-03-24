#include "BTGraphicsSocket.h"

BTGraphicsSocket::BTGraphicsSocket( QGraphicsItem * parent /*= nullptr */ )
	:GraphicsSocket( parent )
{

}

BTGraphicsSocket::~BTGraphicsSocket()
{

}

QPainterPath BTGraphicsSocket::shape() const
{
	return QPainterPath();
}

void BTGraphicsSocket::paint( QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget /* = nullptr */ )
{
	auto last_pos = GetLastItem()->pos() + GetLastItem()->boundingRect().center();
	auto next_pos = GetNextItem()->pos() + GetNextItem()->boundingRect().center();

	QPainterPath path;

	path.moveTo( last_pos );
	path.lineTo( { last_pos.x(), last_pos.y() + ( next_pos.y() - last_pos.y() ) * 0.5f } );
	path.lineTo( { next_pos.x(), last_pos.y() + ( next_pos.y() - last_pos.y() ) * 0.5f } );
	path.lineTo( next_pos );

	QPen pen;
	pen.setColor( Qt::white );


	painter->save();

	painter->setPen( pen );
	painter->drawPath( path );

	painter->restore();


}
