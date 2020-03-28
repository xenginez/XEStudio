/*!
 * \file	QuatMetaWidget.h
 *
 * \author	ZhengYuanQing
 * \date	2020/03/24
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef QUATMETAWIDGET_H__C7E926B3_A757_4F6F_8AA7_D3192C0F37E9
#define QUATMETAWIDGET_H__C7E926B3_A757_4F6F_8AA7_D3192C0F37E9

#include "Global.h"

QT_BEGIN_NAMESPACE
namespace Ui { class QuatMetaWidget; }
QT_END_NAMESPACE

class QuatMetaWidget : public XESMetaWidget
{
	Q_OBJECT

public:
	QuatMetaWidget();

	~QuatMetaWidget() override;

public:
	void Startup( const XE::Variant & val, const QString & tag ) override;

	XE::Variant OnUpdateVariant() override;

	void OnResetVariant( const XE::Variant & val ) override;

public:
	Ui::QuatMetaWidget * ui;
};
DECL_META_CLASS( DLL_EXPORT, QuatMetaWidget );

#endif // QUATMETAWIDGET_H__C7E926B3_A757_4F6F_8AA7_D3192C0F37E9
