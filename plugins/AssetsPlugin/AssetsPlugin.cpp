#include "AssetsPlugin.h"

#include "AssetsDockWidget.h"

USING_XE

AssetsPlugin::AssetsPlugin( XESFramework * framework )
	:Plugin( framework )
{

}

AssetsPlugin::~AssetsPlugin()
{

}

XE::String AssetsPlugin::GetName() const
{
	return "AssetsPlugin";
}

void AssetsPlugin::Startup()
{
	auto widget = new AssetsDockWidget( GetFramework()->GetMainWindow() );
	GetFramework()->GetMainWindow()->addDockWidget( Qt::DockWidgetArea::BottomDockWidgetArea, widget );
}

void AssetsPlugin::Update()
{

}

void AssetsPlugin::Clearup()
{

}


REGISTER_PLUGIN( AssetsPlugin );