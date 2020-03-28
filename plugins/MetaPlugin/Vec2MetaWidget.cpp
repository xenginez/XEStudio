#include "Vec2MetaWidget.h"
#include "ui_Vec2MetaWidget.h"


Vec2MetaWidget::Vec2MetaWidget()
	:ui( new Ui::Vec2MetaWidget )
{
	ui->setupUi( this );
}

Vec2MetaWidget::~Vec2MetaWidget()
{
	delete ui;
}

void Vec2MetaWidget::Startup( const XE::Variant & val, const QString & tag )
{
	XESMetaWidget::Startup( val, tag );

	ui->doubleSpinBoxX->setMinimum( GetTag( "min", "0.00" ).toDouble() );
	ui->doubleSpinBoxX->setMaximum( GetTag( "max", "999999.99" ).toDouble() );
	ui->doubleSpinBoxX->setDecimals( GetTag( "decimals", "2" ).toInt() );
	ui->doubleSpinBoxY->setMinimum( GetTag( "min", "0.00" ).toDouble() );
	ui->doubleSpinBoxY->setMaximum( GetTag( "max", "999999.99" ).toDouble() );
	ui->doubleSpinBoxY->setDecimals( GetTag( "decimals", "2" ).toInt() );

	auto v2 = val.Value<XE::Vec2>();

	ui->doubleSpinBoxX->setValue( v2.x );
	ui->doubleSpinBoxY->setValue( v2.y );
}
XE::Variant Vec2MetaWidget::OnUpdateVariant()
{
	XE::Vec2 v2;

	v2.x = ui->doubleSpinBoxX->value();
	v2.y = ui->doubleSpinBoxY->value();

	return v2;
}

void Vec2MetaWidget::OnResetVariant( const XE::Variant & val )
{
	XESMetaWidget::OnResetVariant( val );

	auto v2 = val.Value<XE::Vec2>();

	ui->doubleSpinBoxX->setValue( v2.x );
	ui->doubleSpinBoxY->setValue( v2.y );
}

