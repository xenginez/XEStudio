#include "SelectTypeMetaWidget.h"

IMPLEMENT_META( SelectTypeMetaWidget )

SelectTypeMetaWidget::SelectTypeMetaWidget()
	:_Widget( nullptr )
{
	_Layout = new QVBoxLayout( this );
	_Layout->setSpacing( 2 );
	_Layout->setContentsMargins( 0, 0, 0, 0 );

	_ComboBox = new QComboBox( this );
	_ComboBox->addItem( "" );
	_Layout->addWidget( _ComboBox );
}

SelectTypeMetaWidget::~SelectTypeMetaWidget()
{

}

void SelectTypeMetaWidget::Startup( const XE::Variant & val, const QString & tag )
{
	XESMetaWidget::Startup( val, tag );

	auto type = GetTag( "type", "" );

	if( type == "" )
	{
		XE::Reflection::VisitClass( [&]( XE::IMetaClassPtr cls )
									{
										_ComboBox->addItem( QString::fromUtf8( cls->GetFullName().ToCString() ) );
									} );
	}
	else
	{
		auto list = type.split( "|" );
		for( const auto & name : list )
		{
			if( auto cls = XE::Reflection::FindClass( name.toStdString() ) )
			{
				VisitClass( cls );
			}
		}
	}

	_ComboBox->setCompleter( new QCompleter( _ComboBox->model(), this ) );

	connect( _ComboBox, &QComboBox::currentTextChanged, [this]( const QString & text )
			 {
				 if( text == "" )
				 {
					 if( _Widget != nullptr )
					 {
						 _Widget->deleteLater();
						 _Widget = nullptr;
					 }
				 }
				 else
				 {
					 auto var = XE::Reflection::FindClass( text.toStdString() )->ConstructPtr();
					 SetVariant( var );
					 _Widget = XE::XESFramework::GetCurrentFramework()->GetServiceT<XE::XESMetaService>()->CreateMetaWidget( var );
					 _Layout->addWidget( _Widget );
				 }
			 } );
}
XE::Variant SelectTypeMetaWidget::OnUpdateVariant()
{
	if( _Widget )
	{
		return _Widget->UpdateVariant();
	}

	return GetVariant();
}

void SelectTypeMetaWidget::OnResetVariant( const XE::Variant & val )
{
	XESMetaWidget::OnResetVariant( val );

	if( _ComboBox->currentText() != val.GetType()->GetFullName().ToCString() )
	{
		_ComboBox->setCurrentText( val.GetType()->GetFullName().ToCString() );
	}

	_Widget->ResetVariant( val );
}

void SelectTypeMetaWidget::VisitClass( const XE::IMetaClassPtr & val )
{
	if( !val->IsAbstract() )
	{
		_ComboBox->addItem( val->GetFullName().ToCString() );
	}

	val->VisitDerivedClass( [this]( XE::IMetaClassPtr cls )
							{
								VisitClass( cls );
							} );
}
