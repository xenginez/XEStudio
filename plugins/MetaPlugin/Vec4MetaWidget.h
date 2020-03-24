/*!
 * \file	Vec4MetaWidget.h
 *
 * \author	ZhengYuanQing
 * \date	2020/03/24
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef VEC4METAWIDGET_H__81282219_A6AF_40C6_AA70_B61F6C23FEF9
#define VEC4METAWIDGET_H__81282219_A6AF_40C6_AA70_B61F6C23FEF9

#include "Global.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Vec4MetaWidget; }
QT_END_NAMESPACE

class Vec4MetaWidget : public XESMetaWidget
{
	Q_OBJECT

public:
	Vec4MetaWidget();

	~Vec4MetaWidget() override;

public:
	void Startup( const XE::Variant & val, const QString & tag ) override;

	XE::Variant UpdateVariant() override;

public:
	Ui::Vec4MetaWidget * ui;
};
DECL_META_CLASS( DLL_EXPORT, Vec4MetaWidget );

#endif // VEC4METAWIDGET_H__81282219_A6AF_40C6_AA70_B61F6C23FEF9
