/*!
 * \file	MetaPlugin.h
 *
 * \author	ZhengYuanQing
 * \date	2020/03/19
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef METAPLUGIN_H__8DCA7F57_F655_461B_AC10_C5B03EE97645
#define METAPLUGIN_H__8DCA7F57_F655_461B_AC10_C5B03EE97645

#include "Global.h"

BEG_XE_NAMESPACE

class MetaPlugin : public XE::Plugin
{
public:
	MetaPlugin( XESFramework * framework );

	~MetaPlugin() override;

public:
	String GetName() const override;

public:
	void Startup() override;

	void Update() override;

	void Clearup() override;

};

END_XE_NAMESPACE

#endif // METAPLUGIN_H__8DCA7F57_F655_461B_AC10_C5B03EE97645
