#pragma once

#include <math/seadVector.h>
#include <basis/seadTypes.h>
#include <container/seadPtrArray.h>
#include <container/seadSafeArray.h>
#include <heap/seadDisposer.h>
#include <thread/seadCriticalSection.h>
#include <thread/seadMutex.h>
#include "KingSystem/Physics/physDefines.h"
#include "KingSystem/Utils/Types.h"

class hkpWorld;

namespace sead {
class Thread;
}

namespace ksys::phys {

class CharacterController;
class CollisionInfo;
class ContactLayerCollisionInfo;
class ContactLayerCollisionInfoGroup;
class ContactListener;
class ContactMgr;
class ContactPointInfo;
class GroupFilter;
class HavokMemoryAllocator;
class LayerContactPointInfo;
class MaterialTable;
class RayCastForRequest;
class RayCastRequestMgr;
class RagdollControllerKeyList;
class RagdollInstanceMgr;
class RigidBody;
class RigidBodyRequestMgr;
class StaticCompoundMgr;
class SystemData;
class SystemGroupHandler;
class World;

enum class IsIndoorStage {
    No,
    Yes,
};

enum class LowPriority : bool { Yes = true, No = false };
enum class OnlyLockIfNeeded : bool { Yes = true, No = false };

class System {
    SEAD_SINGLETON_DISPOSER(System)
    System();
    virtual ~System();

public:
    float get64() const { return _64; }
    float get6c() const { return _6c; }
    // lane4 s64: a RigidBody (Constraint's ctor stores it as the fallback body 0; 0x7100f6ac68 compares with it).
    RigidBody* get190() const { return _190; }
    float getTimeFactor() const { return mTimeFactor; }
    ContactMgr* getContactMgr() const { return mContactMgr; }
    StaticCompoundMgr* getStaticCompoundMgr() const { return mStaticCompoundMgr; }
    RigidBodyRequestMgr* getRigidBodyRequestMgr() const { return mRigidBodyRequestMgr; }
    RagdollInstanceMgr* getRagdollInstanceMgr() const { return mRagdollInstanceMgr; }
    SystemData* getSystemData() const { return mSystemData; }
    MaterialTable* getMaterialTable() const { return mMaterialTable; }
    const sead::Vector3f& getField48() const { return _48; }

    bool isPaused() const;
    // lane4 s30 (CSV PhysicsMemSys::setPauseState / initBeforeStageGen / waitForResourceCreation /
    // setRigidBodyDividedMeshShapeMgr):
    // 0x710121677c
    void setPauseState(bool paused);
    // 0x7101214aac: ContactMgr::initContactPointPool(heap, indoor stage flag at +0x268).
    void initBeforeStageGen(sead::Heap* heap);
    // 0x71012157b4 (CSV PhysicsMemSys::__auto0; declaration only; placeholder name): called by the placement managers
    // after they asked their worker thread to quit.
    void sub_71012157B4(sead::Thread* thread, bool a);
    // 0x7101215358 / 0x71012153b4 (lane4 s64; placeholder names): under `_270`, add the controller to `_2b0` (if
    // there is room) / remove it.
    void sub_7101215358(CharacterController* controller);
    void sub_71012153B4(CharacterController* controller);
    // 0x7101214b04: StaticCompoundMgr::resetExtraTransformsAndApply() if there is one.
    void waitForResourceCreation();
    // 0x7101216c58
    void setRigidBodyDividedMeshShapeMgr(void* mgr);

    void initSystemData(sead::Heap* heap);

    ContactPointInfo* allocContactPointInfo(sead::Heap* heap, int num, const sead::SafeString& name,
                                            int a, int b, int c) const;
    void freeContactPointInfo(ContactPointInfo* info) const;

    LayerContactPointInfo* allocLayerContactPointInfo(sead::Heap* heap, int num, int num2,
                                                      const sead::SafeString& name, int a, int b,
                                                      int c) const;
    void freeLayerContactPointInfo(LayerContactPointInfo* info) const;

    void registerContactPointInfo(ContactPointInfo* info) const;
    // 0x000000710121696c
    void registerCollisionInfo(CollisionInfo* info) const;
    // 0x0000007101216974
    void registerContactPointLayerPair(LayerContactPointInfo* info, ContactLayer layer1,
                                       ContactLayer layer2, bool enabled);

    // 0x00000071012169a4
    CollisionInfo* allocCollisionInfo(sead::Heap* heap, const sead::SafeString& name) const;
    // 0x00000071012169ac
    void freeCollisionInfo(CollisionInfo* info) const;

    // 0x00000071012169b4
    ContactLayerCollisionInfoGroup*
    makeContactLayerCollisionInfoGroup(sead::Heap* heap, ContactLayer layer, int capacity,
                                       const sead::SafeString& name);
    // 0x00000071012169c0
    void freeContactLayerCollisionInfoGroup(ContactLayerCollisionInfoGroup* group);
    // 0x00000071012169c8
    ContactLayerCollisionInfo* trackLayerPair(ContactLayer layer_a, ContactLayer layer_b);

    // 0x0000007101216a20
    void removeRigidBodyFromContactSystem(RigidBody* body);

    // 0x000000710121686c
    SystemGroupHandler* addSystemGroupHandler(ContactLayerType layer_type, int free_list_idx = 0);
    // 0x7101216894: returns an existing system group handler by layer and index.
    SystemGroupHandler* sub_7101216894(ContactLayerType layer_type, int index);
    // 0x71012168c8: returns one of the existing system group handlers.
    SystemGroupHandler* sub_71012168C8(ContactLayerType layer_type, int free_list_idx);
    // 0x0000007101215b68
    void removeSystemGroupHandler(SystemGroupHandler* handler);

    hkpWorld* getHavokWorld(ContactLayerType type) const;

    // 0x0000007101215754
    void lockWorld(ContactLayerType type, const char* description = nullptr, int b = 0,
                   OnlyLockIfNeeded only_lock_if_needed = OnlyLockIfNeeded::No);
    // 0x0000007101215784
    void unlockWorld(ContactLayerType type, const char* description = nullptr, int b = 0,
                     OnlyLockIfNeeded only_lock_if_needed = OnlyLockIfNeeded::No);

    // 0x0000007101216ac8
    GroupFilter* getGroupFilter(ContactLayerType type) const;

    // 0x0000007101216ae8
    RayCastForRequest* allocRayCastRequest(SystemGroupHandler* group_handler = nullptr,
                                           GroundHit ground_hit = GroundHit::HitAll);

    RagdollControllerKeyList* getRagdollCtrlKeyList() const;

    // TODO: rename
    // 0x0000007101216c60
    void setEntityContactListenerField90(bool value);
    // 0x0000007101216c74
    bool getEntityContactListenerField90() const;

    // 0x0000007101216ca4
    bool isActorSystemIdle() const;

    // 0x0000007101216800
    void setEntityContactListenerField91(bool value);
    // 0x71012167ec: disables notifications of the sensor contact listener.
    void sub_71012167EC(bool value);
    // 0x0000007101216814
    bool getEntityContactListenerField91() const;

    // 0x000000710121682c
    void incrementWorldUnkCounter(ContactLayerType layer_type);
    // 0x000000710121684c
    void decrementWorldUnkCounter(ContactLayerType layer_type);

    bool isHavokMainHeapOom() const;

    sead::Heap* getPhysicsTempHeap(LowPriority low_priority) const;

private:
    sead::PtrArray<World> mWorlds;
    u8 _38[0x48 - 0x38];
    sead::Vector3f _48;  // gravity?
    u8 _54[0x60 - 0x54];
    bool mPaused;
    bool _61;
    bool _62;
    u8 _63;
    float _64 = 1.0 / 30.0;
    float _68 = 1.0 / 30.0;
    float _6c = 1.0;
    float _70 = 1.0 / 30.0;
    float mTimeFactor{};
    HavokMemoryAllocator* mHavokAllocator{};
    u8 _80[0xa8 - 0x80];
    sead::CriticalSection mCS;
    void* _e8{};
    void* _f0{};
    GroupFilter* mEntityGroupFilter{};
    GroupFilter* mSensorGroupFilter{};
    sead::FixedPtrArray<GroupFilter, 2> mGroupFilters;
    sead::FixedPtrArray<ContactListener, 2> mContactListeners;
    ContactMgr* mContactMgr;
    void* _150;
    StaticCompoundMgr* mStaticCompoundMgr;
    RigidBodyRequestMgr* mRigidBodyRequestMgr;
    RagdollInstanceMgr* mRagdollInstanceMgr;
    void* mRigidBodyDividedMeshShapeMgr;
    SystemData* mSystemData;
    MaterialTable* mMaterialTable;
    RayCastRequestMgr* mRayCastRequestMgr{};
    RigidBody* _190{};
    void* _198{};
    void* _1a0{};
    sead::Heap* mPhysicsSystemHeap{};
    sead::Heap* mDebugHeap{};
    sead::Heap* mPhysicsTempDefaultHeap{};
    sead::Heap* mPhysicsTempLowHeap{};
    u8 _1c8[0x268 - 0x1c8];
    IsIndoorStage mIsIndoorStage;
    u8 _26c[0x270 - 0x26c];
    // lane4 s64: the character controllers whose mFlags bit 12 is set (0x7101215358 adds, 0x71012153b4 removes).
    sead::Mutex _270;
    sead::PtrArray<CharacterController> _2b0;
    // lane4 s46: system group handlers (sub_7101216894 / sub_71012168C8).
    sead::SafeArray<sead::SafeArray<SystemGroupHandler*, 4>, 2> _2c0;
    sead::SafeArray<sead::SafeArray<SystemGroupHandler*, 2>, 2> _300;
    u8 _320[0x480 - 0x320];
};
KSYS_CHECK_SIZE_NX150(System, 0x480);

class ScopedWorldLock {
public:
    explicit ScopedWorldLock(ContactLayerType type, const char* description = nullptr, int unk = 0,
                             OnlyLockIfNeeded only_lock_if_needed = OnlyLockIfNeeded::No)
        : ScopedWorldLock(true, type, description, unk, only_lock_if_needed) {}

    ScopedWorldLock(bool condition, ContactLayerType type, const char* description = nullptr,
                    int unk = 0, OnlyLockIfNeeded only_lock_if_needed = OnlyLockIfNeeded::No)
        : mCondition(condition), mType(type), mDescription(description), mUnk(unk),
          mOnlyLockIfNeeded(only_lock_if_needed) {
        if (mCondition)
            System::instance()->lockWorld(mType, mDescription, mUnk, mOnlyLockIfNeeded);
    }

    ~ScopedWorldLock() {
        if (mCondition)
            System::instance()->unlockWorld(mType, mDescription, mUnk, mOnlyLockIfNeeded);
    }

    ScopedWorldLock(const ScopedWorldLock&) = delete;
    auto operator=(const ScopedWorldLock&) = delete;

private:
    bool mCondition;
    ContactLayerType mType;
    const char* mDescription;
    int mUnk;
    OnlyLockIfNeeded mOnlyLockIfNeeded;
};

}  // namespace ksys::phys
