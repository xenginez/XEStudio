/*!
 * \file	XESMainWindow.h
 *
 * \author	ZhengYuanQing
 * \date	2020/03/10
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef XESMAINWINDOW_H__69FF9AB4_7EBE_4162_B9A7_CEC1A9F76829
#define XESMAINWINDOW_H__69FF9AB4_7EBE_4162_B9A7_CEC1A9F76829

#include "Type.h"

class XES_API XESMainWindow : public QMainWindow
{
	Q_OBJECT

public:
	XESMainWindow( QWidget * parent = nullptr );

	~XESMainWindow();

public:
	void Save();

	void ResizeDocks();

};

#endif // XESMAINWINDOW_H__69FF9AB4_7EBE_4162_B9A7_CEC1A9F76829
