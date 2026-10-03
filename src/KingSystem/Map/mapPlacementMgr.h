#pragma once

#include <container/seadObjArray.h>
#include <heap/seadDisposer.h>
#include <heap/seadExpHeap.h>
#include <math/seadVector.h>
#include <prim/seadDelegate.h>
#include <prim/seadTypedBitFlag.h>
#include <thread/seadDelegateThread.h>
#include "KingSystem/Utils/Types.h"

namespace ksys::act {
class Actor;
class ClusteredRenderer;
class InstParamPack;
}  // namespace ksys::act

namespace uking {
class VillagerMgr;
}

namespace ksys::map {

class Object;
// Placeholder name (callback argument of the ClusteredRenderer query 0x71012497f8): a stack copy of
// the cluster entry.
struct Unk_71012497f8Entry {
    u8 _0[0x80];
    bool _80;
};
class Placement18;
class PlacementActors;
class PlacementMapMgr;
class PlacementTree;

class PlacementMgr {
    SEAD_SINGLETON_DISPOSER(PlacementMgr)
    PlacementMgr();
    virtual ~PlacementMgr();

    struct TraverseResults {
        sead::PtrArray<act::Actor> pre_actors;
        sead::PtrArray<act::Actor> actors;
        sead::PtrArray<u32> _20;
        sead::PtrArray<u32> _30;
        sead::PtrArray<u32> _40;
        sead::PtrArray<u32> _50;
        sead::PtrArray<map::Object> dragon_item_drop_targets;
        sead::PtrArray<u32> _70;
    };
    KSYS_CHECK_SIZE_NX150(TraverseResults, 0x80);

public:
    void releaseTree();
    void x_3();
    void reset7F0();
    void initClusteredRenderer();
    void auto0();
    bool auto1();
    void x_0(sead::Vector3f* pos, act::InstParamPack* pack);
    void printDebugInfo();
    void loadModel(Object* obj);
    void incrementCounter();
    void x();
    void auto5();
    void auto16();
    bool someFlagCheck() const;
    bool isStaticCompoundReady(const sead::Vector3f& pos, bool x);
    void disableObjStaticCompound(Object* obj);
    // 0x7100e9d3c-like twin at 0x71011e9d3c (placeholder name, declaration only; lane4 s28): the same checks
    // as disableObjStaticCompound, then setStaticCompoundInstanceEnabled(obj, true).
    void enableObjStaticCompound(Object* obj);
    void stubbed();
    void insertTraverseResultPreActor(act::Actor* actor);
    void setFlag8Enabled(bool enabled);
    const char* getEntryUnitConfigName(const Object* obj) const;
    f32 getDeleteDistance(const Object* obj) const;
    f32 getLoadDistancePlus10(const Object* obj) const;
    f32 getDispDistanceComplex(const Object* obj) const;
    bool objStuff(const Object* obj) const;
    void clusteredRendererRequestDraw();
    // 0x71011eb40c: forwards to the ClusteredRenderer (+0x7b8, if any) with `callback` invoked for
    // every cluster within `radius` of `pos`.
    void sub_71011EB40C(const sead::Vector3f* pos, f32 radius, sead::IDelegate1R<Unk_71012497f8Entry*, bool>* callback);
    void updateTimeDivisionFlags(bool on);

    void threadFn(sead::Thread* thread, sead::MessageQueue::Element msg);
    // 0x00000071011eb4dc
    bool auto17(Object* obj);

    enum class MgrFlag {
        _1 = 0x1,
        _2 = 0x2,
        _20 = 0x20,
        _4000 = 0x4000,
        _20000 = 0x20000,
        _40000 = 0x40000,
        _80000 = 0x80000,
        _100000 = 0x100000,
        _200000 = 0x200000,
        _400000 = 0x400000,
        _1000000 = 0x1000000,
    };

    enum class MgrStaticFlags {
        debug = 0x1,
        _8 = 0x8,
        DemoMode = 0x4,
        GrudgeMerge = 0x20,
    };

    bool isGrudgeMerge() const { return sFlags.isOn(MgrStaticFlags::GrudgeMerge); }

    static sead::TypedBitFlag<MgrStaticFlags, u16> sFlags;

    u32 _28;
    u32 _2c = 0;
    u32 _30 = 0;

    u8 TEMP[0x108];
    sead::Delegate2<PlacementMgr, sead::Thread*, sead::MessageQueue::Element> mThreadParams;
    sead::DelegateThread* mThread;
    int mTraverseResultIdx;
    u16 mRequestedMsg = 0;

    sead::Vector3f mCameraPos{};
    sead::Vector3f mPlayerPos{};
    sead::Vector3f mPrevPlayerPos{};
    sead::ExpHeap* mDynamicHeap;
    sead::ExpHeap* mThreadHeap;
    sead::ExpHeap* mVillagerHeap;
    sead::ExpHeap* mTraverseResultHeap;
    void* mActorCreator;
    u32 mLoadedActorCount;
    void* mTeraSystem;
    s32 mIntTime;
    f32 mTime;
    bool mTimeUpdated;

    s32 mMassMemoryUsage;
    s32 mClusteredMemoryUsage;
    u16 _1e4;
    void* mDebugHeap;
    PlacementActors* mPlacementActors;

    // NOTE (lane4 s22): the pointer that used to be declared here (`mVillagerManager`) is not the VillagerMgr;
    // initAndStartPlacementThread (0x71011e5944) stores the VillagerMgr at 0x218 (`mVillagerMgr` below).
    // lane3 s19: the low half is an s32 read by PlayerHellNoFade::calc_ (`>= 11` => finished).
    s32 _1f8;
    u32 _1fc;

    PlacementMapMgr* mPlacementMapMgr;
    Placement18* mPlacement18;
    u8 _210[8];
    uking::VillagerMgr* mVillagerMgr;
    u8 TEMP2[0xc];
    u32 mNumStaticObjs;
    u32 mActorDataMapSize;
    sead::Vector3f _234;
    u8 TEMP2_[0x38];

    u32 _278;
    sead::Vector3f _27c;
    u32 _288;

    s32 mPreActorNumDone;
    s32 mLoadActorNumTotal;
    sead::Vector3f mPrevCameraPos{};
    f32 mDeltaCameraDistance;
    sead::FixedSafeString<256> mStr1;
    sead::FixedSafeString<256> mStr2;
    sead::FixedSafeString<256> mStr3;
    sead::CriticalSection mCS{};

    u64 mStartTick;
    u8 TEMP3[0x4c];

    sead::TypedBitFlag<MgrFlag, sead::Atomic<u32>> mFlags;
    bool mThreadStarted = false;
    bool _689 = false;
    bool _68a = false;
    u32 _68c;
    u32 _690;
    u32 mMessage = 0;
    u32 mJobType = 0;
    TraverseResults mTraverseResults[2];
    PlacementTree* mPlacementTree = nullptr;
    u32 _7a8;
    void* mMassRenderer = nullptr;
    act::ClusteredRenderer* mClusteredRenderer = nullptr;
    void* mPlacementNavi = nullptr;
    u32 mMassRendererReqCount = 0;
    u32 mMassRendererStatus = 0;

    // fix these
    sead::DelegateFunc mInvoker{};
    u8 TEMP4[0x10];

    s32 _7f0 = -1;

    sead::DelegateFunc mInvoker2{};
    u8 TEMP5[0x10];
};
KSYS_CHECK_SIZE_NX150(PlacementMgr, 0x818);
static_assert(offsetof(PlacementMgr, mThreadStarted) == 0x688);
static_assert(offsetof(PlacementMgr, mPlacementMapMgr) == 0x200);
static_assert(offsetof(PlacementMgr, mVillagerMgr) == 0x218);
static_assert(offsetof(PlacementMgr, mNumStaticObjs) == 0x22c);
static_assert(offsetof(PlacementMgr, mPreActorNumDone) == 0x28c);

}  // namespace ksys::map
