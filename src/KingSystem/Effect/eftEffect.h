#pragma once

#include <heap/seadDisposer.h>
#include <container/seadSafeArray.h>
#include <thread/seadCriticalSection.h>
#include <math/seadVector.h>
#include <xlink2/xlink2HandleELink.h>
#include "KingSystem/Effect/eftEffectModelMgr.h"
#include "KingSystem/Physics/physDefines.h"
#include "KingSystem/XLink/xlinkActorUtil.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::act {
class Actor;
class PlayerLink;
}

namespace uking::act {
class Unk_7102459cc0;
}

namespace ksys::eft {

// Effect + 0x9fe0 (placeholder name): a locked table of 32 actor slots (0x30 bytes each, the actor
// pointer first), a count at +0x600 and the lock at +0x608.
class Unk_EffectActorTable {
public:
    void sub_7100DA2118();
    bool sub_7100DA216C(act::Actor* actor, const sead::Vector3f& position);
    // 0x7100da2330 (placeholder name): clears the slot holding `actor` and decrements
    // the count; false when the actor is not in the table. LumberjackTree's destructor calls it.
    bool sub_7100DA2330(act::Actor* actor);

private:
    struct Entry {
        act::Actor* actor;
        sead::Vector3f position;
        u8 _14[4];
        xlink2::HandleELink handle;
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
    void sub_71011B7930();
    void calcMostProbably2();

    // 0x71011b2a34 (placeholder name; `this` is not read): water height at `pos` (a water-layer ray cast or the
    // terrain water query) against the terrain height. Writes the water height (or the terrain height when
    // there is no water) and water depth; returns whether `pos` has water above the terrain.
    bool sub_71011B2A34(const sead::Vector3f* pos, f32* out_depth, f32* out_height,
                        phys::Material* material, s32* submaterial, sead::Vector3f* out_normal,
                        bool use_raycast);

    void setFlags(u32 mask) { mFlags |= mask; }
    void clearFlags(u32 mask) { mFlags &= ~mask; }
    bool hasFlags(u32 mask) const { return (mFlags & mask) != 0; }
    // Read by UKingEmitEffectLoopAction::calc_ (compared with 2); name unknown.
    s32 get193e0() const { return _193e0; }
    Unk_EffectActorTable& getActorTable9FE0() { return _9fe0; }
    EffectModelMgr& getModelMgr() { return mModelMgr; }

    // 0x71011b7404: a printf-style debug log whose body is compiled out (only the va_list spill is left).
    void debugLog(const char* format, ...);
    // 0x71011b62e8: resets the effect level to 0x1e and the xlink user instance, if any.
    void initBeforeStageGenB();
    // 0x71011b88b0: adds a demo resource id to the fixed 32-entry table.
    void addDemoResourceId(u32 id);
    // 0x71011b8950: removes a demo resource id from the table (XLink::resolveDeleteVfxResource).
    void removeDemoResourceId(u32 id);
    // 0x71011b872c: searches and emits an ELink event through the xlink user instance.
    void searchAndEmit(const sead::SafeString& name, xlink2::HandleELink* handle);

private:
    u8 _38[0x9fb8 - 0x38];

public:
    // The player link (set by ksys::setPlayerLink) and the camera actor (set by ksys::sub_7100F40428).
    /* 0x9fb8 */ act::PlayerLink* _9fb8;
    /* 0x9fc0 */ uking::act::Unk_7102459cc0* _9fc0;

private:
    /* 0x9fc8 */ s32 _9fc8;
    u8 _9fcc[0x9fe0 - 0x9fcc];
    Unk_EffectActorTable _9fe0;
    EffectModelMgr mModelMgr;
    u8 _a628_end[0x192c8 - 0xa628 - sizeof(EffectModelMgr)];
    bool _192c8;
    u8 _192c9[0x192f4 - 0x192c9];
    u32 mFlags;
    u8 _192f8[0x19300 - 0x192f8];
    /* 0x19300 */ xlink2::UserInstance* mUserInstance = nullptr;
    u8 _19308[0x193e0 - 0x19308];
    s32 _193e0;
    u8 _193e4[0x19c38 - 0x193e4];
    Unk_71012419b4 mFieldEnvEffect;
    u8 _19c58[0x2a43c - 0x19c58];
    /// Demo resource ids (initialised to -1 by the constructor).
    /* 0x2a43c */ s32 mDemoResourceIds[32];
    u8 _2a4bc[4];
    /* 0x2a4c0 */ sead::CriticalSection mDemoResourceCS;
    u8 _2a500[0x2a750 - 0x2a500];
};
static_assert(sizeof(Effect) == 0x2a750);

}  // namespace ksys::eft
