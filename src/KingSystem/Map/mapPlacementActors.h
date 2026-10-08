#pragma once

#include <container/seadBuffer.h>
#include <container/seadOffsetList.h>
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

namespace ksys::map {

class Object;
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

    sead::TypedLongBitFlag<64, Flag, sead::Atomic<u32>> mFlags;
    sead::TypedBitFlag<ActorFlag8, u8> mActorFlags8;
    u8 _9 = 0;
    u8 _a = 0xff;
    u8 _b = 0;
    u8 _c[0x20 - 0xc];
    res::Unk_71024f9958 _20;
    res::Unk_71024f9938 _58;
    res::ResDerived mRes;
    u8 _d8[0x148 - 0xd8];
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

    // 0x0000007101256be8 (CSV PlacementObjs::dtor): frees every group's object buffer.
    ~PlacementObjs();

    void* _0;
    sead::SafeArray<Group, 10> mGroups;
};

class PlacementActors {
public:
    virtual ~PlacementActors();

    u32 getNumStaticObjs() const;
    Object* getStaticObj_2(s32 idx) const;
    bool sub_7100D524B4() const;
    void x_9();
    // 0x7100d52c0c (an empty function in the original: CSV nullsub_3773)
    void sub_7100D52C0C();
    // 0x7100d53558 (CSV placeObject; declaration only)
    void placeObject(Object* obj);
    // 0x7100d580dc (CSV x_7): calls Object::sub_7100D4DB08 on each object of `_2a8060`, under the mutex `_2a8078`.
    void x_7();
    // 0x7100d52ca4 (declared; unnamed in the CSV): adds `obj` to the first free slot of `_f8` (the list x_9 handles).
    void sub_7100D52CA4(Object* obj);
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
    // 0x0000007100d53d18
    void initActorDataEntry(ActorData* data, const char* name);

    u8 _8[0x28 - 0x8];
    sead::ReadWriteLock mLock;
    PlacementAreaMgr* mStruct1;
    u32 _e8;
    PlacementObjs* mObjs;
    // Objects whose actors are to be (re)enabled (cleared by x_9), guarded by mMutex.
    Object* _f8[128];
    sead::Mutex mMutex;
    sead::SafeArray<ActorData, 6000> mActorData;
    u8 _261b38[0x2a8058 - 0x261b38];
    u32 mActorDataMapSize;
    u8 _2a805c[0x2a8060 - 0x2a805c];
    // The object list walked by x_7 (its link offset is the list's own mOffset).
    sead::OffsetList<Object> _2a8060;
    // The mutex guarding `_2a8060` (used by x_7 only).
    sead::Mutex _2a8078;
    u8 _2a80a0[0x2a80d0 - 0x2a8078 - sizeof(sead::Mutex)];
};
KSYS_CHECK_SIZE_NX150(PlacementActors, 0x2A80D0);

// 0x7100d57658 (CSV name): traverse distance of actor `name`: InfoData::getTraverseDist (x 0.7 for
// "Enemy" / "NPC" profiles), or else derived from InfoData::getBoundingForTraverse (`a2` if that is not
// positive) through two lookup tables (0x7101ec0b8c / 0x7101ec0c04). Not decompiled yet.
f32 getActorTraverseDist(const sead::SafeString& name, f32 a2);
// 0x7100d5787c (CSV name): getActorTraverseDist(name, a2) + 100.
f32 getActorTraverseDistPlus100(const sead::SafeString& name, f32 a2);

}  // namespace ksys::map
