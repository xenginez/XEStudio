/*!
 * \file	ProMainWindow.h
 *
 * \author	ZhengYuanQing
 * \date	2020/03/24
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef PROMAINWINDOW_H__74E30D58_D498_4025_9C7F_8FC62F350274
#define PROMAINWINDOW_H__74E30D58_D498_4025_9C7F_8FC62F350274

#include "Type.h"

QT_BEGIN_NAMESPACE
namespace Ui { class ProMainWindow; }
QT_END_NAMESPACE

class ProMainWindow : public QMainWindow
{
	Q_OBJECT

public:
	ProMainWindow( QWidget * parent = nullptr, Qt::WindowFlags flags = Qt::WindowFlags() );

	~ProMainWindow() override;

protected:
	bool eventFilter( QObject * obj, QEvent * event ) override;

private:
	void LoadRecents();

	QStringList ReadProjectJson() const;

	void WriteProjectJson( const QStringList & val ) const;

private:
	Ui::ProMainWindow * ui;
	QPixmap _Close;
	QPixmap _Close2;
};

#endif // PROMAINWINDOW_H__74E30D58_D498_4025_9C7F_8FC62F350274
