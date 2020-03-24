/*!
 * \file	GraphicsItem.h
 *
 * \author	ZhengYuanQing
 * \date	2020/03/13
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef GRAPHICSITEM_H__BDEC53AF_3CA1_4E4F_8848_327FB6176CE1
#define GRAPHICSITEM_H__BDEC53AF_3CA1_4E4F_8848_327FB6176CE1

#include "Global.h"

class GraphicsItem : public QGraphicsItem
{
public:
	GraphicsItem( QGraphicsItem * parent = nullptr );
	
	~GraphicsItem() override;

public:
	GraphicsScene * GetGraphicsScene() const;
};

#endif // GRAPHICSITEM_H__BDEC53AF_3CA1_4E4F_8848_327FB6176CE1
