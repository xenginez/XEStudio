/*!
 * \file	FSMGraphicsScene.h
 *
 * \author	ZhengYuanQing
 * \date	2020/03/14
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef FSMGRAPHICSSCENE_H__DB5F819B_1F6E_44E1_86E8_592DA7B4FE0C
#define FSMGRAPHICSSCENE_H__DB5F819B_1F6E_44E1_86E8_592DA7B4FE0C

#include "GraphicsScene.h"
#include "FSMGraphicsItem.h"
#include "FSMGraphicsSocket.h"

class FSMGraphicsScene : public GraphicsScene
{
	Q_OBJECT

public:
	FSMGraphicsScene( QObject * parent = nullptr );

	~FSMGraphicsScene() override;

protected: 
	void contextMenuEvent( QGraphicsSceneContextMenuEvent * contextMenuEvent ) override;

public:
	XE::StateMachinePtr GetStateMachine() const;

public:
	void ResetGraphics() override;

	void AddCondition( XE::StateHandle handle, const XE::IMetaClassPtr & cls );

protected:
	void mouseMoveEvent( QGraphicsSceneMouseEvent * mouseEvent ) override;

	void mousePressEvent( QGraphicsSceneMouseEvent * mouseEvent ) override;

private:
	void AddStateMenu( QMenu * menu, const XE::IMetaClassPtr & cls );

private:
	FSMGraphicsSocket * _Socket;
	QMap< XE::StateHandle, FSMGraphicsItem * > _Items;
};

#endif // FSMGRAPHICSSCENE_H__DB5F819B_1F6E_44E1_86E8_592DA7B4FE0C
