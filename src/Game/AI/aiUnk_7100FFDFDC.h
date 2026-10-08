#pragma once

#include <basis/seadTypes.h>

// Placeholder classes (types unknown): the BGM controller objects returned by the BGM manager lookups at
// 0x7100ffdfdc / 0x7100ffdea8 / 0x7100ffe468 / 0x7100ffe5ec / 0x7100ffe6ec (each finds an entry of the list at
// `sub_7100FFD79C()` + 8 by index and casts it; declaration only). Used by the BGM behaviors
// (AssassinBossBgm*, BeastGanonBgm*, EnemyGanonBgmStop, CurseGanonBGMApplyLPF, SandwormBgmControl).

// 0x7100ffdfdc: entry 0xe (the assassin boss BGM).
class Unk_7100ffdfdc {
public:
    // 0x7100ff61bc (4 B, empty; CSV nullsub_4300)
    void sub_7100FF61BC();
    void sub_7100FF61C0();
    void sub_7100FF6220();
    void sub_7100FF6268();
};
Unk_7100ffdfdc* sub_7100FFDFDC();

// 0x7100ffdea8 (the object itself is only tested for null by SandwormBgmControl::m8).
class Unk_7100ffdea8 {
public:
    // 0x710102292c
    void sub_710102292C(bool enable, u32 actor_id);
};
Unk_7100ffdea8* sub_7100FFDEA8();

// Placeholder: the level argument of Unk_7100ffe468::sub_710100FE0C is a one-member aggregate (the original's stack
// temporary is 8-byte aligned, like an enum class / SEAD_ENUM wrapper), not a plain s32.
struct Unk_BgmLevel {
    s32 value = 0;
};

// 0x7100ffe468: entry 0x20 (the Ganon BGM; virtual slot 10 returns a bool).
class Unk_7100ffe468 {
public:
    virtual void m0();
    virtual void m1();
    virtual void m2();
    virtual void m3();
    virtual void m4();
    virtual void m5();
    virtual void m6();
    virtual void m7();
    virtual void m8();
    virtual void m9();
    virtual bool m10();

    // 0x710100fe0c
    void sub_710100FE0C(const Unk_BgmLevel* level);
    // 0x710100ff38
    void sub_710100FF38();
    // 0x71010101ec
    void sub_71010101EC(f32 value);
};
Unk_7100ffe468* sub_7100FFE468();

// 0x7100ffe5ec
class Unk_7100ffe5ec {
public:
    // 0x7101000838
    void sub_7101000838(f32 value);
};
Unk_7100ffe5ec* sub_7100FFE5EC();

// 0x7100ffe6ec: entry 0x1f.
class Unk_7100ffe6ec {
public:
    // 0x7101010c58
    void sub_7101010C58(f32 value);
};
Unk_7100ffe6ec* sub_7100FFE6EC();

// 0x7100ffed80 (declaration only; placeholder name): the byte at +0x88 of SoundMgr::_30->_48 (false if either is null).
bool sub_7100FFED80();
