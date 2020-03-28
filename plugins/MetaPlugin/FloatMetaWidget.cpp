#include "FloatMetaWidget.h"

IMPLEMENT_META( FloatMetaWidget )

FloatMetaWidget::FloatMetaWidget()
{
	auto layout = new QVBoxLayout( this );
	layout->setSpacing( 0 );
	layout->setContentsMargins( 0, 0, 0, 0 );

	_Widget = new QDoubleSpinBox( this );
	layout->addWidget( _Widget );
}

FloatMetaWidget::~FloatMetaWidget()
{

}

void FloatMetaWidget::Startup( const XE::Variant & val, const QString & tag )
{
	XESMetaWidget::Startup( val, tag );

	_Widget->setMinimum( GetTag( "min", "0.00" ).toDouble() );
	_Widget->setMaximum( GetTag( "max", "999999.99" ).toDouble() );
	_Widget->setDecimals( GetTag( "decimals", "2" ).toInt() );

	_Widget->setValue( val.ToFloat64() );
}
XE::Variant FloatMetaWidget::OnUpdateVariant()
{
	return _Widget->value();
}

void FloatMetaWidget::OnResetVariant( const XE::Variant & val )
{
	XESMetaWidget::OnResetVariant( val );

	_Widget->setValue( val.ToFloat64() );
}

