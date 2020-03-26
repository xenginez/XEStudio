/*!
 * \file	AIPlugin.h
 *
 * \author	ZhengYuanQing
 * \date	2020/03/13
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef AIPLUGIN_H__DFA48E4F_6580_4CCE_9A74_579C43FA7C63
#define AIPLUGIN_H__DFA48E4F_6580_4CCE_9A74_579C43FA7C63

#include "Global.h"

BEG_XE_NAMESPACE

class AIPlugin : public XE::Plugin
{
public:
	AIPlugin( XESFramework * framework );

	~AIPlugin() override;

public:
	String GetName() const override;

public:
	void Startup() override;

	void Update() override;

	void Clearup() override;

private:
	XE::uint64 _Stub;
};

END_XE_NAMESPACE

#endif // AIPLUGIN_H__DFA48E4F_6580_4CCE_9A74_579C43FA7C63
