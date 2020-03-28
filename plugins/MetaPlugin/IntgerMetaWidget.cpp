#include "IntgerMetaWidget.h"

IMPLEMENT_META( IntgerMetaWidget )


IntgerMetaWidget::IntgerMetaWidget()
{
	auto layout = new QVBoxLayout( this );
	layout->setSpacing( 0 );
	layout->setContentsMargins( 0, 0, 0, 0 );

	_Widget = new QSpinBox( this );
	layout->addWidget( _Widget );
}

IntgerMetaWidget::~IntgerMetaWidget()
{

}

void IntgerMetaWidget::Startup( const XE::Variant & val, const QString & tag )
{
	XESMetaWidget::Startup( val, tag );

	_Widget->setMinimum( GetTag( "min", "0" ).toInt() );
	_Widget->setMaximum( GetTag( "max", "99999999" ).toInt() );
	_Widget->setSingleStep( GetTag( "step", "1" ).toInt() );

	_Widget->setValue( val.ToInt32() );
}
XE::Variant IntgerMetaWidget::OnUpdateVariant()
{
	return _Widget->value();
}

void IntgerMetaWidget::OnResetVariant( const XE::Variant & val )
{
	XESMetaWidget::OnResetVariant( val );

	_Widget->setValue( val.ToInt32() );
}

