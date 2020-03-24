#include "XESPluginService.h"

#include "XESFramework.h"

USING_XE

Plugin::Plugin( XESFramework * framework )
	:_Framework( framework )
{

}

Plugin::~Plugin()
{

}

XESFramework * Plugin::GetFramework() const
{
	return _Framework;
}

BEG_META( XESPluginService )
END_META()

struct XEPPluginInfo
{
public:
	typedef XE::Plugin * ( *RegisterInvoke )( XE::XESFramework * );

	typedef void( *UnregisterInvoke )( XE::Plugin * );

public:
	XE::Plugin * Plugin;
	XE::LibraryHandle Handle;
	RegisterInvoke Register;
	UnregisterInvoke Unregister;
};

struct XE::XESPluginService::Private
{
	XE::Map < String, XEPPluginInfo > _Plugins;
};

XESPluginService::XESPluginService()
	:_p( new Private )
{

}

XESPluginService::~XESPluginService()
{
	delete _p;
}

void XESPluginService::Prepare()
{

}

bool XESPluginService::Startup()
{
	auto framework = ( ( XE::XESFramework * ) GetFramework() );

	XE::Array<std::filesystem::path> paths;
	paths.push_back( framework->GetApplicationPath() / "plugins" );
	paths.push_back( framework->GetProjectPath() / "plugins" );

	for( const auto & path : paths )
	{
		std::filesystem::directory_iterator end;
		for( std::filesystem::directory_iterator iter( path ); iter != end; ++iter )
		{
			if( std::filesystem::is_directory( *iter ) )
			{
				auto plugin = ( *iter ).path() / ( ( *iter ).path().stem().u8string() + DLL_EXT_NAME );

				XEPPluginInfo info{};
				info.Handle = Library::Open( plugin.u8string() );
				if( info.Handle == LibraryHandle::Invalid )
				{
					XE_LOG( LoggerLevel::Error, "%1 plugin load error!", plugin.u8string() );
					break;
				}
				info.Register = Library::SymbolT < XEPPluginInfo::RegisterInvoke >( info.Handle, "RegisterPlugin" );
				info.Unregister = Library::SymbolT < XEPPluginInfo::UnregisterInvoke >( info.Handle, "UnregisterPlugin" );
				info.Plugin = info.Register( framework );

				info.Plugin->Startup();

				_p->_Plugins.insert( std::make_pair( info.Plugin->GetName(), info ) );
			}
		}
	}

	return true;
}

void XESPluginService::Update()
{

}

void XESPluginService::Clearup()
{
	for( auto & p : _p->_Plugins )
	{
		p.second.Plugin->Clearup();
		p.second.Unregister( p.second.Plugin );
	}

	_p->_Plugins.clear();
}
