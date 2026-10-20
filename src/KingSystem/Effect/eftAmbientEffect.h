#pragma once

#include <container/seadSafeArray.h>
#include <math/seadVector.h>
#include <thread/seadCriticalSection.h>
#include "KingSystem/Effect/eftEffectUnkHelpers.h"
#include "KingSystem/XLink/xlinkActorUtil.h"

namespace ksys::map {
struct Unk_71012497f8Entry;
}

namespace ksys::eft {

class Effect;

// The four emitters constructed at 0x71011b58dc have five-slot vtables. Their
// common state holds three ELink/SLink pairs; 0x710126e51c cycles through them.
// Names follow the asset keys used by the derived calc methods.
class AmbientEffectEmitter {
public:
    virtual ~AmbientEffectEmitter() = default;
    virtual void calc(Effect* effect) = 0;
    virtual void reset() = 0;
    virtual bool getSpawnPosition(Effect* effect, const sead::Vector3f& position,
                                  sead::Vector3f& output) = 0;

    void resetCommon();
    Unk_71012419b4* nextHandle();
    void calcPosition(Effect* effect, sead::Vector3f* output);

    sead::SafeArray<Unk_71012419b4, 3> mHandles;
    u32 mHandleIndex;
    bool mPending;
    f32 mAngle;
    f32 mTimer;
    f32 mInterval;
    f32 mDistance;
    f32 mRadius;
};
KSYS_CHECK_SIZE_NX150(AmbientEffectEmitter, 0x88);
static_assert(offsetof(AmbientEffectEmitter, mHandles) == 8);
static_assert(offsetof(AmbientEffectEmitter, mHandleIndex) == 0x68);
static_assert(offsetof(AmbientEffectEmitter, mAngle) == 0x70);
static_assert(offsetof(AmbientEffectEmitter, mTimer) == 0x74);
static_assert(offsetof(AmbientEffectEmitter, mInterval) == 0x78);
static_assert(offsetof(AmbientEffectEmitter, mDistance) == 0x7c);
static_assert(offsetof(AmbientEffectEmitter, mRadius) == 0x80);

// Vtable 0x7102517ea8, embedded at AmbientEffectMgr +0x48.
class MothEffectEmitter : public AmbientEffectEmitter {
public:
    void calc(Effect* effect) override;
    void reset() override;
    bool getSpawnPosition(Effect* effect, const sead::Vector3f& position,
                          sead::Vector3f& output) override {
        return true;
    }
    s32 mLightIndex;
};
KSYS_CHECK_SIZE_NX150(MothEffectEmitter, 0x88);
static_assert(offsetof(MothEffectEmitter, mLightIndex) == 0x84);

// Vtable 0x7102517ee0, embedded at +0xd0.
class SmallFishEffectEmitter : public AmbientEffectEmitter {
public:
    void calc(Effect* effect) override;
    void reset() override;
    bool getSpawnPosition(Effect* effect, const sead::Vector3f& position,
                          sead::Vector3f& output) override;
    f32 mMinWaterDepth;
};
KSYS_CHECK_SIZE_NX150(SmallFishEffectEmitter, 0x88);
static_assert(offsetof(SmallFishEffectEmitter, mMinWaterDepth) == 0x84);

// Vtable 0x7102517f18, embedded at +0x158.
class FlyEffectEmitter : public AmbientEffectEmitter {
public:
    void calc(Effect* effect) override;
    void reset() override;
    bool getSpawnPosition(Effect* effect, const sead::Vector3f& position,
                          sead::Vector3f& output) override;
    f32 mMaxWaterDepth;
    f32 mMinForestDensity;
};
KSYS_CHECK_SIZE_NX150(FlyEffectEmitter, 0x90);
static_assert(offsetof(FlyEffectEmitter, mMaxWaterDepth) == 0x84);
static_assert(offsetof(FlyEffectEmitter, mMinForestDensity) == 0x88);

// Vtable 0x7102517f50, embedded at +0x1e8.
class ButterflyEffectEmitter : public AmbientEffectEmitter {
public:
    void calc(Effect* effect) override;
    void reset() override;
    bool getSpawnPosition(Effect* effect, const sead::Vector3f& position,
                          sead::Vector3f& output) override;
    // 0x710126fa80: counts matching clustered flower entries for getSpawnPosition.
    bool countFlower(map::Unk_71012497f8Entry* entry);
    f32 mMinFlowers;
    s32 mFlowerCount;
};
KSYS_CHECK_SIZE_NX150(ButterflyEffectEmitter, 0x90);
static_assert(offsetof(ButterflyEffectEmitter, mMinFlowers) == 0x84);
static_assert(offsetof(ButterflyEffectEmitter, mFlowerCount) == 0x88);

// Vtable 0x7102517db8. The constructor and destructor construct/destroy the
// CriticalSection at +0x50. Requests are queued under that lock and processed by calc.
class AmbientEffectRequest {
public:
    virtual ~AmbientEffectRequest() = default;
    virtual void reset();
    virtual void emit(const sead::Vector3f& position);

    void request(const sead::Vector3f& position);
    void calc();

    Unk_71012419b4 mHandle;
    sead::Vector3f mPosition;
    bool mHasPosition;
    f32 mDistance;
    bool mPending;
    sead::Vector3f mRequestedPosition;
    sead::CriticalSection mCS;
};
KSYS_CHECK_SIZE_NX150(AmbientEffectRequest, 0x90);
static_assert(offsetof(AmbientEffectRequest, mPosition) == 0x28);
static_assert(offsetof(AmbientEffectRequest, mHasPosition) == 0x34);
static_assert(offsetof(AmbientEffectRequest, mPending) == 0x3c);
static_assert(offsetof(AmbientEffectRequest, mRequestedPosition) == 0x40);
static_assert(offsetof(AmbientEffectRequest, mCS) == 0x50);

// Four derived request vtables at 0x7102517de8/7e18/7e48/7e78.
class FireflyEffectRequest : public AmbientEffectRequest {
public:
    void emit(const sead::Vector3f& position) override;
};
class DragonflyEffectRequest : public AmbientEffectRequest {
public:
    void emit(const sead::Vector3f& position) override;
};
class BlueDragonflyEffectRequest : public AmbientEffectRequest {
public:
    void emit(const sead::Vector3f& position) override;
};
class YellowDragonflyEffectRequest : public AmbientEffectRequest {
public:
    void emit(const sead::Vector3f& position) override;
};

// Effect::init allocates 0x4b8, constructs it via 0x71011b58dc and stores it at
// Effect +0x19328. reset/calc are 0x710126fccc/0x710126fe94.
class AmbientEffectMgr {
public:
    AmbientEffectMgr();
    void reset();
    void calc(Effect* effect);

    Unk_7102512640 mGoose;
    Unk_7102512658 mLittleBird;
    MothEffectEmitter mMoth;
    SmallFishEffectEmitter mSmallFish;
    FlyEffectEmitter mFly;
    ButterflyEffectEmitter mButterfly;
    FireflyEffectRequest mFirefly;
    DragonflyEffectRequest mDragonfly;
    BlueDragonflyEffectRequest mBlueDragonfly;
    YellowDragonflyEffectRequest mYellowDragonfly;
};
KSYS_CHECK_SIZE_NX150(AmbientEffectMgr, 0x4b8);
static_assert(offsetof(AmbientEffectMgr, mLittleBird) == 0x18);
static_assert(offsetof(AmbientEffectMgr, mMoth) == 0x48);
static_assert(offsetof(AmbientEffectMgr, mSmallFish) == 0xd0);
static_assert(offsetof(AmbientEffectMgr, mFly) == 0x158);
static_assert(offsetof(AmbientEffectMgr, mButterfly) == 0x1e8);
static_assert(offsetof(AmbientEffectMgr, mFirefly) == 0x278);
static_assert(offsetof(AmbientEffectMgr, mDragonfly) == 0x308);
static_assert(offsetof(AmbientEffectMgr, mBlueDragonfly) == 0x398);
static_assert(offsetof(AmbientEffectMgr, mYellowDragonfly) == 0x428);

}  // namespace ksys::eft
