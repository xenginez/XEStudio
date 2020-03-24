/*!
 * \file	PairMetaWidget.h
 *
 * \author	ZhengYuanQing
 * \date	2020/03/19
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef PAIRMETAWIDGET_H__BECA44DB_AD5C_4BC0_9D3A_9D050C847DB4
#define PAIRMETAWIDGET_H__BECA44DB_AD5C_4BC0_9D3A_9D050C847DB4

#include "Global.h"

class PairMetaWidget : public XESMetaWidget
{
	Q_OBJECT

public:
	PairMetaWidget();

	~PairMetaWidget() override;

public:
	void Startup( const XE::Variant & val, const QString & tag ) override;

	XE::Variant UpdateVariant() override;

private:
	QTreeWidget * _Widget;
	XESMetaWidget * _KeyWidget;
	XESMetaWidget * _ValueWidget;
};
DECL_META_CLASS( DLL_EXPORT, PairMetaWidget );

#endif // PAIRMETAWIDGET_H__BECA44DB_AD5C_4BC0_9D3A_9D050C847DB4
