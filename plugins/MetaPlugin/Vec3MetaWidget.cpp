#include "Vec3MetaWidget.h"
#include "ui_Vec3MetaWidget.h"


Vec3MetaWidget::Vec3MetaWidget()
	:ui( new Ui::Vec3MetaWidget )
{
	ui->setupUi( this );
}

Vec3MetaWidget::~Vec3MetaWidget()
{
	delete ui;
}

void Vec3MetaWidget::Startup( const XE::Variant & val, const QString & tag )
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

	auto v3 = val.Value<XE::Vec3>();

	ui->doubleSpinBoxX->setValue( v3.x );
	ui->doubleSpinBoxY->setValue( v3.y );
	ui->doubleSpinBoxZ->setValue( v3.z );
}
XE::Variant Vec3MetaWidget::OnUpdateVariant()
{
	XE::Vec3 v3;

	v3.x = ui->doubleSpinBoxX->value();
	v3.y = ui->doubleSpinBoxY->value();
	v3.z = ui->doubleSpinBoxZ->value();

	return v3;
}

void Vec3MetaWidget::OnResetVariant( const XE::Variant & val )
{
	XESMetaWidget::OnResetVariant( val );

	auto v3 = val.Value<XE::Vec3>();

	ui->doubleSpinBoxX->setValue( v3.x );
	ui->doubleSpinBoxY->setValue( v3.y );
	ui->doubleSpinBoxZ->setValue( v3.z );
}

