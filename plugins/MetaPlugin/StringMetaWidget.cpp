#include "StringMetaWidget.h"

IMPLEMENT_META( StringMetaWidget )

StringMetaWidget::StringMetaWidget()
{
	auto layout = new QVBoxLayout( this );
	layout->setSpacing( 0 );
	layout->setContentsMargins( 0, 0, 0, 0 );

	_Widget = new QLineEdit( this );
	layout->addWidget( _Widget );
}

StringMetaWidget::~StringMetaWidget()
{

}

void StringMetaWidget::Startup( const XE::Variant & val, const QString & tag )
{
	XESMetaWidget::Startup( val, tag );

	_Widget->setPlaceholderText( GetTag( "placeholder" ) );

	_Widget->setText( QString::fromUtf8( val.Value<XE::String>().ToCString() ) );
}

XE::Variant StringMetaWidget::UpdateVariant()
{
	SetVariant( _Widget->text().toStdString() );

	return GetVariant();
}
