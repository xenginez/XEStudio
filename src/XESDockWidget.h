/*!
 * \file	XESDockWidget.h
 *
 * \author	ZhengYuanQing
 * \date	2020/03/10
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef XESDOCKWIDGET_H__44205064_5257_47CA_A8A3_505232C3C35B
#define XESDOCKWIDGET_H__44205064_5257_47CA_A8A3_505232C3C35B

#include "Type.h"

class XES_API XESDockWidget : public QDockWidget
{
	Q_OBJECT

private:
	struct Private;

public:
	XESDockWidget( const QString & title, QWidget * parent = nullptr, Qt::WindowFlags flags = Qt::WindowFlags() );

	XESDockWidget( QWidget * parent = nullptr, Qt::WindowFlags flags = Qt::WindowFlags() );

	~XESDockWidget() override;

public:
	virtual void Save();

public:
	void Execute( const XESDockCmdPtr & cmd );

protected:
	void keyPressEvent( QKeyEvent * event ) override;

	bool event( QEvent * event ) override;

private:
	void TodoCMD( const XESDockCmdPtr & cmd );

	void UndoCMD( const XESDockCmdPtr & cmd );

private:
	Private * _p;
};

#endif // XESDOCKWIDGET_H__44205064_5257_47CA_A8A3_505232C3C35B
