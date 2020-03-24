/*!
 * \file	SelectTypeMetaWidget.h
 *
 * \author	ZhengYuanQing
 * \date	2020/03/19
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef SELECTTYPEMETAWIDGET_H__2D4B5396_D429_4893_B3B9_30FA44FB9C7A
#define SELECTTYPEMETAWIDGET_H__2D4B5396_D429_4893_B3B9_30FA44FB9C7A

#include "Global.h"

class SelectTypeMetaWidget : public XESMetaWidget
{
	Q_OBJECT

public:
	SelectTypeMetaWidget();

	~SelectTypeMetaWidget() override;

public:
	void Startup( const XE::Variant & val, const QString & tag ) override;

	XE::Variant UpdateVariant() override;

private:
	void VisitClass( const XE::IMetaClassPtr & val );

private:
	QVBoxLayout * _Layout;
	QComboBox * _ComboBox;
	XESMetaWidget * _Widget;
};
DECL_META_CLASS( DLL_EXPORT, SelectTypeMetaWidget );

#endif // SELECTTYPEMETAWIDGET_H__2D4B5396_D429_4893_B3B9_30FA44FB9C7A
