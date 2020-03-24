/*!
 * \file	Type.h
 *
 * \author	ZhengYuanQing
 * \date	2020/03/10
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef TYPE_H__50F0EDDE_3E7A_4617_B83D_D88B16A41674
#define TYPE_H__50F0EDDE_3E7A_4617_B83D_D88B16A41674

#include "Global.h"

BEG_XE_NAMESPACE

class XESFramework;

struct XES_API XESCMD
{
	std::function<void()> Todo;
	std::function<void()> Undo;
};

END_XE_NAMESPACE

class XESMainWindow;
class XESMetaWidget;
class ProMainWindow;
class ProListWidgetItem;

#endif // TYPE_H__50F0EDDE_3E7A_4617_B83D_D88B16A41674