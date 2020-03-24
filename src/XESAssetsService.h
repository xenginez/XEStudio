/*!
 * \file	XESAssetsService.h
 *
 * \author	ZhengYuanQing
 * \date	2020/03/10
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef XESASSETSSERVICE_H__97061729_7B7D_4694_AFA1_26581AE18352
#define XESASSETSSERVICE_H__97061729_7B7D_4694_AFA1_26581AE18352

#include "Type.h"

BEG_XE_NAMESPACE

class XES_API XESAssetsService : public XE::AssetsService
{
	OBJECT( XESAssetsService, AssetsService )

public:
	struct Private;

public:
	XESAssetsService();

	~XESAssetsService() override;

public:
	void RegisterAsset( const XE::String & path, const XE::MD5 & md5 );

	void UnregisterAsset( const XE::String & path );

public:
	void SaveAsset( const XE::String & path, const XE::ObjectPtr & val );

protected:
	XE::ObjectPtr SearchAssetData( const XE::String & val ) const override;

private:
	Private * _p;
};

END_XE_NAMESPACE

#endif // XESASSETSSERVICE_H__97061729_7B7D_4694_AFA1_26581AE18352
