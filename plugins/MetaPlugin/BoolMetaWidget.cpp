#include "BoolMetaWidget.h"

IMPLEMENT_META( BoolMetaWidget )

BoolMetaWidget::BoolMetaWidget()
{
	auto layout = new QVBoxLayout( this );
	layout->setSpacing( 0 );
	layout->setContentsMargins( 0, 0, 0, 0 );

	_Widget = new QCheckBox( this );
	layout->addWidget( _Widget );
}

BoolMetaWidget::~BoolMetaWidget()
{

}

void BoolMetaWidget::Startup( const XE::Variant & val, const QString & tag )
{
	XESMetaWidget::Startup( val, tag );

	_Widget->setChecked( val.ToBool() );
}

XE::Variant BoolMetaWidget::OnUpdateVariant()
{
	return _Widget->isChecked();
}

void BoolMetaWidget::OnResetVariant( const XE::Variant & val )
{
	XESMetaWidget::OnResetVariant( val );

	_Widget->setChecked( val.ToBool() );
}

