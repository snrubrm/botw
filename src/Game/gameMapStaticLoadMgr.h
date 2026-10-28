#pragma once

#include <basis/seadTypes.h>
#include <heap/seadDisposer.h>
#include <prim/seadSafeString.h>
#include "KingSystem/Resource/resHandle.h"

namespace ksys::map {

// One entry of the static-mubin table that MapStaticLoadMgr::loadStaticFiles builds: the mubin
// name (+0) and the resource handle it loads (+0x58). getMapStaticMubin searches the name and
// returns the handle.
struct MapStaticMubin {
    sead::FixedSafeString<64> name;
    res::Handle handle;
};
static_assert(sizeof(MapStaticMubin) == 0xa8);

// 0x7102603dc0: the map names the loader resolves (one 0x10-byte SafeString each); 0x7102603dc8 /
// 0x7102603dd0: the number of mubins and the table getMapStaticMubin searches.
extern const sead::SafeString* sMapNames;
extern s32 sNumMubins;
extern MapStaticMubin* sMubins;
// 0x7102603dd8: set while the static mubin table is not meant to be built (cleared by
// initMapStaticResources when the scene asks for map statics).
extern bool sUnk_7102603DD8;
// 0x7102603de0 / 0x7102603de8: the callbacks loadStaticFiles stores for the resource load step.
extern void (*sUnk_7102603DE0)();
extern void (*sUnk_7102603DE8)();
// 0x7102603df0: the main field location mubin loader (0x7100e8dc98 stores it).
extern void (*sLoadLocationMubinCallback)();

class MapStaticLoadMgr {
public:
    // 0x7100e8d84c: builds `count` mubin entries for `names` and starts their resource load.
    static void loadStaticFiles(const sead::SafeString* names, s32 count, sead::Heap* heap,
                                void (*callback1)(), void (*callback2)());
    // 0x7100e8d984: copies each map name into its mubin entry and requests the
    // "Map/<name>/Static.mubin" resource. Placeholder name.
    static void sub_7100E8D984();
};

}  // namespace ksys::map

// 0x7100e8dc98: stores the main field location mubin loader. Placeholder name.
void setLoadLocationMubinCallback(void (*callback)());

// 0x7100e8dca8: the handle of the static mubin named `name`, or null.
ksys::res::Handle* getMapStaticMubin(const sead::SafeString& name);
