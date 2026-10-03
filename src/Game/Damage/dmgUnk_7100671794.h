#pragma once

#include <basis/seadTypes.h>
#include "KingSystem/ActorSystem/actBaseProcLink.h"

namespace ksys::act {
class BaseProc;
}

namespace uking::dmg {

// Entry of the nearest-enemies list in DamageInfoMgr (0x18 bytes).
struct Unk_7100671794_Entry {
    ksys::act::BaseProcLink mLink;
    f32 mDistance = 0;
    bool _14 = false;
};
KSYS_CHECK_SIZE_NX150(Unk_7100671794_Entry, 0x18);

// The object at DamageInfoMgr + 0x4f8 (lane1 s21; no name in the binary; placeholder = address of
// its update function). A list of the 8 nearest enemies (Unk_7100671794_Entry[8], sorted by distance
// from the player), a cooldown (_c0) and spin locks (_cc, _d0). EnemyBattle / EnemyNoticeLimit /
// EnemyPermitAttackSelect / LandHumEnemyFindPlayer use it as an attack permission limiter. Only the
// methods are declared (not decompiled).
class Unk_7100671794 {
public:
    // 0x7100671794: counts the cooldown down and re-sorts the list by the distance to the player.
    void sub_7100671794();
    // 0x7100671a40: starts the cooldown (`frames`) unless it is running; false while it runs.
    bool sub_7100671A40(ksys::act::BaseProc* proc, s32 frames);
    // 0x7100671a64: the cooldown has expired.
    bool sub_7100671A64(ksys::act::BaseProc* proc) const;
    // 0x7100671a74: inserts `entry` into the list; false if it is not one of the nearest `count`.
    bool sub_7100671A74(Unk_7100671794_Entry* entry, s32 count);
    // 0x7100671ed8: whether `proc` is one of the 8 listed enemies.
    bool sub_7100671ED8(ksys::act::BaseProc* proc);
    // 0x7100671f78: removes `proc` from the list.
    void sub_7100671F78(ksys::act::BaseProc* proc);
    // 0x71006720c8
    void sub_71006720C8(ksys::act::BaseProc* proc);

    /* 0x00 */ Unk_7100671794_Entry mEntries[8];
    /* 0xc0 */ f32 _c0;
    /* 0xc4 */ s32 _c4;
    /* 0xc8 */ u32 _c8;
    /* 0xcc */ u32 _cc;
    /* 0xd0 */ u32 _d0;
    /* 0xd4 */ u32 _d4;
};
KSYS_CHECK_SIZE_NX150(Unk_7100671794, 0xd8);

}  // namespace uking::dmg
