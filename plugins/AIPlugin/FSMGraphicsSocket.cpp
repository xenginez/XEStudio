#include "FSMGraphicsSocket.h"

#include "GraphicsView.h"
#include "GraphicsScene.h"
#include "GraphicsWidget.h"

FSMGraphicsSocket::FSMGraphicsSocket( QGraphicsItem * parent /*= nullptr */ )
	:GraphicsSocket( parent )
{
	setFlags( QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsFocusable );
}

FSMGraphicsSocket::~FSMGraphicsSocket()
{

}

const QLineF & FSMGraphicsSocket::GetLine() const
{
	return _Line;
}

void FSMGraphicsSocket::SetLine( const QLineF & val )
{
	_Line = val;
}

const XE::ConditionPtr & FSMGraphicsSocket::GetCondition() const
{
	return _Condition;
}

void FSMGraphicsSocket::SetCondition( const XE::ConditionPtr & val )
{
	_Condition = val;
	this->setToolTip( QString::fromUtf8( val->GetMetaClass()->GetName().ToCString() ) );
}

void FSMGraphicsSocket::paint( QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget /* = nullptr */ )
{
	QPainterPath path;

	QLineF line = _Line;

	if( GetLastItem() )
	{
		line.setP1( GetLastItem()->boundingRect().center() + GetLastItem()->pos() );
	}

	if( GetNextItem() )
	{
		line.setP2( GetNextItem()->boundingRect().center() + GetNextItem()->pos() );
	}

	_Line = line;

	path.moveTo( line.p1() );
	path.lineTo( line.p2() );

	auto v = line.unitVector();
	v.setLength( 10 );
	v.translate( line.dx() / 2, line.dy() / 2 );
	auto n = v.normalVector();
	n.setLength( n.length() * 0.5 );
	auto n2 = n.normalVector().normalVector();

	QPolygonF polygon;
	polygon.push_back( v.p2() );
	polygon.push_back( n.p2() );
	polygon.push_back( n2.p2() );
	polygon.push_back( v.p2() );

	path.addPolygon( polygon );

	QPen pen;
	pen.setColor( Qt::white );
	if( this->isSelected() )
	{
		pen.setColor( Qt::red );
	}

	painter->save();

	painter->setPen( pen );
	painter->fillPath( path, Qt::white );
	if( this->isSelected() )
	{
		painter->fillPath( path, Qt::red );
	}
	painter->drawPath( path );

	painter->restore();
}

QPainterPath FSMGraphicsSocket::shape() const
{
	QPainterPath path;

	auto line = _Line;
	auto v = line.unitVector();
	v.setLength( 10 );
	v.translate( line.dx() / 2, line.dy() / 2 );
	auto n = v.normalVector();
	n.setLength( n.length() * 0.5 );
	auto n2 = n.normalVector().normalVector();

	QPolygonF polygon;
	polygon.push_back( v.p2() );
	polygon.push_back( n.p2() );
	polygon.push_back( n2.p2() );
	polygon.push_back( v.p2() );

	path.addPolygon( polygon );

	return path;
}

QVariant FSMGraphicsSocket::itemChange( GraphicsItemChange change, const QVariant & value )
{
	if( change == QGraphicsItem::GraphicsItemChange::ItemSelectedChange )
	{
		if( value.toBool() )
		{
			GetGraphicsScene()->GetGraphicsView()->GetGraphicsWidget()->ShowProperty( _Condition );
		}
		else
		{
			GetGraphicsScene()->GetGraphicsView()->GetGraphicsWidget()->Save();
			GetGraphicsScene()->GetGraphicsView()->GetGraphicsWidget()->ShowProperty( nullptr );
		}
	}

	return QGraphicsItem::itemChange( change, value );
}
