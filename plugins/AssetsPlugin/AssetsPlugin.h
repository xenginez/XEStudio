/*!
 * \file	AssetsPlugin.h
 *
 * \author	ZhengYuanQing
 * \date	2020/03/11
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef ASSETSPLUGIN_H__3F30E0EB_86B6_4A65_B427_90339DAD35B2
#define ASSETSPLUGIN_H__3F30E0EB_86B6_4A65_B427_90339DAD35B2

#include "Global.h"

BEG_XE_NAMESPACE

class AssetsPlugin : public XE::Plugin
{
public:
	AssetsPlugin( XESFramework * framework );

	~AssetsPlugin() override;

public:
	String GetName() const override;

public:
	void Startup() override;

	void Update() override;

	void Clearup() override;

};


END_XE_NAMESPACE

#endif // ASSETSPLUGIN_H__3F30E0EB_86B6_4A65_B427_90339DAD35B2
