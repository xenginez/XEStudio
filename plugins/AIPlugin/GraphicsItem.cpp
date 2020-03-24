#include "GraphicsItem.h"

#include "GraphicsScene.h"

GraphicsItem::GraphicsItem( QGraphicsItem * parent /*= nullptr */ )
	:QGraphicsItem( parent )
{
	setZValue( 1 );
	setFlags( QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsFocusable );
}

GraphicsItem::~GraphicsItem()
{

}

GraphicsScene * GraphicsItem::GetGraphicsScene() const
{
	return dynamic_cast< GraphicsScene * >( scene() );
}
