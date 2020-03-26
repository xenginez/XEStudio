/*!
 * \file	ProCreateDialog.h
 *
 * \author	ZhengYuanQing
 * \date	2020/03/24
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef PROCREATEDIALOG_H__21D2B55C_333A_4535_ADE0_02B8423326F5
#define PROCREATEDIALOG_H__21D2B55C_333A_4535_ADE0_02B8423326F5

#include "Type.h"

QT_BEGIN_NAMESPACE
namespace Ui { class ProCreateDialog; }
QT_END_NAMESPACE

class ProCreateDialog : public QDialog
{
	Q_OBJECT

public:
	ProCreateDialog( QWidget * parent = nullptr );

	~ProCreateDialog() override;

public:
	const QString & GetPath() const;

private:
	void LoadPackage();

	void OnToolButton();

	void OnPushButtonYes();

	void OnPushButtonNo();

	bool CreateProject();

	void CreateDescription();

private:
	QString _Path;
	Ui::ProCreateDialog * ui;
};

#endif // PROCREATEDIALOG_H__21D2B55C_333A_4535_ADE0_02B8423326F5
