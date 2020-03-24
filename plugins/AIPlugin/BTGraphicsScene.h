/*!
 * \file	BTGraphicsScene.h
 *
 * \author	ZhengYuanQing
 * \date	2020/03/18
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef BTGRAPHICSSCENE_H__E4FBA6BF_7075_49D7_9FAA_4D389C800483
#define BTGRAPHICSSCENE_H__E4FBA6BF_7075_49D7_9FAA_4D389C800483

#include "GraphicsScene.h"

#include "BTGraphicsItem.h"

class BTGraphicsScene : public GraphicsScene
{
	Q_OBJECT

public:
	BTGraphicsScene( QObject * parent = nullptr );

	~BTGraphicsScene() override;

public:
	XE::BehaviorTreePtr GetBehaviorTree() const;

public:
	void ResetGraphics() override;

protected:
	void mousePressEvent( QGraphicsSceneMouseEvent * event ) override;

	void mouseReleaseEvent( QGraphicsSceneMouseEvent * event ) override;

	void contextMenuEvent( QGraphicsSceneContextMenuEvent * event ) override;

private:
	int CalcMaxFloor( const XE::NodePtr & node, int floor );

	BTGraphicsItem * AddNode( const XE::NodePtr & node, int floor, int & x );

	void AddSocket( const XE::NodePtr & node );

	void AddNodeAction( QMenu * menu, const XE::IMetaClassPtr & cls );

private:
	BTGraphicsItem * _SelectItem;
	QMap<XE::NodeHandle, BTGraphicsItem *> _Nodes;
};

#endif // BTGRAPHICSSCENE_H__E4FBA6BF_7075_49D7_9FAA_4D389C800483
