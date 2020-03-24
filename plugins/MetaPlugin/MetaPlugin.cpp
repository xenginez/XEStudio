#include "MetaPlugin.h"

USING_XE

MetaPlugin::MetaPlugin( XESFramework * framework )
	:Plugin( framework )
{

}

MetaPlugin::~MetaPlugin()
{

}

XE::String MetaPlugin::GetName() const
{
	return "MetaPlugin";
}

void MetaPlugin::Startup()
{

}

void MetaPlugin::Update()
{

}

void MetaPlugin::Clearup()
{

}


REGISTER_PLUGIN( MetaPlugin );