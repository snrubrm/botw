#pragma once

#include <basis/seadTypes.h>
#include <prim/seadSafeString.h>
#include "KingSystem/Resource/resHandle.h"

namespace ksys::map {

// One entry of the static-mubin table that MapStaticLoadMgr::loadStaticFiles builds: the mubin
// name (+0) and the resource handle it loads (+0x58). getMapStaticMubin searches the name and
// returns the handle.
struct MapStaticMubin {
    sead::BufferedSafeString name;
    u8 _18[0x40];
    res::Handle handle;
};
static_assert(sizeof(MapStaticMubin) == 0xa8);

// 0x7102603dc8 / 0x7102603dd0: the table the loader fills and getMapStaticMubin searches.
extern s32 sNumMubins;
extern MapStaticMubin* sMubins;

}  // namespace ksys::map

// 0x7100e8dca8: the handle of the static mubin named `name`, or null.
ksys::res::Handle* getMapStaticMubin(const sead::SafeString& name);
