/*!
 * \file	GraphicsSocket.h
 *
 * \author	ZhengYuanQing
 * \date	2020/03/13
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef GRAPHICSSOCKET_H__40E7E98D_45A3_48CF_B431_B8B1ACD01219
#define GRAPHICSSOCKET_H__40E7E98D_45A3_48CF_B431_B8B1ACD01219

#include "GraphicsItem.h"

class GraphicsSocket : public QGraphicsItem
{
public:
	GraphicsSocket( QGraphicsItem * parent = nullptr );

	~GraphicsSocket() override;

public:
	GraphicsItem * GetLastItem() const;

	void SetLastItem( GraphicsItem * item );

	GraphicsItem * GetNextItem() const;

	void SetNextItem( GraphicsItem * item );

public:
	QRectF boundingRect() const override;

public:
	GraphicsScene * GetGraphicsScene() const;

private:
	GraphicsItem * _Last;
	GraphicsItem * _Next;
};

#endif // GRAPHICSSOCKET_H__40E7E98D_45A3_48CF_B431_B8B1ACD01219
