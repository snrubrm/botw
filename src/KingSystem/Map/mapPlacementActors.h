#pragma once

#include <container/seadBuffer.h>
#include <container/seadOffsetList.h>
#include <container/seadPtrArray.h>
#include <container/seadTreeMap.h>
#include <container/seadSafeArray.h>
#include <prim/seadSafeString.h>
#include <prim/seadTypedBitFlag.h>
#include <prim/seadTypedLongBitFlag.h>
#include <thread/seadAtomic.h>
#include <thread/seadMutex.h>
#include <thread/seadReadWriteLock.h>
#include "KingSystem/Map/mapPlacementMap.h"
#include "KingSystem/Resource/resResDerived.h"
#include "KingSystem/Resource/resUnk_71024F9938.h"
#include "KingSystem/Utils/Types.h"

namespace gsys {
class ModelUnit;
}

namespace ksys::eft {
class EffectModelData;
}

namespace ksys::map {

class Object;
class Placement18;
class Unk_7100D4D998;
class PlacementMap;
class PlacementAreaMgr;
class PlacementTree;

// TODO: rename
enum class ActorFlag8 {
    MapPassive = 0x1,
    EnemyOrNpcOrActiveOrAreaOrAirWall = 0x2,
    UndispCutOrPreActorXLinkOrChemical = 0x4,
    _8 = 0x8,
    CanGetPouch = 0x10,
    HasCreateOrDeleteLink = 0x20,
    DragonDropItemTarget = 0x40,
    TreeOrBush = 0x80,
};

class ActorData {
public:
    enum class Flag {
        MapPassive = 0,
        _1 = 1,
        _2 = 2,
        _3 = 3,
        _4 = 4,
        _5 = 5,
        _6 = 6,
        _7 = 7,
        MapConstActive = 8,
        TraverseDist200 = 9,
        TraverseDist400 = 10,
        TraverseDist800 = 11,
        TraverseDistReset = 12,
        TraverseDist2000 = 13,
        TraverseDist4000 = 14,
        _15 = 15,
        _16 = 16,
        RevivalEnable = 17,
        RevivalForUsed = 18,
        RevivalForDrop = 19,
        RevivalRandom = 20,
        RevivalBloodyMoon = 21,
        RevivalUnderGodTimeOrNoneForUsed = 22,
        EnableRemainsScene = 23,
        _24 = 24,
        EnemyOrNpc_DisableFlashback = 25,
        _26 = 26,
        LimitYDiff = 27,
        IsGrassCut = 28,
        HasFar = 29,
        Fairy = 30,
        UnderGodForest = 31,

        EnemyOrNpc = 32,
        MapConstPassive = 33,
        RandomCreateNotRain = 34,
        _35 = 35,
        MessageDialogViewBoard = 36,
        _37 = 37,
        NpcOrNonGanonAndNonGuardianEnemy = 38,
        IgnoreBoundingAtAreaCulling = 39,
        _40 = 40,
        EnemyHuge = 41,
        Enemy = 42,
        _43 = 43,
        EnemyLookOrGrassCutTagOrFirePillarOrDgnWater = 44,
        _45 = 45,
        MapPassiveOrFlag1 = 46,
        _47 = 47,
        _48 = 48,
        SheikSensorTargetDeadOrAlive = 49,
        Dragon = 50,
        TreeOrBush = 51,
        GuardianC = 52,
        _53 = 53,
        HasStopTimerFlag = 54,
        AllRadarOrZukanActor = 55,
        NoCreateForStackLink = 56,
        OnLowTree = 57,
        _58 = 58,
        _59 = 59,
        _60 = 60,
        _61 = 61,
        _62 = 62,
        _63 = 63,
    };

    // D4DF48; the load/unload worker passes this record at PlacementActors + 538 + index * 1A0.
    s32 sub_7100D4DF48() const;

    sead::TypedLongBitFlag<64, Flag, sead::Atomic<u32>> mFlags;
    sead::TypedBitFlag<ActorFlag8, u8> mActorFlags8;
    u8 _9 = 0;
    u8 _a = 0xff;
    u8 _b = 0;
    u8 _c[0x10 - 0xc];
    // The mass-rendered model (MassRenderer 0x71011e4090 flushes its draw array).
    gsys::ModelUnit* _10;
    u8 _18[0x20 - 0x18];
    res::Unk_71024f9958 _20;
    res::Unk_71024f9938 _58;
    res::ResDerived mRes;
    u8 _d8[0xdc - 0xd8];
    f32 _dc;
    f32 _e0;
    f32 _e4;
    u8 _e8[0xf0 - 0xe8];
    Unk_7100D4D998* mEffectEntry;
    /* 0xf8 */ eft::EffectModelData* mEffectModelData;
    u8 _100[0x148 - 0x100];
    sead::FixedSafeString<64> mActorName;
};
KSYS_CHECK_SIZE_NX150(ActorData, 0x1A0);

// TODO: incomplete
class PlacementObjs {
public:
    struct Group {
        sead::Buffer<Object> objects;
        s32 num_objs;
        PlacementMap* map;
    };
    KSYS_CHECK_SIZE_NX150(Group, 0x20);

    // 0x0000007101256eac
    int allocGroupForDynamicMap(PlacementMap* pmap);
    // 0x0000007101256ee8
    void resetGroup(int group_idx);
    // 0x0000007101256cc4
    void freeObjects();
    // 0x0000007101256f04
    void x_0(PlacementTree* tree);
    // 0x0000007101256c78 (CSV allocObj; lane4 s45): the next unused object of the group, or null if it is full.
    Object* allocObj(int group_idx);
    // 0x0000007101256e14 (CSV findObjByHash; lane4 s45): binary search by hash id. Group 0 (the static objects) is
    // searched in the index range [start, end], the other groups over all their objects.
    Object* findObjByHash(const u32& hash, int group_idx, int start, int end);
    // 0x0000007101256d58 (CSV findObjByHashInAllGroups): the same over the groups 0-9; writes the group of the result.
    Object* findObjByHashInAllGroups(const u32& hash, int start, int end, int* out_group);

    // 0x00000071012567f8 (CSV PlacementObjs::ctor): allocates the object buffers of the groups (80600 objects for
    // group 0 and 4100 for each other group if `num_objs` > 10000; otherwise `num_objs` for groups 0 and 1 and
    // one object for each other group).
    PlacementObjs(sead::Heap* heap, s32 num_objs);
    // 0x0000007101256be8 (CSV PlacementObjs::dtor): frees every group's object buffer.
    ~PlacementObjs();

    void* _0;
    sead::SafeArray<Group, 10> mGroups;
    sead::Heap* mHeap;
};

class PlacementActors {
public:
    // 0x7100d51f04 (CSV PlacementActors::ctor; placeholder parameter names): heap, effect heap, actor data
    // capacity and an init argument.
    PlacementActors(sead::Heap* heap, void* a, u32 b, void* c);
    virtual ~PlacementActors();

    u32 getNumStaticObjs() const;
    Object* getStaticObj_2(s32 idx) const;
    bool sub_7100D524B4() const;
    void x_9();
    // 0x7100d52c0c (an empty function in the original: CSV nullsub_3773)
    void sub_7100D52C0C();
    // 0x7100d53558 (CSV placeObject; declaration only)
    void placeObject(Object* obj);
    // 0x7100d580dc (CSV x_7): calls Unk_7100D4D998::sub_7100D4DB08 on each object of `_2a8060`, under the mutex `_2a8078`.
    void x_7();
    void sub_7100D58028(ActorData* data);
    // 0x7100d52ca4 (declared; unnamed in the CSV): adds `obj` to the first free slot of `_f8` (the list x_9 handles).
    void sub_7100D52CA4(Object* obj);
    // 0x7100d52910 (CSV spawnActor; placeholder parameter names): creates the actor of `obj` and registers
    // its base proc; returns whether it was created.
    bool spawnActor(Object* obj);
    // 0x7100d538b8: spawns the actors of the traverse results whose generation group needs them.
    void threadSpawnGenGroupActors(const sead::Vector3f& pos, void* traverse_results);
    // 0x7100d539e4 (declared only; CSV threadFn_x2_a): the per-frame traverse step the placement manager runs
    // on one traverse result set. `results` is PlacementMgr::TraverseResults* (nested private, not modelable
    // from this header), so it is passed as void*.
    void threadFn_x2_a(const sead::Vector3f& pos, void* results);
    // 0x7100d527d8 (CSV PlacementMgrInvoked3_doSpawn): the placement manager's spawn delegate. Clears or sets
    // the object's spawn flag, then spawns the actor (or its generation group when asked).
    bool doSpawn(Object* obj, bool set_flag, bool use_gen_group);
    // 0x0000007100d53788 (CSV name; declared only): spawns the actor of `obj` for the generation group `other`
    // belongs to (parameter names are guesses).
    bool spawnGenGroupActor(Object* obj, Object* other);
    void resetGroup(int group_idx);
    int getNumObjs(int group_idx) const;
    Object* getObj(int group_idx, int object_idx);
    Object* getStaticObj_0(int object_idx);
    // 0x0000007100d581b4
    Object* getStaticObj(int object_idx);
    // 0x0000007100d58230
    Object* getStaticObj_1(int object_idx);
    // 0x0000007100d581f0
    PlacementMap* getMapNextGroup(int group_idx) const;
    // 0x0000007100d58218
    void setNumInUseForStaticGroup(int num);
    u32 allocGroupForDynamicMap(PlacementMap* pmap);
    void removeInnerData1();
    void clearActorDataAndObjects();
    bool checkResLoadStartedAndFailed();
    void freeObjects();
    void reinitActorDataEntryForTreeBuild();
    u32 getStaticNumInUse() const;
    void rebuildTree(PlacementTree* tree);
    int getNumGroups() const;
    // 0x0000007100d522bc
    void deleteActorData(ActorData* data);
    // 0x7100d52708 (placeholder name): releases the effect model data and the effect entry of `data`.
    void releaseEffectModel(ActorData* data);
    // 0x7100d52500: deletes the actor data entries in order for at most 10 ms per call.
    bool removeInnerData2();
    // 0x7100d4fdb0: creates the generation group of `obj` and its linked objects; true when it built one or
    // the object needs none.
    bool buildGenGroup(Object* obj, sead::Heap* heap);
    // 0x7100d574b4: the actor data index of `name`, creating the actor data entry when the name is new.
    s32 findOrInsertActorData(const char* name);
    // 0x0000007100d50210: the largest display distance of `obj` and the objects reachable from its
    // links, skipping objects already in `visited` and the placement LOD / for-sale links.
    f32 getMaxTraverseDistForGenGroupRecursively(Object* obj, sead::PtrArray<Object>* visited);
    // 0x7100d503dc: collects the objects reachable from `obj` into `group_objs` (or into `link_tags`
    // for LinkTagNone objects), and sets the traverse distance of passive objects to `max_dist`.
    void addAllLinkedActorsToGenGroupRecursively(f32 max_dist, Object* obj,
                                                 sead::PtrArray<Object>* group_objs,
                                                 sead::PtrArray<Object>* link_tags);
    // 0x0000007100d53d18
    void initActorDataEntry(ActorData* data, const char* name);

    u8 _8[8];
    sead::Heap* mEffectHeap;
    u8 _18[8];
    // Set by PlacementMgr::createMapsAndInitAndStartPlacementThread.
    Placement18* mPlacement18;
    sead::ReadWriteLock mLock;
    PlacementAreaMgr* mStruct1;
    u32 _e8;
    PlacementObjs* mObjs;
    // Objects whose actors are to be (re)enabled (cleared by x_9), guarded by mMutex.
    Object* _f8[128];
    sead::Mutex mMutex;
    sead::SafeArray<ActorData, 6000> mActorData;
    // Actor name hash -> actor data index.
    sead::TreeMap<u32, s16> mActorDataMap;
    u8 _261b58[0x2a8058 - 0x261b58];
    u32 mActorDataMapSize;
    u8 _2a805c[0x2a8060 - 0x2a805c];
    // The object list walked by x_7 (its link offset is the list's own mOffset).
    sead::OffsetList<Unk_7100D4D998> _2a8060;
    // The mutex guarding `_2a8060`.
    sead::Mutex _2a8078;
    u8 _2a80a0[0x2a80b8 - 0x2a8078 - sizeof(sead::Mutex)];
    // The map objects of the three roaming dragons (Dragon::sub_710000C440, by dragon kind 0 - 2).
    /* 0x2a80b8 */ Object* mDragonObjects[3];
};
KSYS_CHECK_SIZE_NX150(PlacementActors, 0x2A80D0);

// 0x7100d53660 (CSV PlacementObj::shouldSpawn; placeholder owner): whether the actor of `obj` may be
// spawned by the placement thread.
bool shouldSpawn(Object* obj);
// 0x7100d4b1a8 (CSV PlacementObj::x_13; 4248 bytes, placeholder parameters): the spawn point of `obj`
// for `pos`; the implementation is not decompiled yet.
bool x_13(Object* obj, const sead::Vector3f& pos, void* a3, const void* a4);
// 0x7100d57658 (CSV name): traverse distance of actor `name`: InfoData::getTraverseDist (x 0.7 for
// "Enemy" / "NPC" profiles), or else derived from InfoData::getBoundingForTraverse (`a2` if that is not
// positive) through two lookup tables (0x7101ec0b8c / 0x7101ec0c04). Not decompiled yet.
f32 getActorTraverseDist(const sead::SafeString& name, f32 a2);
// 0x7100d5787c (CSV name): getActorTraverseDist(name, a2) + 100.
f32 getActorTraverseDistPlus100(const sead::SafeString& name, f32 a2);

}  // namespace ksys::map
