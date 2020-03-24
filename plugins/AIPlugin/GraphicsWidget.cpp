#include "GraphicsWidget.h"

#include "BTGraphicsScene.h"
#include "FSMGraphicsScene.h"

GraphicsWidget::GraphicsWidget( QWidget * parent /*= nullptr */ )
	:QWidget( parent ), _PropertyWidget( nullptr )
{
	auto verticalLayout = new QVBoxLayout( this );
	verticalLayout->setSpacing( 0 );
	verticalLayout->setContentsMargins( 0, 0, 0, 0 );

	_Splitter = new QSplitter( this );
	_Splitter->setOrientation( Qt::Horizontal );

	_View = new GraphicsView( this );
	_View->SetGraphicsWidget( this );
	_Splitter->addWidget( _View );

	verticalLayout->addWidget( _Splitter );
}


GraphicsWidget::~GraphicsWidget()
{

}

const XE::AIModulePtr & GraphicsWidget::GetAIModule() const
{
	return _AIModule;
}

void GraphicsWidget::SetAIModule( const XE::AIModulePtr & val )
{
	_AIModule = val;

	if( _AIModule->GetMetaClass()->CanConvert( XE::ClassID<XE::StateMachine>::Get() ) )
	{
		_Scene = new FSMGraphicsScene( _View );
	}
	else if( _AIModule->GetMetaClass()->CanConvert( XE::ClassID<XE::BehaviorTree>::Get() ) )
	{
		_Scene = new BTGraphicsScene( _View );
	}

	_Scene->SetGraphicsView( _View );
	_View->setScene( _Scene );

	_Scene->ResetGraphics();
	 
	_BlockBoardWidget = XE::XESFramework::GetCurrentFramework()->GetServiceT<XE::XESMetaService>()->CreateMetaWidget( _AIModule->GetKeys() );
	_Splitter->insertWidget( 0, _BlockBoardWidget );
	_Splitter->setStretchFactor( 0, 4 );
	_Splitter->setStretchFactor( 1, 6 );
}

void GraphicsWidget::ShowProperty( const XE::ObjectPtr & val )
{
	if( _PropertyWidget )
	{
		_PropertyWidget->deleteLater();
		_PropertyWidget = nullptr;
		_Property = nullptr;
	}

	if( val != nullptr )
	{
		_Property = val;
		_PropertyWidget = XE::XESFramework::GetCurrentFramework()->GetServiceT<XE::XESMetaService>()->CreateMetaWidget( val );

		_Splitter->addWidget( _PropertyWidget );
		_Splitter->setStretchFactor( 0, 4 );
		_Splitter->setStretchFactor( 1, 6 );
		_Splitter->setStretchFactor( 2, 4 );
		_Splitter->update();
	}
}

void GraphicsWidget::Save()
{
	if( _BlockBoardWidget )
	{
		GetAIModule()->SetKeys( _BlockBoardWidget->UpdateVariant().Value<XE::Map<XE::String, XE::Variant>>() );
	}

	if( _Property && _PropertyWidget )
	{
		_PropertyWidget->UpdateVariant();

		_Property->GetMetaClass()->VisitProperty( [this]( XE::IMetaPropertyPtr prop )
												  {
													  if( !( prop->GetFlag() & XE::IMetaProperty::NoDesign ) )
													  {
														  auto v = _PropertyWidget->GetVariant();

														  prop->Set( _Property, prop->Get( v ) );
													  }
												  } );
	}
}
