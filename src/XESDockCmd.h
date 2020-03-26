/*!
 * \file	XESDockCmd.h
 *
 * \author	ZhengYuanQing
 * \date	2020/03/25
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef XESDOCKCMD_H__0AD6911A_E5E5_454C_ADD7_812A5537C678
#define XESDOCKCMD_H__0AD6911A_E5E5_454C_ADD7_812A5537C678

#include "Type.h"

class XES_API XESDockCmd : public std::enable_shared_from_this< XESDockCmd >
{
public:
	XESDockCmd();

	virtual ~XESDockCmd();

public:
	virtual void Todo() = 0;

	virtual void Undo() = 0;
};

class XES_API PackDockCmd : public XESDockCmd
{
public:
	PackDockCmd( const std::function<void()> & todo, const std::function<void()> & undo );

public:
	void Todo() override;

	void Undo() override;

private:
	std::function<void()> _Todo;
	std::function<void()> _Undo;
};

#endif // XESDOCKCMD_H__0AD6911A_E5E5_454C_ADD7_812A5537C678
