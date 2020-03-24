/*!
 * \file	BoolMetaWidget.h
 *
 * \author	ZhengYuanQing
 * \date	2020/03/19
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef BOOLMETAWIDGET_H__F4EC6B29_7A41_4143_AF6B_3E32E2F13BC4
#define BOOLMETAWIDGET_H__F4EC6B29_7A41_4143_AF6B_3E32E2F13BC4

#include "Global.h"

class BoolMetaWidget : public XESMetaWidget
{
	Q_OBJECT

public:
	BoolMetaWidget();

	~BoolMetaWidget() override;

public:
	void Startup( const XE::Variant & val, const QString & tag ) override;

	XE::Variant UpdateVariant() override;

private:
	QCheckBox * _Widget;
};
DECL_META_CLASS( DLL_EXPORT, BoolMetaWidget );

#endif // BOOLMETAWIDGET_H__F4EC6B29_7A41_4143_AF6B_3E32E2F13BC4
