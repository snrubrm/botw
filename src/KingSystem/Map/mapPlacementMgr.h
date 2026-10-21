#pragma once

#include <container/seadBuffer.h>
#include <container/seadObjArray.h>
#include <container/seadPtrArray.h>
#include <container/seadObjArray.h>
#include <heap/seadDisposer.h>
#include <heap/seadExpHeap.h>
#include <math/seadVector.h>
#include <math/seadBoundBox.h>
#include <prim/seadDelegate.h>
#include <prim/seadSafeString.h>
#include <cstddef>
#include <prim/seadTypedBitFlag.h>
#include <thread/seadCriticalSection.h>
#include <thread/seadDelegateThread.h>
#include "KingSystem/Utils/Types.h"

namespace gsys {
class ModelUnit;
class Model;
class ModelDrawObj;
}

namespace ksys::act {
class Actor;
class ClusteredRenderer;
class InstParamPack;
}  // namespace ksys::act

// The "PlacementNavi" object (getName at 0x71011ed3cc); placeholder class in Game/gameUnkRttiPlaceholders.h.
class Unk_7102513630;

namespace uking {
class VillagerMgr;
}

namespace ksys::xlink {
class XLink;
}

namespace ksys::tera {
class System;
}

namespace ksys {
class Task;
}  // namespace ksys

namespace ksys::map {

class Object;
class PlacementMgr;
class ActorData;

s32 sub_7100EDB6E0(bool* out_below, f32* out_height, tera::System* system,
                   const sead::Vector3f* pos);

// Placeholder name (0x71011e3d6c, CSV MassRenderer::x_2; the class of PlacementMgr::mMassRenderer): declaration only.
class MassRenderer {
public:
    // 0x71011e1694: releases the models and the entry pool.
    ~MassRenderer();
    // 0x71011e1904 / 0x71011e190c: begin and advance the three-model cleanup.
    void beginCleanup();
    bool cleanupModel();
    void sub_71011E1788(bool free_heap);

    // 0x71011e3d6c (804 B): updates the object's entry after its render flag changed.
    void x_2(PlacementMgr* mgr, Object* obj);
    // 0x71011e4090: flushes the UBOs of the draw arrays of every active entry's model unit (`a` is unused).
    // 0x71011e1ffc / 0x71011e264c (CSV unnamed / MassRenderer::setup / MassRenderer::update; declaration
    // only; placeholder names and parameters).
    void sub_71011E4090(PlacementMgr* mgr, bool a);
    // 0x71011e3cd0 (CSV MassRenderer::requestDraw): queues the draw of the mass-rendered models.
    void requestDraw(PlacementMgr* mgr, bool a);
    // 0x71011e41d8 (CSV MassRenderer::x_1): the object's mass-render distance scale, clamped to 1.
    f32 x_1(const Object* obj) const;
    void sub_71011E1FFC(const void* traverse_results, const sead::Vector3f* camera_pos, f32 distance);
    void sub_71011E264C(PlacementMgr* mgr);
    // 0x71011e41f4: whether `p` is one of the three pointers at 0xc8 / 0x138 / 0x1a8 (the draw arrays; the type of `p`
    // is unknown, it is only compared).
    bool sub_71011E41F4(const void* p) const;

    // 0x71011eb32c (PlacementMgr forwards to this inline test): whether bit `idx` of the bit buffer of the active slot
    // is set.
    bool isBitSet(u32 idx) const { return (mSlots[_78].bits[idx >> 5] & (1u << (idx & 0x1f))) != 0; }

    // Three 0x70-byte render slots begin at +0xb8 (constructor 0x71011e151c).
    struct Slot {
        // 0x71011e1b88 allocates 0x10-byte draw bindings and copies their first
        // pointer into the parallel draw-object array.
        struct DrawEntry {
            gsys::ModelDrawObj* object;
            u64 _8;
        };
        struct BoundsEntry {
            u64 _0;
            sead::BoundBox2f bounds;
        };
        sead::Vector3f _0;
        u32 _c;
        gsys::Model* mModel;
        sead::Buffer<DrawEntry> draw_entries;
        sead::Buffer<gsys::ModelDrawObj*> draw_objects;
        sead::Buffer<BoundsEntry> entry_bounds;
        sead::Buffer<u32> bits;
        sead::BoundBox2f bounds;
        u32 _68;
        u32 _6c;
    };
    KSYS_CHECK_SIZE_NX150(Slot, 0x70);

    // Placeholder: an entry of _18 (one per mass-rendered model).
    struct Entry {
        u16 mActorDataIdx;
        u8 _2[4];
        bool _6;
    };

    sead::PtrArray<gsys::ModelUnit> mUnits;
    u8 _10[0x18 - 0x10];
    // Native teardown returns entries to the embedded free list and deletes its work buffer.
    /* 0x18 */ sead::ObjArray<Entry> _18;
    /* 0x38 */ sead::CriticalSection _38;
    /* 0x78 */ s32 _78;
    u8 _7c[0x98 - 0x7c];
    // Initialised to 0.2 by the constructor; the traverse setup reads it.
    f32 _98;
    sead::Heap* mWorkHeap;
    sead::Buffer<gsys::ModelDrawObj> mDrawObjects;
    /* 0xb8 */ Slot mSlots[3];
    /* 0x208 */ s32 mCleanupIndex;
    u32 _20c;
    /* 0x210 */ sead::CriticalSection _210;
    // The constructor clears +0x250; PlacementMgr allocates 0x258 bytes at 0x71011e5944.
    u32 _250 = 0;
};
KSYS_CHECK_SIZE_NX150(MassRenderer, 0x258);

// Placeholder name (callback argument of the ClusteredRenderer query 0x71012497f8): a stack copy of
// the cluster entry.
struct Unk_71012497f8Entry {
    // The query producer copies the model name, translation, XLink and active flag.
    /* 0x00 */ sead::SafeString mName;
    // Identifies the actor (Unk_710251ad68 keeps it in its known-actor lists).
    /* 0x10 */ void* _10;
    u8 _18[0x20 - 0x18];
    /* 0x20 */ sead::Vector3f mPosition;
    u8 _2c[0x78 - 0x2c];
    /* 0x78 */ xlink::XLink* mXLink;
    /* 0x80 */ bool _80;
};
KSYS_CHECK_SIZE_NX150(Unk_71012497f8Entry, 0x88);
static_assert(offsetof(Unk_71012497f8Entry, mName) == 0);
static_assert(offsetof(Unk_71012497f8Entry, mPosition) == 0x20);
static_assert(offsetof(Unk_71012497f8Entry, mXLink) == 0x78);
static_assert(offsetof(Unk_71012497f8Entry, _80) == 0x80);
class Placement18;
class Rail;
class RailConnectablePoint;
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
        // PlacementTree::checkSpawnStuff pushes the traversed Object pointers here.
        sead::PtrArray<Object> _70;
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
    // 0x71011ea08c: requests the actor's bfres model and stores its scale in the actor data.
    void loadModel(ActorData* data);
    // 0x71011e9e04: clamps the camera position, finds the placement tree cell and tells the worker to load the
    // pre-actors around it.
    void loadAllPreactors(const sead::Vector3f& pos, bool a2);
    // 0x71011e57ec (CSV createMapsAndInitAndStartPlacementThread; placeholder parameters): allocates the
    // placement actors / maps and starts the worker thread.
    void createMapsAndInitAndStartPlacementThread(sead::Heap* heap, void* a3, void* a4, void* a5, void* a6,
                                                  void* a7, u32 a8);
    // 0x71011e5944 (CSV initAndStartPlacementThread; declaration only; placeholder parameters).
    void initAndStartPlacementThread(PlacementActors* actors, PlacementMapMgr* map_mgr, Placement18* p18,
                                     sead::Heap* heap, void* a3, void* a4, void* a5, void* a6, void* a7);
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
    bool invoked1(Task* task);
    bool invoked2(void* arg);
    // Whole 11EA4C8 reads ActorData::mActorName at +0x148 and returns true.
    bool invoked2_(ActorData* data);
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
    // 0x71011ea44c / 0x71011ea454 (CSV __auto13 / __auto7; placeholder names, declaration only; lane1 s47): forward
    // to the rail manager at +0x208: the connectable rail point near `pos` (the cell `x` / `z`) / the rail named
    // `name` near `pos`.
    RailConnectablePoint* sub_71011EA44C(const sead::Vector3f* pos, s32 x, s32 z);
    Rail* sub_71011EA454(const sead::SafeString& name, const sead::Vector3f* pos);
    RailConnectablePoint* sub_71011EA45C(const sead::Vector3f* pos,
                                      const sead::SafeString& route_id);
    const RailConnectablePoint* roadStuff(const sead::SafeString& route_ids);
    const RailConnectablePoint* __auto10(const sead::SafeString& point_name);
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
    // Native 0x71011ec098 searches all groups under the placement actor read lock.
    // Event actor producer 0x7100da9d3c supplies its name/subname strings and consumes Object*.
    Object* sub_71011EC098(const sead::SafeString& name, const sead::SafeString& unique_name);
    // 0x71011ec130 searches one group with the same name and unique-name filters.
    Object* sub_71011EC130(s32 group, const sead::SafeString& name,
                          const sead::SafeString& unique_name);

    // Native camera caller924078 passes both names and the origin; the callee returns the nearest Object.
    Object* sub_71011EC398(const sead::SafeString& name, const sead::SafeString& unique_name,
                           const sead::Vector3f& origin);
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
    // 0x71011eb43c (placeholder name): forwards `out` and `pos` to sub_7101249DF4.
    void sub_71011EB43C(sead::Vector2<s32>* out, const sead::Vector3f* pos);
    // 0x71011e6e8c (placeholder name): once the placement thread runs, tells the villager manager (while the scene status is 0
    // and the manager flags `_2000000` (only) are set).
    void sub_71011E6E8C();
    // 0x71011ebfbc (placeholder name; called by evt::ActorBase::m4): registers `obj` (false if it already is).
    bool sub_71011EBFBC(Object* obj);
    // 0x71011ec01c (placeholder name; called by evt::ActorBase::m5): unregisters `obj`.
    void sub_71011EC01C(Object* obj);

    void threadFn(sead::Thread* thread, sead::MessageQueue::Element msg);
    // 0x71011e7200 (CSV threadTraverse; declaration only): the worker's traverse step for result `idx`.
    void threadTraverse(s32 idx);
    // 0x71011e8e84 (CSV threadLoadUnloadCheck; declaration only; `a` picks the pre-actor mode, `b` waits for
    // the dynamic maps): loads / unloads the maps around the camera and the actors of the tree.
    void threadLoadUnloadCheck(s32 a, bool b);
    // 0x71011e70ec: the per-frame worker step that runs the initializer checks and the generation-group
    // spawn pass for traverse result `idx`.
    void threadHandleChecksAndDirectActorGen(s32 idx);
    // 0x71011e6b3c: asks the clustered / mass / forest renderers and the far-actor merge to draw.
    void requestDraw();
    // 0x00000071011eb4dc
    bool auto17(Object* obj);

    enum class MgrFlag {
        _1 = 0x1,
        _2 = 0x2,
        _4 = 0x4,
        _200 = 0x200,
        _400 = 0x400,
        _800 = 0x800,
        _2000 = 0x2000,
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
    // Read by PlacementActors::threadSpawnGenGroupActors (worker pause flags).
    bool isFlagOn(MgrFlag flag) const { return mFlags.isOn(flag); }

    static sead::TypedBitFlag<MgrStaticFlags, u16> sFlags;

    u32 _28;
    u32 _2c = 0;
    u32 _30 = 0;

    u8 TEMP[4];
    // The objects registered by the event system (they get Flag0::_20000: no job push); count at 0x138.
    Object* mEventObjs[32];
    s32 mNumEventObjs;
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
    tera::System* mTeraSystem;
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
    s32 _220;
    f32 _224;
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
    // Bit flags: bit 0 is cleared by requestDraw, bits 2 / 5 / 7 select the renderers it draws;
    // bit 6 is tested by sub_71011E9DB0.
    u32 _690;
    u32 mMessage = 0;
    u32 mJobType = 0;
    TraverseResults mTraverseResults[2];
    PlacementTree* mPlacementTree = nullptr;
    u32 _7a8;
    MassRenderer* mMassRenderer = nullptr;
    act::ClusteredRenderer* mClusteredRenderer = nullptr;
    Unk_7102513630* mPlacementNavi = nullptr;
    u32 mMassRendererReqCount = 0;
    u32 mMassRendererStatus = 0;

    // Passed to BaseProcMgr::removeInitializerTasksIf at 0x71011e70ec.
    sead::Delegate1R<PlacementMgr, Task*, bool> mInvoker;

    s32 _7f0 = -1;

    // LowPrioThreadMgr request delegate in 0x71011ea1fc (void* user data).
    sead::Delegate1R<PlacementMgr, void*, bool> mInvoker2;
};
KSYS_CHECK_SIZE_NX150(PlacementMgr, 0x818);
static_assert(offsetof(PlacementMgr, mThreadStarted) == 0x688);
static_assert(offsetof(PlacementMgr, mPlacementMapMgr) == 0x200);
static_assert(offsetof(PlacementMgr, mVillagerMgr) == 0x218);
static_assert(offsetof(PlacementMgr, mNumStaticObjs) == 0x22c);
static_assert(offsetof(PlacementMgr, mPreActorNumDone) == 0x28c);
static_assert(offsetof(PlacementMgr, mDynamicHeap) == 0x198);

// 0x7101249df4 (declared only): writes the x and z cell indices of `pos` (25 m cells, relative to the origin global
// 0x2580000+0x6d8) to `out`.
void sub_7101249DF4(sead::Vector2<s32>* out, const sead::Vector3f* pos);

}  // namespace ksys::map
