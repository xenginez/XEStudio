/*!
 * \file	AIDockWidget.h
 *
 * \author	ZhengYuanQing
 * \date	2020/03/13
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef AIDOCKWIDGET_H__969089A6_A79B_48B9_ADD9_14427FF60F87
#define AIDOCKWIDGET_H__969089A6_A79B_48B9_ADD9_14427FF60F87

#include "Global.h"

class AIDockWidget : public XESDockWidget
{
	Q_OBJECT

public:
	AIDockWidget( QWidget * parent = nullptr, Qt::WindowFlags flags = Qt::WindowFlags() );

	~AIDockWidget() override;

public:
	void SetAssetPath( const XE::String & val );

public:
	void Save() override;

private:
	GraphicsWidget * _Widget;
	XE::AssetInstance< XE::AIModule > _AIModule;
};

#endif // AIDOCKWIDGET_H__969089A6_A79B_48B9_ADD9_14427FF60F87
