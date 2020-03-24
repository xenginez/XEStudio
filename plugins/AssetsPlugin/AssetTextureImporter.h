/*!
 * \file	AssetTextureImporter.h
 *
 * \author	ZhengYuanQing
 * \date	2020/03/13
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef ASSETTEXTUREIMPORTER_H__1C3B79E6_9B67_4D35_8589_90EC845B7D43
#define ASSETTEXTUREIMPORTER_H__1C3B79E6_9B67_4D35_8589_90EC845B7D43

#include "AssetImporter.h"

BEG_XE_NAMESPACE

class AssetTextureImporter : public XE::AssetImporter
{
	OBJECT( AssetTextureImporter, AssetImporter )

public:
	AssetTextureImporter();

	~AssetTextureImporter() override;

public:
	QString GetIcon() const override;

	QString GetSuffix() const override;

	QString GetSupport() const override;

	void Importer( const QString & from_path, const QString & to_path ) const override;

private:
	static XE::PixelFormat ConvertToFormat( QImage::Format format );

};

END_XE_NAMESPACE

#endif // ASSETTEXTUREIMPORTER_H__1C3B79E6_9B67_4D35_8589_90EC845B7D43
