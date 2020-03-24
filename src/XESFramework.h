/*!
 * \file	XESFramework.h
 *
 * \author	ZhengYuanQing
 * \date	2020/03/10
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef XESFRAMEWORK_H__DCBB226A_1497_4AC7_8611_745E4936AF72
#define XESFRAMEWORK_H__DCBB226A_1497_4AC7_8611_745E4936AF72

#include "Type.h"

BEG_XE_NAMESPACE

class XES_API XESFramework : public XE::CoreFramework
{
	OBJECT( XESFramework, CoreFramework )

private:
	friend class ProMainWindow;

private:
	struct Private;

public:
	XESFramework();

	~XESFramework() override;

public:
	static XESFramework * GetCurrentFramework();

public:
	int Exec( int argc, char * argv[] );

public:
	void Prepare() override;

	void Startup() override;

	void Update() override;

	void Clearup() override;

public:
	XESMainWindow * GetMainWindow() const;

public:
	const XE::String & GetProjectName() const;

	std::filesystem::path GetProjectPath() const;

	std::filesystem::path GetPackagePath() const;

	std::filesystem::path GetAssetsPath() const override;

	std::filesystem::path GetUserDataPath() const override;

public:
	void Save() override;

	void Reload() override;

protected:
	String GetValue( const String & key ) override;

	void SetValue( const String & key, const String & val ) override;

protected:
	void LoadModules() override;

private:
	void InitPro( int argc, char * argv[] );

	void InitQt( int argc, char * argv[] );

private:
	void SetProjectName( const XE::String & val );

	void SetProjectPath( const std::filesystem::path & val );

private:
	Private * _p;
};

END_XE_NAMESPACE

#endif // XESFRAMEWORK_H__DCBB226A_1497_4AC7_8611_745E4936AF72
