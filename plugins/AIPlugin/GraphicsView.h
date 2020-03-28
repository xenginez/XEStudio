/*!
 * \file	GraphicsView.h
 *
 * \author	ZhengYuanQing
 * \date	2020/03/13
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef GRAPHICSVIEW_H__7DB6DEF8_DB20_47FF_B7A8_CA466CF9D1E7
#define GRAPHICSVIEW_H__7DB6DEF8_DB20_47FF_B7A8_CA466CF9D1E7

#include "Global.h"

class GraphicsView : public QGraphicsView
{
	Q_OBJECT

public:
	GraphicsView( QWidget * parent = nullptr );

	~GraphicsView() override;

public:
	XESDockWidget * GetDockWidget() const;

public:
	GraphicsWidget * GetGraphicsWidget() const;

	void SetGraphicsWidget( GraphicsWidget * val );

protected:
	void wheelEvent( QWheelEvent * event ) override;

	void mousePressEvent( QMouseEvent * event ) override;

	void mouseMoveEvent( QMouseEvent * event ) override;

	void mouseReleaseEvent( QMouseEvent * event ) override;

public:
	void translate( QPointF val );

private:
	qreal _Sacle;
	QPoint _MovePos;
	GraphicsWidget * _Widget;
};

#endif // GRAPHICSVIEW_H__7DB6DEF8_DB20_47FF_B7A8_CA466CF9D1E7
