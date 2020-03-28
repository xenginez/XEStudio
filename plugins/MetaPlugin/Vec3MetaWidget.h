/*!
 * \file	Vec3MetaWidget.h
 *
 * \author	ZhengYuanQing
 * \date	2020/03/24
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef VEC3METAWIDGET_H__603CA0C5_7DA7_49E4_B6E5_C17FEE5A2F58
#define VEC3METAWIDGET_H__603CA0C5_7DA7_49E4_B6E5_C17FEE5A2F58

#include "Global.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Vec3MetaWidget; }
QT_END_NAMESPACE

class Vec3MetaWidget : public XESMetaWidget
{
	Q_OBJECT

public:
	Vec3MetaWidget();

	~Vec3MetaWidget() override;

public:
	void Startup( const XE::Variant & val, const QString & tag ) override;

	XE::Variant OnUpdateVariant() override;

	void OnResetVariant( const XE::Variant & val ) override;

public:
	Ui::Vec3MetaWidget * ui;
};
DECL_META_CLASS( DLL_EXPORT, Vec3MetaWidget );

#endif // VEC3METAWIDGET_H__603CA0C5_7DA7_49E4_B6E5_C17FEE5A2F58
