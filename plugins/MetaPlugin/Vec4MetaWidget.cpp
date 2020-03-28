#include "Vec4MetaWidget.h"
#include "ui_Vec4MetaWidget.h"


Vec4MetaWidget::Vec4MetaWidget()
	:ui( new Ui::Vec4MetaWidget )
{
	ui->setupUi( this );
}

Vec4MetaWidget::~Vec4MetaWidget()
{
	delete ui;
}

void Vec4MetaWidget::Startup( const XE::Variant & val, const QString & tag )
{
	XESMetaWidget::Startup( val, tag );

	ui->doubleSpinBoxX->setMinimum( GetTag( "min", "0.00" ).toDouble() );
	ui->doubleSpinBoxX->setMaximum( GetTag( "max", "999999.99" ).toDouble() );
	ui->doubleSpinBoxX->setDecimals( GetTag( "decimals", "2" ).toInt() );

	ui->doubleSpinBoxY->setMinimum( GetTag( "min", "0.00" ).toDouble() );
	ui->doubleSpinBoxY->setMaximum( GetTag( "max", "999999.99" ).toDouble() );
	ui->doubleSpinBoxY->setDecimals( GetTag( "decimals", "2" ).toInt() );

	ui->doubleSpinBoxZ->setMinimum( GetTag( "min", "0.00" ).toDouble() );
	ui->doubleSpinBoxZ->setMaximum( GetTag( "max", "999999.99" ).toDouble() );
	ui->doubleSpinBoxZ->setDecimals( GetTag( "decimals", "2" ).toInt() );

	ui->doubleSpinBoxW->setMinimum( GetTag( "min", "0.00" ).toDouble() );
	ui->doubleSpinBoxW->setMaximum( GetTag( "max", "999999.99" ).toDouble() );
	ui->doubleSpinBoxW->setDecimals( GetTag( "decimals", "2" ).toInt() );

	auto v4 = val.Value<XE::Vec4>();

	ui->doubleSpinBoxX->setValue( v4.x );
	ui->doubleSpinBoxY->setValue( v4.y );
	ui->doubleSpinBoxZ->setValue( v4.z );
	ui->doubleSpinBoxW->setValue( v4.w );
}
XE::Variant Vec4MetaWidget::OnUpdateVariant()
{
	XE::Vec4 v4;

	v4.x = ui->doubleSpinBoxX->value();
	v4.y = ui->doubleSpinBoxY->value();
	v4.z = ui->doubleSpinBoxZ->value();
	v4.w = ui->doubleSpinBoxW->value();

	return v4;
}

void Vec4MetaWidget::OnResetVariant( const XE::Variant & val )
{
	XESMetaWidget::OnResetVariant( val );

	auto v4 = val.Value<XE::Vec4>();

	ui->doubleSpinBoxX->setValue( v4.x );
	ui->doubleSpinBoxY->setValue( v4.y );
	ui->doubleSpinBoxZ->setValue( v4.z );
	ui->doubleSpinBoxW->setValue( v4.w );
}

