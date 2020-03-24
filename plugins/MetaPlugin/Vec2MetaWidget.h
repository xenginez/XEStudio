/*!
 * \file	Vec2MetaWidget.h
 *
 * \author	ZhengYuanQing
 * \date	2020/03/24
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef VEC2METAWIDGET_H__B3546172_F552_4F7C_B3BB_AE1AB4E6A6D3
#define VEC2METAWIDGET_H__B3546172_F552_4F7C_B3BB_AE1AB4E6A6D3

#include "Global.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Vec2MetaWidget; }
QT_END_NAMESPACE

class Vec2MetaWidget : public XESMetaWidget
{
	Q_OBJECT

public:
	Vec2MetaWidget();

	~Vec2MetaWidget() override;

public:
	void Startup( const XE::Variant & val, const QString & tag ) override;

	XE::Variant UpdateVariant() override;

public:
	Ui::Vec2MetaWidget * ui;
};
DECL_META_CLASS( DLL_EXPORT, Vec2MetaWidget );

#endif // VEC2METAWIDGET_H__B3546172_F552_4F7C_B3BB_AE1AB4E6A6D3
