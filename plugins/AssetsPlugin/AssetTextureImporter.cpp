#include "AssetTextureImporter.h"

USING_XE

BEG_META( AssetTextureImporter )
END_META()

AssetTextureImporter::AssetTextureImporter()
{

}

AssetTextureImporter::~AssetTextureImporter()
{

}

QString AssetTextureImporter::GetIcon() const
{
	return ":/icons/texture.png";
}

QString AssetTextureImporter::GetSuffix() const
{
	return "texture";
}

QString AssetTextureImporter::GetSupport() const
{
	return "png, jpg, bmp, dds, ppm, xbm, xpm, jpeg";
}

void AssetTextureImporter::Importer( const QString & from_path, const QString & to_path ) const
{
	// TODO: 
	QImage image( from_path );
	if( !image.isNull() )
	{
		XE::Buffer buf;

		XE::TexturePtr texture = XE::MakeShared<XE::Texture>();

		texture->SetWidth( image.width() );
		texture->SetHeight( image.height() );
		texture->SetDepth( image.depth() );
		texture->SetData( buf );

		XE::BinarySaveArchive save;

		save & texture;

		auto f_path = std::filesystem::u8path( from_path.toUtf8().toStdString() );
		auto path = std::filesystem::u8path( to_path.toUtf8().toStdString() ) / (f_path.stem().u8string() + ".texture");
		std::ofstream ofs( path );
		save.Save( ofs );
		ofs.close();
	}
}

XE::PixelFormat AssetTextureImporter::ConvertToFormat( QImage::Format format )
{
	switch( format )
	{
	case QImage::Format_Invalid:
		break;
	case QImage::Format_Mono:
		break;
	case QImage::Format_MonoLSB:
		break;
	case QImage::Format_Indexed8:
		break;
	case QImage::Format_RGB32:
		break;
	case QImage::Format_ARGB32:
		break;
	case QImage::Format_ARGB32_Premultiplied:
		break;
	case QImage::Format_RGB16:
		break;
	case QImage::Format_ARGB8565_Premultiplied:
		break;
	case QImage::Format_RGB666:
		break;
	case QImage::Format_ARGB6666_Premultiplied:
		break;
	case QImage::Format_RGB555:
		break;
	case QImage::Format_ARGB8555_Premultiplied:
		break;
	case QImage::Format_RGB888:
		break;
	case QImage::Format_RGB444:
		break;
	case QImage::Format_ARGB4444_Premultiplied:
		break;
	case QImage::Format_RGBX8888:
		break;
	case QImage::Format_RGBA8888:
		break;
	case QImage::Format_RGBA8888_Premultiplied:
		break;
	case QImage::Format_BGR30:
		break;
	case QImage::Format_A2BGR30_Premultiplied:
		break;
	case QImage::Format_RGB30:
		break;
	case QImage::Format_A2RGB30_Premultiplied:
		break;
	case QImage::Format_Alpha8:
		break;
	case QImage::Format_Grayscale8:
		break;
	case QImage::Format_RGBX64:
		break;
	case QImage::Format_RGBA64:
		break;
	case QImage::Format_RGBA64_Premultiplied:
		break;
	case QImage::NImageFormats:
		break;
	default:
		break;
	}

	return XE::PixelFormat::PIXELFORMAT_NONE;
}
