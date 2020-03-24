/*!
 * \file	BTGraphicsSocket.h
 *
 * \author	ZhengYuanQing
 * \date	2020/03/18
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef BTGRAPHICSSOCKET_H__C12CAC29_BD94_455F_A1A2_43068CCBF2CF
#define BTGRAPHICSSOCKET_H__C12CAC29_BD94_455F_A1A2_43068CCBF2CF

#include "GraphicsSocket.h"

class BTGraphicsSocket : public GraphicsSocket
{
public:
	BTGraphicsSocket( QGraphicsItem * parent = nullptr );

	~BTGraphicsSocket() override;

public:
	QPainterPath shape() const override;

	void paint( QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget /* = nullptr */ );

};

#endif // BTGRAPHICSSOCKET_H__C12CAC29_BD94_455F_A1A2_43068CCBF2CF
