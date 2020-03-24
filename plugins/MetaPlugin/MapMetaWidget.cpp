#include "MapMetaWidget.h"
#include "ui_MapMetaWidget.h"
 
#include "PairMetaWidget.h"

IMPLEMENT_META( MapMetaWidget )

MapMetaWidget::MapMetaWidget()
	:ui( new Ui::MapMetaWidget )
{
	ui->setupUi( this );

	connect( ui->pushButtonAdd, &QPushButton::clicked, this, &MapMetaWidget::OnPushButtonAddClicked );
	connect( ui->pushButtonSub, &QPushButton::clicked, this, &MapMetaWidget::OnPushButtonSubClicked );
}

MapMetaWidget::~MapMetaWidget()
{
	delete ui;
}

void MapMetaWidget::Startup( const XE::Variant & val, const QString & tag )
{
	XESMetaWidget::Startup( val, tag );

 	auto arr = val.Value<XE::VariantMap>();
 
 	for( const auto & var : arr )
 	{
		AddItem( var );
 	}
}

XE::Variant MapMetaWidget::UpdateVariant()
{
	XE::VariantMap map;

	for( int i = 0; i < ui->tableWidget->rowCount(); ++i )
	{
		XE::VariantPair pair;

		pair.first = ( (XESMetaWidget * )ui->tableWidget->cellWidget( i, 0 ) )->UpdateVariant();
		pair.second = ( (XESMetaWidget * )ui->tableWidget->cellWidget( i, 1 ) )->UpdateVariant();

		map.insert( pair );
	}

	SetVariant( map );

	return GetVariant();
}

void MapMetaWidget::OnPushButtonAddClicked()
{
	XE::VariantPair var;

	AddItem( var );
}

void MapMetaWidget::OnPushButtonSubClicked()
{
	ui->tableWidget->removeRow( ui->tableWidget->currentRow() );
}

void MapMetaWidget::AddItem( const XE::VariantPair & pair )
{
	auto key = pair.first;
	if( key.IsInvalid() && GetTag( "key_type" ) != "" )
	{
		key = XE::Reflection::FindClass( GetTag( "key_type" ).toStdString() )->ConstructPtr();
	}
	auto key_widget = XE::XESFramework::GetCurrentFramework()->GetServiceT<XE::XESMetaService>()->CreateMetaWidget( key );

	auto value = pair.second;
	if( value.IsInvalid() && GetTag( "value_type" ) != "" )
	{
		value = XE::Reflection::FindClass( GetTag( "value_type" ).toStdString() )->ConstructPtr();
	}
	auto value_widget = XE::XESFramework::GetCurrentFramework()->GetServiceT<XE::XESMetaService>()->CreateMetaWidget( value );

	ui->tableWidget->setRowCount( ui->tableWidget->rowCount() + 1 );

	ui->tableWidget->setCellWidget( ui->tableWidget->rowCount() - 1, 0, key_widget );
	ui->tableWidget->setCellWidget( ui->tableWidget->rowCount() - 1, 1, value_widget );
	ui->tableWidget->resizeRowToContents( ui->tableWidget->rowCount() - 1 );
}
