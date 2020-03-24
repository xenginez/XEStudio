/*!
 * \file	FSMGraphicsSocket.h
 *
 * \author	ZhengYuanQing
 * \date	2020/03/16
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef FSMGRAPHICSSOCKET_H__4E6E823D_B411_416F_B2B9_A3DA9D2C53C5
#define FSMGRAPHICSSOCKET_H__4E6E823D_B411_416F_B2B9_A3DA9D2C53C5

#include "GraphicsSocket.h"

class FSMGraphicsSocket : public GraphicsSocket
{
public:
	FSMGraphicsSocket( QGraphicsItem * parent = nullptr );

	~FSMGraphicsSocket() override;

public:
	const QLineF & GetLine() const;

	void SetLine( const QLineF & val );

public:
	const XE::ConditionPtr & GetCondition() const;

	void SetCondition( const XE::ConditionPtr & val );

public:
	void paint( QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget /* = nullptr */ );

	QPainterPath shape() const override;

protected:
	QVariant itemChange( GraphicsItemChange change, const QVariant & value ) override;

private:
	QLineF _Line;
	XE::ConditionPtr _Condition;
};

#endif // FSMGRAPHICSSOCKET_H__4E6E823D_B411_416F_B2B9_A3DA9D2C53C5
