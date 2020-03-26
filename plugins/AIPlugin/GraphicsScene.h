/*!
 * \file	GraphicsScene.h
 *
 * \author	ZhengYuanQing
 * \date	2020/03/13
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef GRAPHICSSCENE_H__A1F22755_8561_4638_BA49_916C0AE48E1D
#define GRAPHICSSCENE_H__A1F22755_8561_4638_BA49_916C0AE48E1D

#include "Global.h"

class GraphicsScene : public QGraphicsScene
{
	Q_OBJECT

public:
	GraphicsScene( QObject * parent = nullptr );

	~GraphicsScene() override;

public:
	virtual void ResetGraphics() = 0;

public:
	AIDockWidget * GetDockWidget() const;

public:
	GraphicsView * GetGraphicsView() const;

	void SetGraphicsView( GraphicsView * val );

protected:
	void drawBackground( QPainter * painter, const QRectF & rect ) override;

private:
	GraphicsView * _View;
};

#endif // GRAPHICSSCENE_H__A1F22755_8561_4638_BA49_916C0AE48E1D
