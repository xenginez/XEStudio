#include "ArrayMetaWidget.h"
#include "ui_ArrayMetaWidget.h"

IMPLEMENT_META( ArrayMetaWidget )

ArrayMetaWidget::ArrayMetaWidget()
	:ui( new Ui::ArrayMetaWidget )
{
	ui->setupUi( this );

	connect( ui->pushButtonAdd, &QPushButton::clicked, this, &ArrayMetaWidget::OnPushButtonAddClicked );
	connect( ui->pushButtonSub, &QPushButton::clicked, this, &ArrayMetaWidget::OnPushButtonSubClicked );
}

ArrayMetaWidget::~ArrayMetaWidget()
{
	delete ui;
}

void ArrayMetaWidget::Startup( const XE::Variant & val, const QString & tag )
{
	XESMetaWidget::Startup( val, tag );

	auto arr = val.ToArray();
	for( const auto & var : arr )
	{
		auto widget = XE::XESFramework::GetCurrentFramework()->GetServiceT<XE::XESMetaService>()->CreateMetaWidget( var );
		auto item = new QListWidgetItem();
		item->setSizeHint( widget->sizeHint() );
		ui->listWidget->addItem( item );
		ui->listWidget->setItemWidget( item, widget );
	}
}

XE::Variant ArrayMetaWidget::UpdateVariant()
{
	XE::VariantArray arr;

	for( int i = 0; i < ui->listWidget->count(); ++i )
	{
		auto widget = (XESMetaWidget * )ui->listWidget->itemWidget( ui->listWidget->item( i ) );
		arr.push_back( widget->UpdateVariant() );
	}

	SetVariant( arr );

	return GetVariant();
}

void ArrayMetaWidget::OnPushButtonAddClicked()
{
	XE::Variant var;

	auto type = GetTag( "type", "" );
	if( type != "" )
	{
		var = XE::Reflection::FindClass( type.toStdString() )->ConstructPtr();
	}

	auto widget = XE::XESFramework::GetCurrentFramework()->GetServiceT<XE::XESMetaService>()->CreateMetaWidget( var );
	auto item = new QListWidgetItem();
	item->setSizeHint( widget->sizeHint() );
	ui->listWidget->addItem( item );
	ui->listWidget->setItemWidget( item, widget );
}

void ArrayMetaWidget::OnPushButtonSubClicked()
{
	if( ui->listWidget->currentItem() != nullptr )
	{
		delete ui->listWidget->takeItem( ui->listWidget->row( ui->listWidget->currentItem() ) );
	}
}
