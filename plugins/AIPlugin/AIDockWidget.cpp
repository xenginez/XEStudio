#include "AIDockWidget.h"

#include "GraphicsWidget.h"

AIDockWidget::AIDockWidget( QWidget * parent /*= nullptr*/, Qt::WindowFlags flags /*= Qt::WindowFlags() */ )
	:XESDockWidget( "AIPluginWidget", parent, flags )
{
	_Widget = new GraphicsWidget( this );

	setWidget( _Widget );

	setAllowedAreas( Qt::DockWidgetArea::TopDockWidgetArea );
}

AIDockWidget::~AIDockWidget()
{

}

void AIDockWidget::SetAssetPath( const XE::String & val )
{
	_AIModule = XE::AssetInstance< XE::AIModule >( val );

	_Widget->SetAIModule( _AIModule.get_shared() );
}

void AIDockWidget::Save()
{
	XESDockWidget::Save();

	XE::XESFramework::GetCurrentFramework()->GetServiceT<XE::XESAssetsService>()->SaveAsset( _AIModule.GetPath(), _AIModule.get_shared() );
}
