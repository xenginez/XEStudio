/*!
 * \file	Event.h
 *
 * \author	ZhengYuanQing
 * \date	2020/03/20
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef EVENT_H__4DCFAB0E_9419_4D4E_B58B_F4DCFE0F9CF0
#define EVENT_H__4DCFAB0E_9419_4D4E_B58B_F4DCFE0F9CF0

#include "Type.h"

BEG_XE_NAMESPACE

DECL_EVENT( OPEN_ASSET_AI, "open asset type *.ai", XE::String );
DECL_EVENT( OPEN_ASSET_ANIM, "open asset type *.anim", XE::String );
DECL_EVENT( OPEN_ASSET_MESH, "open asset type *.mesh", XE::String );
DECL_EVENT( OPEN_ASSET_WORLD, "open asset type *.world", XE::String );
DECL_EVENT( OPEN_ASSET_SOUND, "open asset type *.sound", XE::String );
DECL_EVENT( OPEN_ASSET_TEXTURE, "open asset type *.texture", XE::String );
DECL_EVENT( OPEN_ASSET_SHADER, "open asset type *.shader", XE::String );
DECL_EVENT( OPEN_ASSET_PREFAB, "open asset type *.prefab", XE::String );
DECL_EVENT( OPEN_ASSET_SKELETON, "open asset type *.skeleton", XE::String );
DECL_EVENT( OPEN_ASSET_MATERIAL, "open asset type *.material", XE::String );
DECL_EVENT( OPEN_ASSET_UNKNOWN, "open asset type unknown", XE::String );

END_XE_NAMESPACE

#endif // EVENT_H__4DCFAB0E_9419_4D4E_B58B_F4DCFE0F9CF0
