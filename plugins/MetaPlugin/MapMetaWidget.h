/*!
 * \file	MapMetaWidget.h
 *
 * \author	ZhengYuanQing
 * \date	2020/03/20
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef MAPMETAWIDGET_H__3D9C3705_ECB9_46D4_8E94_D85B65CFB341
#define MAPMETAWIDGET_H__3D9C3705_ECB9_46D4_8E94_D85B65CFB341

#include "Global.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MapMetaWidget; }
QT_END_NAMESPACE

class MapMetaWidget : public XESMetaWidget
{
	Q_OBJECT

public:
	MapMetaWidget();

	~MapMetaWidget() override;

public:
	void Startup( const XE::Variant & val, const QString & tag ) override;

	XE::Variant UpdateVariant() override;

private:
	void OnPushButtonAddClicked();

	void OnPushButtonSubClicked();

private:
	void AddItem( const XE::VariantPair & pair );

private:
	Ui::MapMetaWidget * ui;
};
DECL_META_CLASS( DLL_EXPORT, MapMetaWidget );

#endif // MAPMETAWIDGET_H__3D9C3705_ECB9_46D4_8E94_D85B65CFB341
