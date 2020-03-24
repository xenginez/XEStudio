#include "PairMetaWidget.h"

IMPLEMENT_META( PairMetaWidget )

PairMetaWidget::PairMetaWidget()
{
	auto layout = new QVBoxLayout( this );
	layout->setSpacing( 0 );
	layout->setContentsMargins( 0, 0, 0, 0 );

	_Widget = new QTreeWidget( this );
	_Widget->setHeaderHidden( true );
	layout->addWidget( _Widget );
}

PairMetaWidget::~PairMetaWidget()
{

}

void PairMetaWidget::Startup( const XE::Variant & val, const QString & tag )
{
	XESMetaWidget::Startup( val, tag );

	auto pair = val.Value<XE::VariantPair>();

	if( pair.first.IsInvalid() && GetTag( "key_type" ) != "" )
	{
		pair.first = XE::Reflection::FindClass( GetTag( "key_type" ).toStdString() )->ConstructPtr();
	}
	auto key_item = new QTreeWidgetItem( _Widget );
	key_item->setText( 0, "key" );
	_KeyWidget = XE::XESFramework::GetCurrentFramework()->GetServiceT<XE::XESMetaService>()->CreateMetaWidget( pair.first );
	auto item = new QTreeWidgetItem( key_item );
	item->setSizeHint( 0, _KeyWidget->sizeHint() );
	_Widget->setItemWidget( item, 0, _KeyWidget );

	if( pair.first.IsInvalid() && GetTag( "value_type" ) != "" )
	{
		pair.second = XE::Reflection::FindClass( GetTag( "value_type" ).toStdString() )->ConstructPtr();
	}
	auto value_item = new QTreeWidgetItem( _Widget );
	value_item->setText( 0, "value" );
	_ValueWidget = XE::XESFramework::GetCurrentFramework()->GetServiceT<XE::XESMetaService>()->CreateMetaWidget( pair.second );
	item = new QTreeWidgetItem( value_item );
	item->setSizeHint( 0, _ValueWidget->sizeHint() );
	_Widget->setItemWidget( item, 0, _ValueWidget );
}

XE::Variant PairMetaWidget::UpdateVariant()
{
	XE::VariantPair pair;
	pair.first = _KeyWidget->UpdateVariant();
	pair.second = _ValueWidget->UpdateVariant();

	SetVariant( pair );

	return GetVariant();
}
