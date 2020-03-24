#include "XESAssetsService.h"

USING_XE

BEG_META( XESAssetsService )
END_META()

struct XE::XESAssetsService::Private
{

};

XESAssetsService::XESAssetsService()
	:_p( new Private )
{

}

XESAssetsService::~XESAssetsService()
{
	delete _p;
}

void XESAssetsService::RegisterAsset( const XE::String & path, const XE::MD5 & md5 )
{
	auto assets_path = GetFramework()->GetUserDataPath() / "assets.data";
	if( std::filesystem::exists( assets_path ) )
	{
		std::ofstream ofs( assets_path, std::ios::app );
		if( ofs.is_open() )
		{
			ofs << path.ToStdString() << ":" << md5.To32String() << ":" << 0 << std::endl;
		}
	}

	Super::ResetMD5Cache();
}

void XESAssetsService::UnregisterAsset( const XE::String & path )
{
	XE::Map<XE::String, XE::MD5> map;

	auto assets_path = GetFramework()->GetUserDataPath() / "assets.data";
	std::ifstream ifs( assets_path );
	if( ifs.is_open() )
	{
		char buf[512] = { 0 };

		while( !ifs.eof() )
		{
			ifs.getline( buf, 512 );
			auto list = XE::StringUtils::Split( buf, ":" );
			map.insert( { list[0], list[1] } );
		}
	}

	auto it = map.find( path );
	if( it != map.end() )
	{
		if( std::filesystem::exists( assets_path ) )
		{
			std::ofstream ofs( assets_path, std::ios::app );
			if( ofs.is_open() )
			{
				for( const auto & p : map )
				{
					ofs << p.first.ToStdString() << ":" << p.second.To32String() << ":" << 0 << std::endl;
				}
			}
		}

		Super::ResetMD5Cache();
	}
}

void XESAssetsService::SaveAsset( const XE::String & path, const XE::ObjectPtr & val )
{
	auto str = path.ToStdString();
	str.erase( str.begin() );

	std::ofstream ofs( GetFramework()->GetAssetsPath() / str );

	if( ofs.is_open() )
	{
		XE::JsonSaveArchive save;

		save & val;

		save.Save( ofs );

		ofs.close();
	}
}

XE::ObjectPtr XESAssetsService::SearchAssetData( const XE::String & val ) const
{
	auto str = val.ToStdString();
	str.erase( str.begin() );

	std::ifstream ifs( GetFramework()->GetAssetsPath() / str );

	if( ifs.is_open() )
	{
		XE::ObjectPtr obj;
		XE::JsonLoadArchive load( ifs );
		load & obj;

		return obj;
	}

	return nullptr;
}
