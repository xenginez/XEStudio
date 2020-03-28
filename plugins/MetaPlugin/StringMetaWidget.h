/*!
 * \file	StringMetaWidget.h
 *
 * \author	ZhengYuanQing
 * \date	2020/03/19
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef STRINGMETAWIDGET_H__2DD8EC90_B2A1_4A9B_9C7C_5E0176FE3600
#define STRINGMETAWIDGET_H__2DD8EC90_B2A1_4A9B_9C7C_5E0176FE3600

#include "Global.h"

class StringMetaWidget : public XESMetaWidget
{
	Q_OBJECT

public:
	StringMetaWidget();

	~StringMetaWidget() override;

public:
	void Startup( const XE::Variant & val, const QString & tag ) override;

	XE::Variant OnUpdateVariant() override;

	void OnResetVariant( const XE::Variant & val ) override;

public:
	QLineEdit * _Widget;
};
DECL_META_CLASS( DLL_EXPORT, StringMetaWidget );

#endif // STRINGMETAWIDGET_H__2DD8EC90_B2A1_4A9B_9C7C_5E0176FE3600
