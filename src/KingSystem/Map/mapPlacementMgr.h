#pragma once

#include <container/seadBuffer.h>
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
class PlacementMgr;

// Placeholder name (0x71011e3d6c, CSV MassRenderer::x_2; the class of PlacementMgr::mMassRenderer): declaration only.
class MassRenderer {
public:
    // 0x71011e3d6c (804 B): updates the object's entry after its render flag changed.
    void x_2(PlacementMgr* mgr, Object* obj);
    // 0x71011e4090 / 0x71011e1ffc / 0x71011e264c (CSV unnamed / MassRenderer::setup / MassRenderer::update; declaration
    // only; placeholder names and parameters).
    void sub_71011E4090(PlacementMgr* mgr, bool a);
    void sub_71011E1FFC(const void* traverse_results, const sead::Vector3f* camera_pos, f32 distance);
    void sub_71011E264C(PlacementMgr* mgr);
    // 0x71011e41f4: whether `p` is one of the three pointers at 0xc8 / 0x138 / 0x1a8 (the draw arrays; the type of `p`
    // is unknown, it is only compared).
    bool sub_71011E41F4(const void* p) const;

    // 0x71011eb32c (PlacementMgr forwards to this inline test): whether bit `idx` of the bit buffer of the active slot
    // is set.
    bool isBitSet(u32 idx) const { return (_90[1 + _78].bits[idx >> 5] & (1u << (idx & 0x1f))) != 0; }

    struct Slot {
        sead::Buffer<u32> bits;
        u8 _10[0x38 - 0x10];
        /* 0x38 */ void* _38;
        u8 _40[0x70 - 0x40];
    };

    u8 _0[0x78];
    /* 0x78 */ s32 _78;
    u8 _7c[0x90 - 0x7c];
    /* 0x90 */ Slot _90[3];
};

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
    // 0x71011e9c28 (CSV __auto4; placeholder name, declaration only): `enabled` changes the object's render flag
    // (mass renderer / forest renderer update).
    void sub_71011E9C28(Object* obj, bool enabled);
    // 0x71011eb46c (CSV __auto19; placeholder name): PlacementActors::sub_7100D52CA4(obj).
    void sub_71011EB46C(Object* obj);
    // 0x71011e4da8 (CSV invoked2): runs invoked2_ (0x71011ea4c8, declaration only) and returns true.
    bool invoked2(void* arg);
    void invoked2_();
    // 0x71011e54e8 (CSV initBeforeStageGenB)
    void initBeforeStageGenB();
    // 0x71011e6ee0 (CSV x; placeholder name): the per-frame update of the placement helpers.
    void sub_71011E6EE0();
    // 0x71011e6c60 (CSV x_5; placeholder name)
    bool sub_71011E6C60();
    // 0x71011e6260 (CSV initPlacementTree)
    void initPlacementTree(bool skip_rebuild);
    // 0x71011e6308 (CSV placeActors)
    void placeActors();
    // 0x71011e5734 / 0x71011e5678 (CSV stopThread / stopThreads)
    void stopThread();
    void stopThreads();
    // 0x71011e9db0 (CSV __auto8; placeholder name): unless flag 2 is set: PlacementActors::x_7 and the clustered
    // renderer's 0x1244598 step (not while flag 0x40 / `_690` bit 6 is set).
    void sub_71011E9DB0();
    // 0x71011e63fc (CSV x_0; placeholder name): the map cell of `pos` (1000 x 1000 cells, origin -5000 / -4000) and the
    // position inside the cell.
    struct CellPos {
        s32 col;
        s32 row;
        f32 x;
        f32 z;
    };
    void sub_71011E63FC(const sead::Vector3f* pos, CellPos* out);
    // 0x71011eb2ac / 0x71011eb460 (CSV x_8 / x_7; placeholder names): forward to the mass / forest renderers.
    void sub_71011EB2AC();
    u32 sub_71011EB460() const;
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
    // 0x71011eb37c / 0x71011eb3f8 / 0x71011eb428 / 0x71011eb450 (placeholder names): forwarders to the clustered / mass
    // renderers.
    bool sub_71011EB37C() const;
    bool sub_71011EB32C(u32 idx) const;
    void sub_71011EB3F8(const sead::Vector3f* pos, f32 radius, bool x,
                        sead::IDelegate1R<Unk_71012497f8Entry*, bool>* callback);
    void sub_71011EB428(const sead::Vector3f* pos, f32 radius, bool x,
                        sead::IDelegate1R<Unk_71012497f8Entry*, bool>* callback);
    bool sub_71011EB450(const void* p);

    void threadFn(sead::Thread* thread, sead::MessageQueue::Element msg);
    // 0x00000071011eb4dc
    bool auto17(Object* obj);

    enum class MgrFlag {
        _1 = 0x1,
        _2 = 0x2,
        _20 = 0x20,
        _40 = 0x40,
        _4000 = 0x4000,
        _20000 = 0x20000,
        _40000 = 0x40000,
        _80000 = 0x80000,
        _100000 = 0x100000,
        _100 = 0x100,
        _10000 = 0x10000,
        _200000 = 0x200000,
        _2000000 = 0x2000000,
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
    u8 TEMP2[8];
    s32 _228;
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
    u8 _690;  // bit 6 is tested by sub_71011E9DB0
    u8 _691[3];
    u32 mMessage = 0;
    u32 mJobType = 0;
    TraverseResults mTraverseResults[2];
    PlacementTree* mPlacementTree = nullptr;
    u32 _7a8;
    MassRenderer* mMassRenderer = nullptr;
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
