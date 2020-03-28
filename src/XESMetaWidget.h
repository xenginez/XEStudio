/*!
 * \file	XESMetaWidget.h
 *
 * \author	ZhengYuanQing
 * \date	2020/03/19
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef XESMETAWIDGET_H__6ABC4B24_A872_4A92_A55A_B1A11270AF6F
#define XESMETAWIDGET_H__6ABC4B24_A872_4A92_A55A_B1A11270AF6F

#include "Type.h"

class XES_API XESMetaWidget : public QWidget
{
	Q_OBJECT

public:
	XESMetaWidget();

	~XESMetaWidget() override;

Q_SIGNALS:
	void ResetVariant( const XE::Variant & val );

public:
	virtual void Startup( const XE::Variant & val, const QString & tag );

	virtual XE::Variant UpdateVariant();

	virtual XE::Variant OnUpdateVariant() = 0;

	virtual void OnResetVariant( const XE::Variant & val );

public:
	XE::Variant GetVariant() const;

	void SetVariant( const XE::Variant & val );

protected:
	QString GetTag( const QString & val, const QString & def = "" ) const;

private:
	XESDockWidget * GetDockWidget() const;

private:
	XE::Variant _Value;
	QMap<QString, QString> _Tags;
	QMap<QString, XESMetaWidget *> _Props;
};
DECL_META_CLASS( XES_API, XESMetaWidget );

class XES_API XESEnumMetaWidget : public XESMetaWidget
{
	Q_OBJECT

public:
	XESEnumMetaWidget();

	~XESEnumMetaWidget() override;

public:
	void Startup( const XE::Variant & val, const QString & tag ) override;

	XE::Variant OnUpdateVariant() override;

	void OnResetVariant( const XE::Variant & val ) override;

private:
	QComboBox * _Widget;
};
DECL_META_CLASS( XES_API, XESEnumMetaWidget );

class XES_API XESClassMetaWidget : public XESMetaWidget
{
	Q_OBJECT

public:
	XESClassMetaWidget();

	~XESClassMetaWidget() override;

public:
	void Startup( const XE::Variant & val, const QString & tag ) override;

	XE::Variant OnUpdateVariant() override;

	void OnResetVariant( const XE::Variant & val ) override;

private:
	void AddProperty( const XE::IMetaPropertyPtr & val );

private:
	QTableWidget * _Widget;
	QMap<QString, XESMetaWidget *> _Props;
};
DECL_META_CLASS( XES_API, XESClassMetaWidget );

#endif // XESMETAWIDGET_H__6ABC4B24_A872_4A92_A55A_B1A11270AF6F
