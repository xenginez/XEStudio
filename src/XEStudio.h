/*!
 * \file	XEStudio.h
 *
 * \author	ZhengYuanQing
 * \date	2020/03/10
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef XESTUDIO_H__F05CFA6A_14CD_45DF_8C43_73606FD473BF
#define XESTUDIO_H__F05CFA6A_14CD_45DF_8C43_73606FD473BF

#include "Event.h"
#include "XESDockCmd.h"
#include "XESFramework.h"
#include "XESDockWidget.h"
#include "XESMainWindow.h"
#include "XESMetaWidget.h"
#include "XESMetaService.h"
#include "XESAssetsService.h"
#include "XESPluginService.h"


#define REGISTER_PLUGIN( NAME ) \
extern "C" DLL_EXPORT XE::Plugin * RegisterPlugin( XE::XESFramework * framework ) \
{ \
	return new NAME( framework ); \
} \
extern "C" DLL_EXPORT void UnregisterPlugin( XE::Plugin * plugin ) \
{ \
	delete plugin; \
}

#endif // XESTUDIO_H__F05CFA6A_14CD_45DF_8C43_73606FD473BF
