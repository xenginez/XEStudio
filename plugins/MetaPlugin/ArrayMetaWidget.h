/*!
 * \file	ArrayMetaWidget.h
 *
 * \author	ZhengYuanQing
 * \date	2020/03/19
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef ARRAYMETAWIDGET_H__7AE70872_6034_4821_A82D_7BAB5359B68F
#define ARRAYMETAWIDGET_H__7AE70872_6034_4821_A82D_7BAB5359B68F

#include "Global.h"

QT_BEGIN_NAMESPACE
namespace Ui { class ArrayMetaWidget; }
QT_END_NAMESPACE

class ArrayMetaWidget : public XESMetaWidget
{
	Q_OBJECT

public:
	ArrayMetaWidget();

	~ArrayMetaWidget() override;

public:
	void Startup( const XE::Variant & val, const QString & tag ) override;

	XE::Variant OnUpdateVariant() override;

	void OnResetVariant( const XE::Variant & val ) override;

private:
	void OnPushButtonAddClicked();

	void OnPushButtonSubClicked();

private:
	Ui::ArrayMetaWidget * ui;
};
DECL_META_CLASS( DLL_EXPORT, ArrayMetaWidget );

#endif // ARRAYMETAWIDGET_H__7AE70872_6034_4821_A82D_7BAB5359B68F
