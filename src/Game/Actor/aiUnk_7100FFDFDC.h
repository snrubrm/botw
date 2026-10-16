#pragma once

#include <basis/seadTypes.h>
#include "Game/gameUnkRttiPlaceholders.h"
#include "KingSystem/Sound/sndBgmMgr.h"

// Placeholder classes (types unknown): the BGM controller objects returned by the BGM manager lookups at
// 0x7100ffdfdc / 0x7100ffdea8 / 0x7100ffe468 / 0x7100ffe5ec / 0x7100ffe6ec (each finds an entry of the list at
// `sub_7100FFD79C()` + 8 by index and casts it; declaration only). Used by the BGM behaviors
// (AssassinBossBgm*, BeastGanonBgm*, EnemyGanonBgmStop, CurseGanonBGMApplyLPF, SandwormBgmControl).

// 0x7100ffdfdc: entry 0xe (the assassin boss BGM): ksys::snd::sub_7100FFDFDC (sndBgmMgr.h) returns it as
// ksys::snd::Unk_710260f048.
using Unk_7100ffdfdc = ksys::snd::Unk_710260f048;
using ksys::snd::sub_7100FFDFDC;

// 0x7100ffdea8 (the object itself is only tested for null by SandwormBgmControl::m8).
class Unk_7100ffdea8 {
public:
    // 0x710102292c
    void sub_710102292C(bool enable, u32 actor_id);
};
Unk_7100ffdea8* sub_7100FFDEA8();

// 0x7100ffe468: entry 0x20, the Ganon beast BGM Unk_71024fec18 (ksys::snd::sub_7100FFE468, sndBgmMgr.h).
using Unk_7100ffe468 = Unk_71024fec18;
using ksys::snd::sub_7100FFE468;

// FFE520/FFE5EC both cast to the existing Remains boss BGM RTTI owner.
class Unk_71024fd448;
using Unk_7100ffe5ec = Unk_71024fd448;
Unk_71024fd448* sub_7100FFE520(const ksys::snd::RemainsBossBgmType* type);
Unk_7100ffe5ec* sub_7100FFE5EC();

// 0x7100ffe6ec: entry 0x1f, the Ganon BGM Unk_71024fed48 (ksys::snd::sub_7100FFE6EC, sndBgmMgr.h).
using Unk_7100ffe6ec = Unk_71024fed48;
using ksys::snd::sub_7100FFE6EC;


// 0x7100ffeb28 (declaration only): BGM kind 35, RTTI-checked as the priest boss BGM.
class Unk_71024fe970;
Unk_71024fe970* sub_7100FFEB28();
