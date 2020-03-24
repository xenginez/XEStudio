#include "XESFramework.h"

#include "DarkStyle.h"
#include "XESMainWindow.h"
#include "ProMainWindow.h"
#include "XESApplication.h"


USING_XE

BEG_META( XESFramework )
END_META()

struct XE::XESFramework::Private
{
	QTimer * _Timer;
	XE::String _ProjName;
	XESMainWindow * _MainWindow;
	XESApplication * _Application;
	std::filesystem::path  _ProjPath;
	XE::Map < String, String > _KeyMap;
	XE::Map < String, String > _Editor;
	XE::Map < String, String > _Project;
};

XE::XESFramework::XESFramework()
	:_p( new Private )
{

}

XE::XESFramework::~XESFramework()
{
	delete _p;
}

XE::XESFramework * XE::XESFramework::GetCurrentFramework()
{
	return static_cast< XESFramework * >( XE::IFramework::GetCurrentFramework() );
}

int XE::XESFramework::Exec( int argc, char * argv[] )
{
	_p->_Application = new XESApplication( argc, argv );
	_p->_Application->setStyle( new DarkStyle );


	if( argc > 1 )
	{
		std::filesystem::path proj( argv[1] );

		if( std::filesystem::exists( proj ) )
		{
			auto nn = proj.stem();
			_p->_ProjName = nn.string();
			_p->_ProjPath = proj.parent_path();
		}
	}
	else
	{
		InitPro( argc, argv );
		if( _p->_ProjName == "" )
		{
			return 0;
		}
	}

	XE::Library::RegisterEnvPath( GetProjectPath() / "modules" );

	Prepare();

	InitQt( argc, argv );

	Startup();

	int ret = _p->_Application->exec();

	Clearup();

	return ret;
}

void XE::XESFramework::Prepare()
{
	Super::Prepare();
}

void XE::XESFramework::Startup()
{
	Super::Startup();
}

void XE::XESFramework::Update()
{
	Super::Update();
}

void XE::XESFramework::Clearup()
{
	Save();

	Super::Clearup();

	_p->_Editor.clear();
	_p->_Project.clear();
	_p->_KeyMap.clear();
}

XESMainWindow * XE::XESFramework::GetMainWindow() const
{
	return _p->_MainWindow;
}

const XE::String & XE::XESFramework::GetProjectName() const
{
	return _p->_ProjName;
}

std::filesystem::path XE::XESFramework::GetProjectPath() const
{
	return _p->_ProjPath;
}

std::filesystem::path XE::XESFramework::GetPackagePath() const
{
	return this->GetApplicationPath() / "package";
}

std::filesystem::path XE::XESFramework::GetAssetsPath() const
{
	return GetProjectPath() / "assets";
}

std::filesystem::path XE::XESFramework::GetUserDataPath() const
{
	return GetProjectPath() / "data";
}

void XESFramework::Save()
{
	auto proj_path = XESFramework::GetCurrentFramework()->GetProjectPath() / ( XESFramework::GetCurrentFramework()->GetProjectName() + ".xeproj" ).ToCString();
	auto editor_path = XESFramework::GetCurrentFramework()->GetApplicationPath() / "editor.json";
	auto keymap_path = XESFramework::GetCurrentFramework()->GetApplicationPath() / "keymap.json";

	Super::Save( proj_path, _p->_Project );
	Super::Save( editor_path, _p->_Editor );
	Super::Save( keymap_path, _p->_KeyMap );

	_p->_MainWindow->Save();
}

void XESFramework::Reload()
{
	auto proj_path = XESFramework::GetCurrentFramework()->GetProjectPath() / ( XESFramework::GetCurrentFramework()->GetProjectName().ToStdString() + ".xeproj" );
	auto editor_path = XESFramework::GetCurrentFramework()->GetApplicationPath() / "editor.json";
	auto keymap_path = XESFramework::GetCurrentFramework()->GetApplicationPath() / "keymap.json";

	Super::Reload( proj_path, _p->_Project );
	Super::Reload( editor_path, _p->_Editor );
	Super::Reload( keymap_path, _p->_KeyMap );
}

XE::String XESFramework::GetValue( const String & key )
{
	const std::string & str = key.ToStdString();

	if( str.find_first_of( "KeyMap" ) == 0 )
	{
		auto it = _p->_KeyMap.find( key );
		if( it != _p->_KeyMap.end() )
		{
			return it->second;
		}

		_p->_KeyMap.insert( { key, "" } );

		return "";
	}

	if( str.find_first_of( "Editor" ) == 0 )
	{
		auto it = _p->_Editor.find( key );
		if( it != _p->_Editor.end() )
		{
			return it->second;
		}

		_p->_Editor.insert( { key, "" } );

		return "";
	}

	auto it = _p->_Project.find( key );
	if( it != _p->_Project.end() )
	{
		return it->second;
	}

	_p->_Project.insert( { key, "" } );

	return "";
}

void XESFramework::SetValue( const String & key, const String & val )
{
	const std::string & str = key.ToStdString();

	if( str.find_first_of( "KeyMap" ) == 0 )
	{
		_p->_KeyMap.insert( { key, val } );
		return;
	}

	if( str.find_first_of( "Editor" ) == 0 )
	{
		_p->_Editor.insert( { key, val } );
		return;
	}

	_p->_Project.insert( { key, val } );
}

void XESFramework::LoadModules()
{
	Super::LoadModules();

	auto path = GetProjectPath() / "modules";

	std::filesystem::directory_iterator end;
	for( std::filesystem::directory_iterator iter( path ); iter != end; ++iter )
	{
		if( std::filesystem::is_directory( *iter ) )
		{
			auto module = ( *iter ).path() / ( ( *iter ).path().stem().u8string() + DLL_EXT_NAME );
			if( Library::Open( module.u8string() ) == LibraryHandle::Invalid )
			{
				std::cout << "load module \"" << module.u8string() << "\" fail" << std::endl;
			}
		}
	}
}

void XESFramework::InitPro( int argc, char * argv[] )
{
	auto mainwindow = new ProMainWindow;
	mainwindow->show();

	_p->_Application->exec();
}

void XESFramework::InitQt( int argc, char * argv[] )
{
	_p->_MainWindow = new XESMainWindow;
	_p->_MainWindow->showMaximized();

	_p->_Timer = new QTimer();
	_p->_Timer->connect( _p->_Timer, &QTimer::timeout, [this]()
						 {
							 Update();
						 } );

	QTimer::singleShot( 200, [this]()
						{
							_p->_MainWindow->ResizeDocks();
							_p->_Timer->start( 1 );
						} );

	_p->_Application->processEvents();
}

void XESFramework::SetProjectName( const XE::String & val )
{
	_p->_ProjName = val;
}

void XESFramework::SetProjectPath( const std::filesystem::path & val )
{
	_p->_ProjPath = val;
}
