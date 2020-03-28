#include "XESMetaWidget.h"

#include "XESDockCmd.h"
#include "XESDockWidget.h"

#include "XESFramework.h"
#include "XESMetaService.h"

class MetaVariantCmd : public XESDockCmd
{
public:
	MetaVariantCmd( XESMetaWidget * widget, const XE::Variant & val )
		:_Widget( widget ), _New( val ), _Old( widget->GetVariant() )
	{

	}

public:
	virtual void Todo()
	{
		_Widget->ResetVariant( _New );
	}

	virtual void Undo()
	{
		_Widget->ResetVariant( _Old );
	}

private:
	XESMetaWidget * _Widget;
	XE::Variant _Old;
	XE::Variant _New;
};

Q_DECLARE_METATYPE( XE::Variant );

IMPLEMENT_META( XESMetaWidget )

XESMetaWidget::XESMetaWidget()
{
	connect( this, &XESMetaWidget::ResetVariant, this, &XESMetaWidget::OnResetVariant );
}

XESMetaWidget::~XESMetaWidget()
{

}

void XESMetaWidget::Startup( const XE::Variant & val, const QString & tag /* = "" */ )
{
	_Value = val;
	QString Tag = tag;

	if( !Tag.isEmpty() )
	{
		Tag.replace( " ", "" );
		auto list = Tag.split( "," );
		for( const auto & str : list )
		{
			auto list2 = str.split( "=" );
			if( list2.size() == 2 )
			{
				_Tags.insert( list2[0], list2[1] );
			}
		}
	}
}

XE::Variant XESMetaWidget::UpdateVariant()
{
	_Value = OnUpdateVariant();

	return _Value;
}

void XESMetaWidget::OnResetVariant( const XE::Variant & val )
{
	_Value = val;
}

XE::Variant XESMetaWidget::GetVariant() const
{
	return _Value;
}

void XESMetaWidget::SetVariant( const XE::Variant & val )
{
	GetDockWidget()->Execute( XE::MakeShared<MetaVariantCmd>( this, val ) );
}

QString XESMetaWidget::GetTag( const QString & val, const QString & def /*= ""*/ ) const
{
	auto it = _Tags.find( val );

	if( it != _Tags.end() )
	{
		return it.value();
	}

	return def;
}

XESDockWidget * XESMetaWidget::GetDockWidget() const
{
	QObject * widget = parent();
	while( widget != nullptr )
	{
		if( auto dockwidget = qobject_cast< XESDockWidget * >( widget ) )
		{
			return dockwidget;
		}

		if( QWidget * p = qobject_cast< QWidget * >( widget ) )
		{
			widget = p->parent();
		}
		else
		{
			widget = nullptr;
		}
	}
	return nullptr;
}


IMPLEMENT_META( XESEnumMetaWidget )

XESEnumMetaWidget::XESEnumMetaWidget()
{
	auto layout = new QVBoxLayout( this );
	layout->setSpacing( 0 );
	layout->setContentsMargins( 0, 0, 0, 0 );

	_Widget = new QComboBox( this ); 
	_Widget->setCompleter( new QCompleter( _Widget->model(), this ) );

	layout->addWidget( _Widget );
}

XESEnumMetaWidget::~XESEnumMetaWidget()
{

}

void XESEnumMetaWidget::Startup( const XE::Variant & val, const QString & tag /* = "" */ )
{
	XESMetaWidget::Startup( val, tag );

	if( auto men = SP_CAST<XE::IMetaEnum>( GetVariant().GetType() ) )
	{
		men->Visit( [this]( XE::String name, XE::Variant value )
					{
						_Widget->addItem( name.ToCString(), QVariant::fromValue( value ) );
					} );
	}

	for( int i = 0; i < _Widget->count(); ++i )
	{
		auto var = GetVariant();
		if( var == _Widget->itemData( 0 ).value<XE::Variant>() )
		{
			_Widget->setCurrentIndex( i );
			break;
		}
	}
}

XE::Variant XESEnumMetaWidget::OnUpdateVariant()
{
	return _Widget->itemData( _Widget->currentIndex() ).value<XE::Variant>();
}

void XESEnumMetaWidget::OnResetVariant( const XE::Variant & val )
{
	XESMetaWidget::OnResetVariant( val );

	if( auto emu = DP_CAST<XE::IMetaEnum>( val.GetType() ) )
	{
		auto name = emu->FindName( val );
		for( int i = 0; i < _Widget->count(); ++i )
		{
			if( _Widget->itemText( i ).toStdString() == name.ToStdString() )
			{
				_Widget->setCurrentIndex( i );
				break;
			}
		}
	}
}


IMPLEMENT_META( XESClassMetaWidget )

XESClassMetaWidget::XESClassMetaWidget()
{
	auto layout = new QVBoxLayout( this );
	layout->setSpacing( 0 );
	layout->setContentsMargins( 0, 0, 0, 0 );

	_Widget = new QTableWidget( this );
	if( _Widget->columnCount() < 2 )
		_Widget->setColumnCount( 2 );
	QTableWidgetItem * __qtablewidgetitem = new QTableWidgetItem();
	__qtablewidgetitem->setText( "name" );
	_Widget->setHorizontalHeaderItem( 0, __qtablewidgetitem );
	QTableWidgetItem * __qtablewidgetitem1 = new QTableWidgetItem();
	__qtablewidgetitem1->setText( "value" );
	_Widget->setHorizontalHeaderItem( 1, __qtablewidgetitem1 );
	_Widget->setObjectName( QString::fromUtf8( "_Widget" ) );
	_Widget->setEditTriggers( QAbstractItemView::NoEditTriggers );
	_Widget->setSelectionMode( QAbstractItemView::SingleSelection );
	_Widget->setSelectionBehavior( QAbstractItemView::SelectRows );
	_Widget->setRowCount( 0 );
	_Widget->setColumnCount( 2 );
	_Widget->horizontalHeader()->setStretchLastSection( true );
	_Widget->verticalHeader()->setVisible( false );

	layout->addWidget( _Widget );
}

XESClassMetaWidget::~XESClassMetaWidget()
{

}

void XESClassMetaWidget::Startup( const XE::Variant & val, const QString & tag /* = "" */ )
{
	XESMetaWidget::Startup( val, tag );

	if( auto cls = SP_CAST<XE::IMetaClass>( GetVariant().GetType() ) )
	{
		cls->VisitProperty( [this]( XE::IMetaPropertyPtr prop )
							{
								if( !( prop->GetFlag() & XE::IMetaProperty::NoDesign ) )
								{
									AddProperty( prop );
								}
							} );
	}
}

XE::Variant XESClassMetaWidget::OnUpdateVariant()
{
	auto var = GetVariant();

	if( auto cls = SP_CAST<XE::IMetaClass>( XESMetaWidget::GetVariant().GetType() ) )
	{
		cls->VisitProperty( [&]( XE::IMetaPropertyPtr prop )
							{
								if( !( prop->GetFlag() & XE::IMetaProperty::NoDesign ) )
								{
									if( _Props.find( prop->GetName().ToCString() ) != _Props.end() )
									{
										prop->Set( var, _Props[prop->GetName().ToCString()]->UpdateVariant() );
									}
								}
							} );
	}

	return var;
}

void XESClassMetaWidget::OnResetVariant( const XE::Variant & val )
{
	XESMetaWidget::OnResetVariant( val );

	if( auto cls = SP_CAST<XE::IMetaClass>( GetVariant().GetType() ) )
	{
		cls->VisitProperty( [this, val]( XE::IMetaPropertyPtr prop )
							{
								if( !( prop->GetFlag() & XE::IMetaProperty::NoDesign ) )
								{
									auto it = _Props.find( prop->GetName().ToCString() );
									if( it != _Props.end() )
									{
										it.value()->ResetVariant( prop->Get( val ) );
									}
								}
							} );
	}
}

void XESClassMetaWidget::AddProperty( const XE::IMetaPropertyPtr & val )
{
	if( auto service = XE::XESFramework::GetCurrentFramework()->GetServiceT<XE::XESMetaService>() )
	{
		if( auto widget = service->CreateMetaWidget( val->Get( GetVariant() ), val->GetFullName() ) )
		{
			auto item = new QTableWidgetItem( val->GetName().ToCString() );
			
			_Widget->setRowCount( _Widget->rowCount() + 1 );

			_Widget->setItem( _Widget->rowCount() - 1, 0, item );
			_Widget->setCellWidget( _Widget->rowCount() - 1, 1, widget );
			_Widget->resizeRowToContents( _Widget->rowCount() - 1 );

			_Props.insert( val->GetName().ToCString(), widget );
		}
	}
}
