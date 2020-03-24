/*!
 * \file	BTGraphicsItem.h
 *
 * \author	ZhengYuanQing
 * \date	2020/03/18
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef BTGRAPHICSITEM_H__CB3D6AD4_E475_4256_8553_3273315AD428
#define BTGRAPHICSITEM_H__CB3D6AD4_E475_4256_8553_3273315AD428

#include "GraphicsItem.h"

class BTGraphicsItem : public GraphicsItem
{
public:
	static constexpr XE::uint32 Width = 100;
	static constexpr XE::uint32 Height = 60;

public:
	BTGraphicsItem( QGraphicsItem * parent = nullptr );

	~BTGraphicsItem() override;

public:
	const XE::NodePtr & GetNode() const;

	void SetNode( const XE::NodePtr & val );

public:
	QRectF boundingRect() const override;

	void setBoundingRect( const QRectF & val );

	void paint( QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget /* = nullptr */ );

protected:
	void contextMenuEvent( QGraphicsSceneContextMenuEvent * event ) override;

	QVariant itemChange( GraphicsItemChange change, const QVariant & value ) override;

private:
	void AddNodeAction( QMenu * menu, const XE::IMetaClassPtr & cls );

private:
	QRectF _Rect;
	XE::NodePtr _Node;
};

#endif // BTGRAPHICSITEM_H__CB3D6AD4_E475_4256_8553_3273315AD428
