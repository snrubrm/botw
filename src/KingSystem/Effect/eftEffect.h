#pragma once

#include <heap/seadDisposer.h>
#include <container/seadSafeArray.h>
#include <thread/seadCriticalSection.h>
#include <math/seadVector.h>
#include <xlink2/xlink2HandleELink.h>
#include "KingSystem/Effect/eftEffectModelMgr.h"
#include "KingSystem/Effect/eftRainbow.h"
#include "KingSystem/Physics/physDefines.h"
#include "KingSystem/Resource/resHandle.h"
#include "KingSystem/XLink/xlinkActorUtil.h"
#include "KingSystem/Utils/Types.h"

namespace xlink2 {
class ResAssetCallTable;
class ResourceAccessorELink;
}

namespace ksys::act {
class Actor;
class PlayerLink;
}

namespace uking::act {
class Unk_7102459cc0;
}

namespace ksys::eft {

class AmbientEffectMgr;

// Placeholder for the two u16 ids xlink2 writes back through the ResEset out parameter. lib/xlink2
// models ResEset as an empty struct; this is the layout the game code stores into.
struct Unk_ResEset {
    u16 _0;
    u16 _2;
};

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
    friend class Rainbow;
    // The bird emitter queries the stage's forest-density table directly into its retained sample.
    friend class Unk_7102512658;
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
    // Bit 13 (byte +0x192f5 bit 5) makes calc skip the ambient effect manager. Meaning unknown.
    static constexpr u32 cFlag_Unk2000 = 0x2000;
    // Bit 25 (byte +0x192f7 bit 1) makes calcMostProbably2 run the 32x32 water-query grid around the
    // player. Meaning unknown.
    static constexpr u32 cFlag_Unk2000000 = 0x02000000;

    // 0x71011b7f60 (placeholder name): the placement effect step ksys::CalcPlacementMgr2 runs while
    // the terrain manager is not ready.
    void sub_71011B7F60();
    // 0x71011b63ac / 0x71011b7b0c (CSV calcMostProbably / calcMostProbably2; declaration only): called by
    // MCMgr::invoked3.
    void calcMostProbably();
    void sub_71011B7930();
    void calcMostProbably2();
    // 0x71011b6b48 / 0x71011b6ff8 / 0x71011b742c (placeholder names): the parallel particle group steps
    // calcMostProbably2 runs before the water grid.
    void calcGsysParallel();
    void x_0();
    void x_1();
    // 0x71011b8584 / 0x71011b8658 (CSV Effect::__auto4 / __auto5; declared only, placeholder names): called by
    // EventFlowTimeline::m8 with (on, true) when a timeline pauses / resumes
    void sub_71011B8584(bool on);
    void sub_71011B8658(bool on);
    // 0x71011b6154 (declared only): clears and sets up the particle groups of the model scene.
    void initParticleGroups(bool flag);

    // 0x71011b2a34 (placeholder name; `this` is not read): water height at `pos` (a water-layer ray cast or the
    // terrain water query) against the terrain height. Writes the water height (or the terrain height when
    // there is no water) and water depth; returns whether `pos` has water above the terrain.
    bool sub_71011B2A34(const sead::Vector3f* pos, f32* out_depth, f32* out_height,
                        phys::Material* material, s32* submaterial, sead::Vector3f* out_normal,
                        bool use_raycast);
    // 0x71011b2d34 (placeholder name; `this` is not read): the ground ray cast below `pos`; true when
    // the hit material is Water, Lava or Bog. Writes the hit height and, when the corresponding out
    // pointers are given, the material, the sub-material index and the hit normal.
    bool sub_71011B2D34(const sead::Vector3f* pos, f32* out_height, phys::Material* out_material,
                        s32* out_submaterial, sead::Vector3f* out_normal);

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
    // 0x71011b5fe8 (CSV Effect::initBeforeStageGen; declaration only).
    void initBeforeStageGen(sead::Heap* heap);
    // 0x71011b5ed4: loads the ELink2 database through the handle at +0x9a98 and hands its raw
    // data to the xlink system.
    void loadELinkDatabase(const sead::SafeString& requester);
    // 0x71011b88b0: adds a demo resource id to the fixed 32-entry table.
    void addDemoResourceId(u32 id);
    // 0x71011b8950: removes a demo resource id from the table (XLink::resolveDeleteVfxResource).
    void removeDemoResourceId(u32 id);
    // 0x71011b872c: searches and emits an ELink event through the xlink user instance.
    void searchAndEmit(const sead::SafeString& name, xlink2::HandleELink* handle);
    void kill_0();
    void kill();
    // 0x71011b7da0 (placeholder name): whether the wind vector selects an enabled bit of the wind
    // stats mask (a 5x5 wind grid).
    bool sub_71011B7DA0(const sead::Vector3f* wind);
    // 0x71011b630c: runs the ambient effect manager when the scene and camera are ready.
    void calc();
    void updatePlayerPos(const sead::Matrix34f& matrix, const sead::Matrix34f& alternate);
    // 0x71011b87ac: queries the forest_density table selected during stage initialization.
    f32 queryForestDensity(const sead::Vector3f* position);
    // 0x71011b2ee0 (placeholder parameter type; lib models ResEset as empty): replaces the
    // resource / emitter set ids of a DummyBlank or DummyBlankLoop replacement set.
    void replaceResEset(Unk_ResEset* eset, const xlink2::ResAssetCallTable& table,
                        const xlink2::ResourceAccessorELink& accessor, const char* name);
    // 0x71011b3e84 (placeholder name): interpolates the effect-level scale curve at `level`
    // (0 outside 0..15, the last sample from 15 up).
    f32 getLevelScaleMaybe(f32 level) const;

private:
    u8 _38[0x96b0 - 0x38];
    // Set to skip Effect::calc.
    bool _96b0;
    // Set while the timeline is paused (sub_71011B8658).
    bool _96b1;
    u8 _96b2[0x9a98 - 0x96b2];
    // Loads ELink2/ELink2DB.belnk (loadELinkDatabase).
    ksys::res::Handle mELinkDBHandle;
    u8 _9ae8[0x9b8c - 0x9ae8];
    u8 _9b8c;
    u8 _9b8d;
    u8 _9b8e[2];
    // Initialised to 4.0 / 0.0 by initBeforeStageGen; the two stores merge into one 64-bit store.
    f32 _9b90;
    f32 _9b94;
    bool _9b98;
    u8 _9b99[3];
    s32 _9b9c;
    // Read by initParticleGroups: skips the fourth particle group when set.
    u8 _9ba0;
    u8 _9ba1[0x9fb8 - 0x9ba1];

public:
    // The player link (set by ksys::setPlayerLink) and the camera actor (set by ksys::sub_7100F40428).
    /* 0x9fb8 */ act::PlayerLink* _9fb8;
    /* 0x9fc0 */ uking::act::Unk_7102459cc0* _9fc0;

private:
    /* 0x9fc8 */ s32 _9fc8;
    u8 _9fcc[0x9fe0 - 0x9fcc];
    Unk_EffectActorTable _9fe0;
    EffectModelMgr mModelMgr;
    u8 _a628_end[0x192b0 - 0xa628 - sizeof(EffectModelMgr)];
    f32 _192b0;
    f32 _192b4;
    u8 _192b8[0x192c8 - 0x192b8];
    bool _192c8;
    u8 _192c9[0x192f4 - 0x192c9];
    u32 mFlags;
    u8 _192f8[0x19300 - 0x192f8];
    /* 0x19300 */ xlink2::UserInstance* mUserInstance = nullptr;
    // Stats table of the wind mask queried by sub_71011B7DA0.
    /* 0x19308 */ void* mWindStatsMaybe = nullptr;
    void* mForestDensityStats;
    // The water-effect placement ring x_0 steps around the camera: an angle advanced 12 degrees
    // per frame, a countdown timer, the sampled water distance and the effect state.
    f32 mWaterRingAngle;
    f32 mWaterRingTimer;
    f32 mWaterRingDistance;
    s32 mWaterRingState;
    AmbientEffectMgr* mAmbientEffectMgr;
    u8 _19330[0x19370 - 0x19330];
    Rainbow mRainbow;
    s32 _193e0;
    u8 _193e4[4];
    // Counted up by sub_71011B8584 / sub_71011B8658 while the particle groups are off; reset to 0 otherwise.
    s32 _193e8;
    u8 _193ec[0x19c38 - 0x193ec];
    Unk_71012419b4 mFieldEnvEffect;
    // The camera water distance the effect uses (x_1): the running distance, the per-direction
    // distances, the direction index and the player distance.
    f32 mWaterDistanceMaybe;
    f32 mWaterDirDistances[3];
    s32 mWaterDirIndex;
    f32 mPlayerWaterDistance;
    u8 _19c70[0x2a3e0 - 0x19c70];
    // 0x2a3e0 (Effect::init): the sixteen samples of the effect-level scale curve.
    f32 mLevelScaleTable[16];
    u8 _2a420[0x2a42c - 0x2a420];
    s32 _2a42c;
    u8 _2a430[0x2a43c - 0x2a430];
    /// Demo resource ids (initialised to -1 by the constructor).
    /* 0x2a43c */ sead::SafeArray<s32, 32> mDemoResourceIds;
    u8 _2a4bc[4];
    /* 0x2a4c0 */ sead::CriticalSection mDemoResourceCS;
    u8 _2a500[0x2a750 - 0x2a500];
};
static_assert(sizeof(Effect) == 0x2a750);

}  // namespace ksys::eft
