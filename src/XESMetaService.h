/*!
 * \file	XESMetaService.h
 *
 * \author	ZhengYuanQing
 * \date	2020/03/19
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef XESMETASERVICE_H__478C26F9_3AD4_4B5F_B74A_9BF2B441BA1A
#define XESMETASERVICE_H__478C26F9_3AD4_4B5F_B74A_9BF2B441BA1A

#include "Type.h"

BEG_XE_NAMESPACE

class XES_API XESMetaService : public XE::IService
{
	OBJECT( XESMetaService, IService )

private:
	struct Private;

public:
	XESMetaService();

	~XESMetaService() override;

public:
	void Prepare() override;

	bool Startup() override;

	void Update() override;

	void Clearup() override;

public:
	XESMetaWidget * CreateMetaWidget( const XE::Variant & val, const XE::String & name = "" );

private:
	Private * _p;
};

END_XE_NAMESPACE

#endif // XESMETASERVICE_H__478C26F9_3AD4_4B5F_B74A_9BF2B441BA1A
