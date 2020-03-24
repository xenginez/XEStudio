/*!
 * \file	XESApplication.h
 *
 * \author	ZhengYuanQing
 * \date	2020/03/13
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef XESAPPLICATION_H__5FA6ACB1_CB35_4283_86E6_CA06E766013C
#define XESAPPLICATION_H__5FA6ACB1_CB35_4283_86E6_CA06E766013C

#include "Global.h"

class XESApplication : public QApplication
{
	Q_OBJECT

public:
	XESApplication( int & argc, char ** argv );

	~XESApplication() override;

public:
	bool notify( QObject * obj, QEvent * event ) override;

};

#endif // XESAPPLICATION_H__5FA6ACB1_CB35_4283_86E6_CA06E766013C
