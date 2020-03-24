/*!
 * \file	GraphicsWidget.h
 *
 * \author	ZhengYuanQing
 * \date	2020/03/14
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef GRAPHICSWIDGET_H__BF39D758_E862_4921_843A_751A072F9A57
#define GRAPHICSWIDGET_H__BF39D758_E862_4921_843A_751A072F9A57

#include "GraphicsView.h"
#include "GraphicsScene.h"

class GraphicsWidget : public QWidget
{
	Q_OBJECT

public:
	GraphicsWidget( QWidget * parent = nullptr );

	~GraphicsWidget() override;

public:
	const XE::AIModulePtr & GetAIModule() const;

	void SetAIModule( const XE::AIModulePtr & val );

public:
	void ShowProperty( const XE::ObjectPtr & val );

	void Save();

private:
	GraphicsView * _View;
	QSplitter * _Splitter;
	GraphicsScene * _Scene;
	XE::AIModulePtr _AIModule;
	XE::ObjectPtr _Property;
	XESMetaWidget * _PropertyWidget;
	XESMetaWidget * _BlockBoardWidget;
};

#endif // GRAPHICSWIDGET_H__BF39D758_E862_4921_843A_751A072F9A57
