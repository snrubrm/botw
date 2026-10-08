#pragma once

#include <heap/seadDisposer.h>
#include <container/seadSafeArray.h>
#include <thread/seadCriticalSection.h>
#include "KingSystem/Utils/Types.h"

namespace ksys::act {
class Actor;
class PlayerLink;
}

namespace ksys::eft {

// Effect + 0x9fe0 (placeholder name): a locked table of 32 actor slots (0x30 bytes each, the actor
// pointer first), a count at +0x600 and the lock at +0x608.
class Unk_EffectActorTable {
public:
    void sub_7100DA2118();
    // 0x7100da2330 (placeholder name): clears the slot holding `actor` and decrements
    // the count; false when the actor is not in the table. LumberjackTree's destructor calls it.
    bool sub_7100DA2330(act::Actor* actor);

private:
    struct Entry {
        act::Actor* actor;
        u8 _8[0x20];
        bool _28;
        u8 _29[7];
    };
    sead::SafeArray<Entry, 32> _0;
    s32 mCount;
    u8 _604[4];
    sead::CriticalSection mCS;
};

// The effect manager singleton (CSV: Effect::createInstance 0x71011b3fb0, ctor 0x71011b403c; instance
// pointer 0x7102621598, size 0x2a750, singleton disposer at +0x18). The namespace is a guess. Only
// the flags word used by game code is declared, at its original offset.
class Effect {
    u8 _8[0x10];
    SEAD_SINGLETON_DISPOSER(Effect)
    Effect();
    virtual ~Effect();

public:
    // Bits of mFlags. Bit 12 is exposed to xlink as global property 0x28 (XLink::calc); WaterSurfaceBase
    // sets it while its "move" sound event is running.
    static constexpr u32 cFlag_WaterSurfaceMaybe = 0x1000;
    // Tested by ItemConductor::calc_ (a byte load of bit 0 at +0x192f5); meaning unknown.
    static constexpr u32 cFlag_Unk100 = 0x100;

    // 0x71011b63ac / 0x71011b7b0c (CSV calcMostProbably / calcMostProbably2; declaration only): called by
    // MCMgr::invoked3.
    void calcMostProbably();
    void calcMostProbably2();

    void setFlags(u32 mask) { mFlags |= mask; }
    void clearFlags(u32 mask) { mFlags &= ~mask; }
    bool hasFlags(u32 mask) const { return (mFlags & mask) != 0; }
    // Read by UKingEmitEffectLoopAction::calc_ (compared with 2); name unknown.
    s32 get193e0() const { return _193e0; }
    Unk_EffectActorTable& getActorTable9FE0() { return _9fe0; }

private:
    u8 _38[0x9fb8 - 0x38];

public:
    // The player link (set by ksys::setPlayerLink) and the camera actor (set by ksys::sub_7100F40428).
    /* 0x9fb8 */ act::PlayerLink* _9fb8;
    /* 0x9fc0 */ void* _9fc0;

private:
    u8 _9fc8[0x9fe0 - 0x9fc8];
    Unk_EffectActorTable _9fe0;
    u8 _9fe0_end[0x192f4 - 0x9fe0 - sizeof(Unk_EffectActorTable)];
    u32 mFlags;
    u8 _192f8[0x193e0 - 0x192f8];
    s32 _193e0;
    u8 _193e4[0x2a750 - 0x193e4];
};
static_assert(sizeof(Effect) == 0x2a750);

}  // namespace ksys::eft
