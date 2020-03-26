#include "AIPlugin.h"

#include "AIDockWidget.h"

USING_XE

AIPlugin::AIPlugin( XESFramework * framework )
	:Plugin( framework ), _Stub( 0 )
{

}

AIPlugin::~AIPlugin()
{

}

XE::String AIPlugin::GetName() const
{
	return "AIPlugin";
}

void AIPlugin::Startup()
{
	_Stub = GetFramework()->GetEventService()->RegisterListener( XE::OPEN_ASSET_AI, []( EventPtr event )
														 {
															 auto widget = new AIDockWidget( XE::XESFramework::GetCurrentFramework()->GetMainWindow() );
															 widget->SetAssetPath( event->parameter.Value<XE::String>() );
															 XE::XESFramework::GetCurrentFramework()->GetMainWindow()->addDockWidget( Qt::DockWidgetArea::TopDockWidgetArea, widget );
															 XE::XESFramework::GetCurrentFramework()->GetMainWindow()->ResizeDocks();
														 } );
}

void AIPlugin::Update()
{
	
}

void AIPlugin::Clearup()
{
	GetFramework()->GetEventService()->UnregisterListener( XE::OPEN_ASSET_AI, _Stub );
}


REGISTER_PLUGIN( AIPlugin );