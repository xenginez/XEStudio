#include "GraphicsSocket.h"

#include "GraphicsView.h"
#include "GraphicsScene.h"

GraphicsSocket::GraphicsSocket( QGraphicsItem * parent /*= nullptr */ )
	:QGraphicsItem( parent ), _Last( nullptr ), _Next( nullptr )
{

}

GraphicsSocket::~GraphicsSocket()
{

}

GraphicsItem * GraphicsSocket::GetLastItem() const
{
	return _Last;
}

void GraphicsSocket::SetLastItem( GraphicsItem * item )
{
	_Last = item;
}

GraphicsItem * GraphicsSocket::GetNextItem() const
{
	return _Next;
}

void GraphicsSocket::SetNextItem( GraphicsItem * item )
{
	_Next = item;
}

QRectF GraphicsSocket::boundingRect() const
{
	return GetGraphicsScene()->GetGraphicsView()->sceneRect();
}

GraphicsScene * GraphicsSocket::GetGraphicsScene() const
{
	return static_cast< GraphicsScene * >( scene() );
}
