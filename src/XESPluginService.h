/*!
 * \file	XESPluginService.h
 *
 * \author	ZhengYuanQing
 * \date	2019/10/27
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef XESPLUGINSERVICE_H__52A2E13F_70F9_438A_9953_38971B045A47
#define XESPLUGINSERVICE_H__52A2E13F_70F9_438A_9953_38971B045A47

#include "Type.h"

BEG_XE_NAMESPACE

class XES_API Plugin
{
public:
	Plugin( XESFramework * framework );

	virtual ~Plugin();

public:
	virtual String GetName() const = 0;

public:
	virtual void Startup() = 0;

	virtual void Update() = 0;

	virtual void Clearup() = 0;

protected:
	XESFramework * GetFramework() const;

private:
	XESFramework * _Framework;
};

class XES_API XESPluginService : public XE::IService
{
	OBJECT( XESPluginService, IService )

private:
	struct Private;

public:
	XESPluginService();
	
	~XESPluginService() override;

public:
	void Prepare()override;

	bool Startup() override;

	void Update() override;

	void Clearup() override;

private:
	Private * _p;
};

END_XE_NAMESPACE

#endif // XESPLUGINSERVICE_H__52A2E13F_70F9_438A_9953_38971B045A47
