/*!
 * \file	Global.h
 *
 * \author	ZhengYuanQing
 * \date	2020/03/10
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef GLOBAL_H__893EE6B2_4C05_4A8D_841F_5C57234D35DC
#define GLOBAL_H__893EE6B2_4C05_4A8D_841F_5C57234D35DC

#include <QSet>
#include <QMap>
#include <QMenu>
#include <QEvent>
#include <QLabel>
#include <QMovie>
#include <QTimer>
#include <QVector>
#include <QThread>
#include <QToolBar>
#include <QMenuBar>
#include <QSpinBox>
#include <QPainter>
#include <QBitArray>
#include <QLineEdit>
#include <QKeyEvent>
#include <QSettings>
#include <QComboBox>
#include <QCheckBox>
#include <QSplitter>
#include <QJsonArray>
#include <QScrollBar>
#include <QBoxLayout>
#include <QClipboard>
#include <QScrollBar>
#include <QtSql/QSql>
#include <QCompleter>
#include <QListWidget>
#include <QMessageBox>
#include <QMouseEvent>
#include <QFileDialog>
#include <QPushButton>
#include <QTreeWidget>
#include <QDockWidget>
#include <QMessageBox>
#include <QMainWindow>
#include <QJsonObject>
#include <QHeaderView>
#include <QTableWidget>
#include <QApplication>
#include <QJsonDocument>
#include <QGraphicsItem>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QDoubleSpinBox>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlDatabase>
#include <QGraphicsSceneMouseEvent>


#include <Core/Core.h>

#if defined(XESTUDIO_LIBRARY)
#  define XES_API Q_DECL_EXPORT
#else
#  define XES_API Q_DECL_IMPORT
#endif

#endif // GLOBAL_H__893EE6B2_4C05_4A8D_841F_5C57234D35DC
