/*!
 * \file	DarkStyle.h
 *
 * \author	ZhengYuanQing
 * \date	2019/10/26
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef DARKSTYLE_H__75812F8F_B8AE_4CB8_B3DC_818474708916
#define DARKSTYLE_H__75812F8F_B8AE_4CB8_B3DC_818474708916

#include <QFile>
#include <QFont>
#include <QProxyStyle>
#include <QApplication>
#include <QStyleFactory>

class DarkStyle : public QProxyStyle
{
	Q_OBJECT

public:
	DarkStyle();
	explicit DarkStyle( QStyle * style );

	QStyle * baseStyle() const;

	void polish( QPalette & palette ) override;
	void polish( QApplication * app ) override;

private:
	QStyle * styleBase( QStyle * style = Q_NULLPTR ) const;
};

#endif // DARKSTYLE_H__75812F8F_B8AE_4CB8_B3DC_818474708916
