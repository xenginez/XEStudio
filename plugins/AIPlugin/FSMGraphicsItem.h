/*!
 * \file	FSMGraphicsItem.h
 *
 * \author	ZhengYuanQing
 * \date	2020/03/15
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef FSMGRAPHICSITEM_H__9AAD2138_EE01_4C64_9CE2_1BA9BE8A0EC1
#define FSMGRAPHICSITEM_H__9AAD2138_EE01_4C64_9CE2_1BA9BE8A0EC1

#include "GraphicsItem.h"

class FSMGraphicsItem : public GraphicsItem
{
public:
	static constexpr XE::float32 Radius = 40;

public:
	FSMGraphicsItem( QGraphicsItem * parent = nullptr );

	~FSMGraphicsItem() override;

public:
	const XE::StatePtr & GetState() const;

	void SetState( const XE::StatePtr & val );

public:
	void paint( QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget /* = nullptr */ );

	QRectF boundingRect() const override;

protected:
	void contextMenuEvent( QGraphicsSceneContextMenuEvent * event ) override;

	QVariant itemChange( GraphicsItemChange change, const QVariant & value ) override;

private:
	void AddConditionalAction( QMenu * menu, const XE::IMetaClassPtr & val ) const;

private:
	XE::StatePtr _State;
};

#endif // FSMGRAPHICSITEM_H__9AAD2138_EE01_4C64_9CE2_1BA9BE8A0EC1
