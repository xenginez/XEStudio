/*!
 * \file	FloatMetaWidget.h
 *
 * \author	ZhengYuanQing
 * \date	2020/03/19
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef FLOATMETAWIDGET_H__C31F5977_6ADA_4782_938D_FE096567B91C
#define FLOATMETAWIDGET_H__C31F5977_6ADA_4782_938D_FE096567B91C

#include "Global.h"

class FloatMetaWidget : public XESMetaWidget
{
	Q_OBJECT

public:
	FloatMetaWidget();

	~FloatMetaWidget() override;

public:
	void Startup( const XE::Variant & val, const QString & tag ) override;

	XE::Variant UpdateVariant() override;

private:
	QDoubleSpinBox * _Widget;
};
DECL_META_CLASS( DLL_EXPORT, FloatMetaWidget );

#endif // FLOATMETAWIDGET_H__C31F5977_6ADA_4782_938D_FE096567B91C
