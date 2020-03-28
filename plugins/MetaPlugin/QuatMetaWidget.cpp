#include "QuatMetaWidget.h"
#include "ui_QuatMetaWidget.h"


QuatMetaWidget::QuatMetaWidget()
	:ui( new Ui::QuatMetaWidget )
{
	ui->setupUi( this );
}

QuatMetaWidget::~QuatMetaWidget()
{
	delete ui;
}

void QuatMetaWidget::Startup( const XE::Variant & val, const QString & tag )
{
	XESMetaWidget::Startup( val, tag );

	ui->doubleSpinBoxX->setMinimum( 0 );
	ui->doubleSpinBoxX->setMaximum( 360 );
	ui->doubleSpinBoxX->setDecimals( 2 );

	ui->doubleSpinBoxY->setMinimum( 0 );
	ui->doubleSpinBoxY->setMaximum( 360 );
	ui->doubleSpinBoxY->setDecimals( 2 );

	ui->doubleSpinBoxZ->setMinimum( 0 );
	ui->doubleSpinBoxZ->setMaximum( 360 );
	ui->doubleSpinBoxZ->setDecimals( 2 );

	auto q = val.Value<XE::Quat>();
	XE::Vec3 e;
	XE::Mathf::QuatToEuler( q, e );

	ui->doubleSpinBoxX->setValue( e.x );
	ui->doubleSpinBoxY->setValue( e.y );
	ui->doubleSpinBoxZ->setValue( e.z );
}
XE::Variant QuatMetaWidget::OnUpdateVariant()
{
	XE::Vec3 e;

	e.x = ui->doubleSpinBoxX->value();
	e.y = ui->doubleSpinBoxY->value();
	e.z = ui->doubleSpinBoxZ->value();

	return XE::Mathf::QuatFromEuler( e );
}

void QuatMetaWidget::OnResetVariant( const XE::Variant & val )
{
	XESMetaWidget::OnResetVariant( val );

	auto q = val.Value<XE::Quat>();
	XE::Vec3 e;
	XE::Mathf::QuatToEuler( q, e );

	ui->doubleSpinBoxX->setValue( e.x );
	ui->doubleSpinBoxY->setValue( e.y );
	ui->doubleSpinBoxZ->setValue( e.z );
}

