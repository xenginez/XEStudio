/*!
 * \file	AssetImporter.h
 *
 * \author	ZhengYuanQing
 * \date	2020/03/12
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef ASSETIMPORTER_H__6E11B15D_35F1_425D_9993_C97CA6AD6418
#define ASSETIMPORTER_H__6E11B15D_35F1_425D_9993_C97CA6AD6418

#include "Global.h"

BEG_XE_NAMESPACE

class AssetImporter : public std::enable_shared_from_this< AssetImporter >
{
	OBJECT( AssetImporter )

public:
	AssetImporter();

	virtual ~AssetImporter();

public:
	virtual QString GetIcon() const = 0;

	virtual QString GetSuffix() const = 0;

	virtual QString GetSupport() const = 0;

	virtual void Importer( const QString & from_path, const QString & to_path ) const = 0;
};

END_XE_NAMESPACE

#endif // ASSETIMPORTER_H__6E11B15D_35F1_425D_9993_C97CA6AD6418
