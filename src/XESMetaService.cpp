#include "XESMetaService.h"

#include "XESFramework.h"
#include "XESMetaWidget.h"

USING_XE

struct PMetaClassInfo
{
	QString Tag;
	QString Name;
	QString Widget;
};

struct XESMetaService::Private
{
	QMap<QString, PMetaClassInfo> _Infos;
};

IMPLEMENT_META( XESMetaService )

XESMetaService::XESMetaService()
	:_p( new Private )
{

}

XESMetaService::~XESMetaService()
{
	delete _p;
}

void XESMetaService::Prepare()
{
	auto path = XESFramework::GetCurrentFramework()->GetApplicationPath() / "meta.json";

	QFile file( QString::fromUtf8( path.u8string().c_str() ) );
	if( file.open( QIODevice::ReadOnly ) )
	{
		QJsonParseError error;
		auto doc = QJsonDocument::fromJson( file.readAll(), &error );
		if( error.error == QJsonParseError::NoError )
		{
			auto classes = doc.object().find( "Class" ).value().toObject();
			for( auto it = classes.begin(); it != classes.end(); ++it )
			{
				PMetaClassInfo class_info;
				auto value = it.value().toObject();

				class_info.Name = it.key();
				class_info.Tag = value.find( "tag" ).value().toString();
				class_info.Widget = value.find( "widget" ).value().toString();
				_p->_Infos.insert( class_info.Name, std::move( class_info ) );
			}

			auto props = doc.object().find( "Property" ).value().toObject();
			for( auto it = props.begin(); it != props.end(); ++it )
			{
				auto prop = it.value().toObject();
				for( auto prop_it = prop.begin(); prop_it != prop.end(); ++prop_it )
				{
					PMetaClassInfo prop_info;

					auto value = prop_it.value().toObject();

					prop_info.Name = it.key() + "::" + prop_it.key();
					prop_info.Tag = value.find( "tag" ).value().toString();
					prop_info.Widget = value.find( "widget" ).value().toString();
					_p->_Infos.insert( prop_info.Name, std::move( prop_info ) );
				}
			}
		}
		else
		{
			XE_LOG( XE::LoggerLevel::Error, "%1 read error: %2", path.u8string(), error.errorString().toStdString() );
		}
	}
}

bool XESMetaService::Startup()
{
	return true;
}

void XESMetaService::Update()
{

}

void XESMetaService::Clearup()
{

}

XESMetaWidget * XESMetaService::CreateMetaWidget( const XE::Variant & val, const XE::String & name /*= "" */ )
{
	XESMetaWidget * widget = nullptr;

	auto it = _p->_Infos.end();
	if( name != "" )
	{
		it = _p->_Infos.find( name.ToCString() );
	}
	if( it == _p->_Infos.end() )
	{
		it = _p->_Infos.find( XE::TypeID<XE::Variant>::Get( &val )->GetFullName().ToCString() );
	}

	if( it != _p->_Infos.end() )
	{
		if( auto cls = XE::Reflection::FindClass( it.value().Widget.toStdString() ) )
		{
			widget = (XESMetaWidget * )cls->Construct().Detach();
			widget->Startup( val, it.value().Tag );
		}
	}
	else if( val.GetType()->GetType() == XE::MetaType::ENUM )
	{
		widget = new XESEnumMetaWidget();
		widget->Startup( val, "" );
	}
	else if( val.GetType()->GetType() == XE::MetaType::CLASS )
	{
		widget = new XESClassMetaWidget();
		widget->Startup( val, "" );
	}

	return widget;
}

