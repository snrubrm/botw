#pragma once

#include <basis/seadTypes.h>
#include <thread/seadCriticalSection.h>
#include "KingSystem/Resource/resHandle.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::act {
class Actor;
}

namespace uking::dmg {

// Name from the CSV (ClothStiffnessMgr::x 0x7100665530; the object is DamageInfoMgr + 0xe98, lane1 request for
// ChuchuRoot). Caches up to three loaded resources (`Entry`) with a reference count, keyed by a name string built from
// the actor's `_570->_b0->_310->_98` data; `mCS` guards the entries. Size 0x348.
// TODO: incomplete (only the functions used by the AI are declared; none is written yet except reset).
class ClothStiffnessMgr {
public:
    struct Entry {
        /* 0x00 */ u8 _0[0x98];  // a FixedSafeString (the key)
        /* 0x98 */ f32 _98;
        /* 0x9c */ f32 _9c;
        /* 0xa0 */ s32 mRefCount;
        /* 0xa4 */ u8 _a4[4];
        /* 0xa8 */ void* _a8;
        /* 0xb0 */ ksys::res::Handle mHandle;
    };
    static_assert(sizeof(Entry) == 0x100);

    // 0x7100665530 (declared only): finds or loads the entry for `actor` (stiffness values `a` / `b`) and takes a
    // reference. false if the actor has no physics / ragdoll data.
    bool x(f32 a, f32 b, ksys::act::Actor* actor);
    // 0x7100665a84 (declared only): drops the reference taken by x() (requests the unload at 0).
    void sub_7100665A84(ksys::act::Actor* actor);
    // 0x7100665b20: forgets all the entries' pointers and reference counts.
    void sub_7100665B20();

    /* 0x000 */ Entry mEntries[3];
    /* 0x300 */ u8 _300[8];
    /* 0x308 */ sead::CriticalSection mCS;
};
KSYS_CHECK_SIZE_NX150(ClothStiffnessMgr, 0x348);

}  // namespace uking::dmg
