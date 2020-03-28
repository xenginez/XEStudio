/*!
 * \file	IntgerMetaWidget.h
 *
 * \author	ZhengYuanQing
 * \date	2020/03/19
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef INTGERMETAWIDGET_H__0262B1B5_2456_46D3_B4F2_FF8A401E1EC8
#define INTGERMETAWIDGET_H__0262B1B5_2456_46D3_B4F2_FF8A401E1EC8

#include "Global.h"

class IntgerMetaWidget : public XESMetaWidget
{
	Q_OBJECT

public:
	IntgerMetaWidget();

	~IntgerMetaWidget() override;

public:
	void Startup( const XE::Variant & val, const QString & tag ) override;

	XE::Variant OnUpdateVariant() override;

	void OnResetVariant( const XE::Variant & val ) override;

private:
	QSpinBox * _Widget;
};
DECL_META_CLASS( DLL_EXPORT, IntgerMetaWidget );

#endif // INTGERMETAWIDGET_H__0262B1B5_2456_46D3_B4F2_FF8A401E1EC8
