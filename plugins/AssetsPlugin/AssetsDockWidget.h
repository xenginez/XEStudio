/*!
 * \file	AssetsDockWidget.h
 *
 * \author	ZhengYuanQing
 * \date	2020/03/11
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef ASSETSDOCKWIDGET_H__401FAC9A_589C_428B_9982_060AE40477D8
#define ASSETSDOCKWIDGET_H__401FAC9A_589C_428B_9982_060AE40477D8

#include "AssetImporter.h"

QT_BEGIN_NAMESPACE
namespace Ui { class AssetsDockWidget; }
QT_END_NAMESPACE

class AssetsDockWidget : public XESDockWidget
{
	Q_OBJECT

public:
	AssetsDockWidget( QWidget * parent = nullptr, Qt::WindowFlags flags = Qt::WindowFlags() );

	~AssetsDockWidget();

private:
	void Init();

protected:
	bool eventFilter( QObject * obj, QEvent * event ) override;

private:
	void OnTreeWidgetFolderItemClicked( QTreeWidgetItem * item, int column );

	void OnListWidgetItemItemDoubleClicked( QListWidgetItem * item );

	void OnComboBoxFilterCurrentTextChanged( const QString & text );

	void OnTreeWidgetFolderContextMenuEvent( QContextMenuEvent * event );

	void OnListWidgetItemContextMenuEvent( QContextMenuEvent * event );

	void OnTreeWidgetFolderItemChanged( QTreeWidgetItem * item, int column );

	void OnListWidgetItemItemChanged( QListWidgetItem * item );

private:
	void AddTreeWidgetFolder( const QString & path, QTreeWidgetItem * parent );

	void ResetListWidgetItem( const QString & path );

	void ImportAsset( const QString & path );

private:
	QString SuffixToIcon( const QString & suffix ) const;

private:
	Ui::AssetsDockWidget * ui;
	QString _CurrentPath;
	QTreeWidgetItem * _EditTreeItem;
	QListWidgetItem * _EditListItem;
	QMap<QString, QString> _SuffixIcon;
	QMap<QString, std::shared_ptr<XE::AssetImporter> > _Supports;
};

#endif // ASSETSDOCKWIDGET_H__401FAC9A_589C_428B_9982_060AE40477D8
