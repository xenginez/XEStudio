/*!
 * \file	ProListWidgetItem.h
 *
 * \author	ZhengYuanQing
 * \date	2020/03/24
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef PROLISTWIDGETITEM_H__C9C74253_FC3D_4DB1_A8CF_1B1961FF0AF8
#define PROLISTWIDGETITEM_H__C9C74253_FC3D_4DB1_A8CF_1B1961FF0AF8

#include "Type.h"

QT_BEGIN_NAMESPACE
namespace Ui { class ProListWidgetItem; }
QT_END_NAMESPACE

class ProListWidgetItem : public QWidget
{
	Q_OBJECT

public:
	ProListWidgetItem( const QString & path, QWidget * parent = nullptr );

	~ProListWidgetItem() override;

Q_SIGNALS:
	void DoubleClicked( const QString & path );

	void DeleteItem();

public:
	const QString & GetPath() const;

protected:
	void enterEvent( QEvent * event ) override;

	void leaveEvent( QEvent * event ) override;

	void mouseDoubleClickEvent( QMouseEvent * event ) override;

private:
	QString _Path;
	Ui::ProListWidgetItem * ui;
};

#endif // PROLISTWIDGETITEM_H__C9C74253_FC3D_4DB1_A8CF_1B1961FF0AF8
