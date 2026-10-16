#include "KingSystem/Physics/System/physSystem.h"
#include <math/seadMathCalcCommon.h>
#include "KingSystem/Physics/Ragdoll/physRagdollInstanceMgr.h"
#include "KingSystem/Physics/System/physStaticCompoundMgr.h"
#include "KingSystem/Physics/System/physContactMgr.h"
#include "KingSystem/Physics/System/physWorld.h"
#include <heap/seadHeap.h>
#include <prim/seadScopedLock.h>
#include <thread/seadThread.h>
#include "KingSystem/ActorSystem/actBaseProcMgr.h"
#include "KingSystem/Physics/Cloth/physClothResource.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Physics/RigidBody/physRigidBodyRequestMgr.h"
#include "KingSystem/Physics/Ragdoll/physRagdollControllerKeyList.h"
#include "KingSystem/Physics/Ragdoll/physRagdollResource.h"
#include "KingSystem/Physics/RigidBody/TeraMesh/physTeraMeshRigidBodyResource.h"
#include "KingSystem/Physics/RigidBody/physRigidBodyResource.h"
#include "KingSystem/Physics/System/physStaticCompound.h"
#include "KingSystem/Physics/SupportBone/physSupportBoneResource.h"
#include "KingSystem/Physics/System/physContactListener.h"
#include "KingSystem/Physics/System/physContactMgr.h"
#include "KingSystem/Physics/System/physContactPointInfo.h"
#include "KingSystem/Physics/System/physEntityGroupFilter.h"
#include "KingSystem/Physics/System/physGroupFilter.h"
#include "KingSystem/Physics/System/physLayerContactPointInfo.h"
#include "KingSystem/Physics/System/physMaterialTable.h"
#include "KingSystem/Physics/System/physRayCastRequestMgr.h"
#include "KingSystem/Physics/System/physSensorGroupFilter.h"
#include "KingSystem/Physics/System/physSystemData.h"
#include "KingSystem/Physics/System/physHavokMemoryAllocator.h"
#include "KingSystem/Resource/resEntryFactory.h"
#include "KingSystem/Resource/resSystem.h"

namespace ksys::phys {

SEAD_SINGLETON_DISPOSER_IMPL(System)

bool System::isPaused() const {
    return mPaused;
}

void System::setPauseState(bool paused) {
    mPaused = paused;
}

void System::initBeforeStageGen(sead::Heap* heap) {
    mContactMgr->initContactPointPool(heap, mIsIndoorStage);
}

void System::waitForResourceCreation() {
    if (mStaticCompoundMgr)
        mStaticCompoundMgr->resetExtraTransformsAndApply();
}

void System::setRigidBodyDividedMeshShapeMgr(void* mgr) {
    mRigidBodyDividedMeshShapeMgr = mgr;
}

void System::sub_7101216AA8(Unk_71012a6844::ItemA* item) {
    _150->sub_71012A69E0(item);
}

void System::sub_7101216AB0(Unk_71012a6844::ItemA* item) {
    _150->sub_71012A6A44(item);
}

void System::sub_7101216AB8(Unk_71012a6844::ItemB* item) {
    _150->sub_71012A6AA4(item);
}

void System::sub_7101216AC0(Unk_71012a6844::ItemB* item) {
    _150->sub_71012A6AF8(item);
}

void System::registerCollisionInfo(CollisionInfo* info) const {
    mContactMgr->registerCollisionInfo(info);
}

void System::initSystemData(sead::Heap* heap) {
    res::registerEntryFactory(new (heap) res::EntryFactory<RigidBodyResource>(1.0, 0x400), "hkrb");
    res::registerEntryFactory(new (heap) res::EntryFactory<RagdollResource>(1.0, 0x400), "hkrg");
    res::registerEntryFactory(new (heap) res::EntryFactory<SupportBoneResource>(1.0, 0x100000),
                              "bphyssb");
    res::registerEntryFactory(new (heap) res::EntryFactory<ClothResource>(2.0, 0x2800), "hkcl");
    res::registerEntryFactory(new (heap) res::EntryFactory<StaticCompound>(1.3, 0x40000), "hksc");
    res::registerEntryFactory(new (heap) res::EntryFactory<TeraMeshRigidBodyResource>(1.0, 0x800),
                              "hktmrb");
    res::registerEntryFactory(new (heap) res::EntryFactory<RagdollControllerKeyList>(1.0, 0x4000),
                              "brgcon");

    mEntityGroupFilter = EntityGroupFilter::make(FirstEntity, LastEntity, heap);
    mSensorGroupFilter = SensorGroupFilter::make(LastSensor, heap);
    mGroupFilters.pushBack(mEntityGroupFilter);
    mGroupFilters.pushBack(mSensorGroupFilter);

    mContactMgr = new (heap) ContactMgr;
    if (mContactMgr)
        mContactMgr->init(heap);

    mMaterialTable = new (heap) MaterialTable;

    mSystemData = new (heap) SystemData;
    mSystemData->load(mPhysicsSystemHeap, mEntityGroupFilter, mSensorGroupFilter, mMaterialTable,
                      mContactMgr);
}

void System::removeSystemGroupHandler(SystemGroupHandler* handler) {
    mGroupFilters[static_cast<s32>(handler->getLayerType())]->removeSystemGroupHandler(handler);
}

ContactPointInfo* System::allocContactPointInfo(sead::Heap* heap, int num,
                                                const sead::SafeString& name, int a, int b,
                                                int c) const {
    return mContactMgr->makeContactPointInfo(heap, num, name, a, b, c);
}

void System::freeContactPointInfo(ContactPointInfo* info) const {
    mContactMgr->freeContactPointInfo(info);
}

CollisionInfo* System::allocCollisionInfo(sead::Heap* heap, const sead::SafeString& name) const {
    return mContactMgr->makeCollisionInfo(heap, name);
}

void System::freeCollisionInfo(CollisionInfo* info) const {
    mContactMgr->freeCollisionInfo(info);
}

ContactLayerCollisionInfoGroup*
System::makeContactLayerCollisionInfoGroup(sead::Heap* heap, ContactLayer layer, int capacity,
                                           const sead::SafeString& name) {
    return mContactMgr->makeContactLayerCollisionInfoGroup(heap, layer, capacity, name);
}

void System::freeContactLayerCollisionInfoGroup(ContactLayerCollisionInfoGroup* group) {
    mContactMgr->freeContactLayerCollisionInfoGroup(group);
}

GroupFilter* System::getGroupFilter(ContactLayerType type) const {
    return mGroupFilters[static_cast<s32>(type)];
}

RayCastForRequest* System::allocRayCastRequest(SystemGroupHandler* group_handler,
                                               GroundHit ground_hit) {
    return mRayCastRequestMgr->allocRequest(group_handler, ground_hit);
}

void System::initSystemGroupHandlers() {
    for (int type = 0; type < NumContactLayerTypes; ++type) {
        for (int i = 0; i < 4; ++i)
            _2c0[type][i] = mGroupFilters[type]->addSystemGroupHandler(0);
        for (int i = 0; i < 2; ++i)
            _300[type][i] = mGroupFilters[type]->addSystemGroupHandler(1);
    }
}

SystemGroupHandler* System::addSystemGroupHandler(ContactLayerType layer_type, int free_list_idx) {
    return getGroupFilter(layer_type)->addSystemGroupHandler(free_list_idx);
}

// NON_MATCHING: the original round-trips the index through the stack (`str w2, [sp, #0xc]; ldrsw x9, [sp, #0xc]`).
SystemGroupHandler* System::sub_7101216894(ContactLayerType layer_type, int index) {
    return _2c0[static_cast<s32>(layer_type)][index];
}

// NON_MATCHING: as sub_7101216894 (the index round trip through the stack).
SystemGroupHandler* System::sub_71012168C8(ContactLayerType layer_type, int free_list_idx) {
    return _300[static_cast<s32>(layer_type)][free_list_idx];
}

LayerContactPointInfo* System::allocLayerContactPointInfo(sead::Heap* heap, int num, int num2,
                                                          const sead::SafeString& name, int a,
                                                          int b, int c) const {
    return mContactMgr->makeLayerContactPointInfo(heap, num, num2, name, a, b, c);
}

void System::freeLayerContactPointInfo(LayerContactPointInfo* info) const {
    mContactListeners[static_cast<s32>(info->getLayerType())]->removeLayerPairsForContactPointInfo(
        info);
    mContactMgr->freeContactPointInfo(info);
}

// NON_MATCHING: regalloc (x8/w9 swapped)
void System::setEntityContactListenerField90(bool value) {
    mContactListeners(int(ContactLayerType::Entity))->_90 = value;
}

bool System::getEntityContactListenerField90() const {
    return mContactListeners(int(ContactLayerType::Entity))->_90;
}

// NON_MATCHING: regalloc (x8/w9 swapped)
void System::setEntityContactListenerField91(bool value) {
    mContactListeners(int(ContactLayerType::Entity))->_91 = value;
}

// NON_MATCHING: pointer and value registers differ from the original store.
void System::sub_71012167EC(bool value) {
    mContactListeners(int(ContactLayerType::Sensor))->mDisableContactPointInfoNotifications = value;
}

bool System::getEntityContactListenerField91() const {
    return mContactListeners(int(ContactLayerType::Entity))->_91;
}

void System::removeRigidBodyFromContactSystem(RigidBody* body) {
    const auto layer_type = getContactLayerType(body->getContactLayer());
    if (mPaused)
        mContactMgr->removeContactPointsWithBody(body);
    mContactListeners[int(layer_type)]->unregisterCollisionWithBody(body);
    mContactMgr->removeCollisionEntriesWithBody(body);
    mContactMgr->removeImpulseEntriesWithBody(body);
}

bool System::isActorSystemIdle() const {
    const bool busy = _62 || _61;
    if (!act::BaseProcMgr::instance())
        return true;
    return busy |
           (act::BaseProcMgr::instance()->getStatus() != act::BaseProcMgr::Status::ProcessingActorJobs);
}

void System::registerContactPointInfo(ContactPointInfo* info) const {
    mContactMgr->registerContactPointInfo(info);
}

void System::registerContactPointLayerPair(LayerContactPointInfo* info, ContactLayer layer1,
                                           ContactLayer layer2, bool enabled) {
    mContactListeners[static_cast<s32>(info->getLayerType())]->addLayerPairForContactPointInfo(
        info, layer1, layer2, enabled);
}

ContactLayerCollisionInfo* System::trackLayerPair(ContactLayer layer_a, ContactLayer layer_b) {
    return mContactListeners[static_cast<s32>(getContactLayerType(layer_a))]->trackLayerPair(
        layer_a, layer_b);
}

RagdollControllerKeyList* System::getRagdollCtrlKeyList() const {
    if (!mSystemData)
        return nullptr;
    return mSystemData->getRagdollCtrlKeyList();
}

bool System::isHavokMainHeapOom() const {
    return static_cast<f32>(mHavokAllocator->getHeapFreeSize()) /
               static_cast<f32>(mHavokAllocator->getHeapSize()) <
           0.05f;
}

hkpWorld* System::getHavokWorld(ContactLayerType type) const {
    return mWorlds(int(type))->getHavokWorld();
}

void System::sub_710121624C() {
    if (_61)
        return;

    if (_70 < _64) {
        _70 += _70 * 0.1f;
        _70 = sead::Mathf::clampMax(_70, _64);
    } else if (_70 > _64) {
        _70 += _70 * -0.1f;
        _70 = sead::Mathf::clampMin(_70, _64);
    }

    if (!mPaused) {
        if (mStaticCompoundMgr)
            mStaticCompoundMgr->processUpdates();
        _68 = _64;
        mContactMgr->clearContactPoints();
        _150->sub_71012A6B48();
    }
    _62 = true;
    mRigidBodyRequestMgr->x_0(false, mPaused);
    mRagdollInstanceMgr->calc();
    _62 = false;
}

void System::sub_7101216328() {
    if (_61)
        return;

    if (!mPaused)
        mWorlds[int(ContactLayerType::Entity)]->sub_71012B3F50(_64);
    if (!mPaused)
        mContactMgr->processImpulseEntries();
    mRigidBodyRequestMgr->calc1(ContactLayerType::Entity, mPaused);
    mRagdollInstanceMgr->calc1();
    if (mPaused)
        return;
    mRayCastRequestMgr->scheduleRequestProcessing();
    mContactListeners[int(ContactLayerType::Entity)]->clearTable();
    _150->sub_71012A6BB0();
    mRigidBodyRequestMgr->x_2();
}

void System::sub_71012163F0() {
    if (_61)
        return;
    mWorlds[int(ContactLayerType::Sensor)]->getCS().lock();
    _62 = true;
    mRigidBodyRequestMgr->x_0(true, mPaused);
    _62 = false;
}

void System::sub_710121652C() {
    if (_61)
        return;
    mWorlds[int(ContactLayerType::Entity)]->getCS().lock();
    sub_710121624C();
    sub_7101216328();
    mWorlds[int(ContactLayerType::Entity)]->getCS().unlock();
    sub_71012163F0();
    sub_7101216454();
}

void System::sub_7101216648() {
    if (mPaused)
        return;
    lockWorld(ContactLayerType::Entity);
    mRigidBodyRequestMgr->x_13();
    unlockWorld(ContactLayerType::Entity);
}

void System::sub_71012165F8(ContactLayerType type) {
    mWorlds[int(type)]->getCS().lock();
}

void System::sub_7101216620(ContactLayerType type) {
    mWorlds[int(type)]->getCS().unlock();
}

void System::sub_7101216790(bool value) {
    if (sead::ThreadMgr::instance()->getCurrentThread()->getPriority() <= sead::Thread::cDefaultPriority)
        _61 = value;
}

void System::lockWorld(ContactLayerType type, const char* description, int b,
                       OnlyLockIfNeeded only_lock_if_needed) {
    mWorlds[int(type)]->lockCS(description, b, only_lock_if_needed);
}

void System::unlockWorld(ContactLayerType type, const char* description, int b,
                         OnlyLockIfNeeded only_lock_if_needed) {
    mWorlds[int(type)]->unlockCS(description, b, only_lock_if_needed);
}

void System::incrementWorldUnkCounter(ContactLayerType layer_type) {
    mWorlds[int(layer_type)]->sub_71012B3FB0();
}

void System::decrementWorldUnkCounter(ContactLayerType layer_type) {
    mWorlds[int(layer_type)]->sub_71012B3FC8();
}

sead::Heap* System::getPhysicsTempHeap(LowPriority low_priority) const {
    if (low_priority != LowPriority::No ||
        sead::ThreadMgr::instance()->getCurrentThread()->getPriority() >
            sead::Thread::cDefaultPriority)
        return mPhysicsTempLowHeap;

    if (mPhysicsTempDefaultHeap->getMaxAllocatableSize(8) <= 0x2800)
        mPhysicsTempDefaultHeap->dump();

    return mPhysicsTempDefaultHeap;
}

void System::sub_7101215358(CharacterController* controller) {
    auto lock = sead::makeScopedLock(_270);
    _2b0.pushBack(controller);
}

void System::sub_71012153B4(CharacterController* controller) {
    auto lock = sead::makeScopedLock(_270);
    const s32 index = _2b0.indexOf(controller);
    if (index >= 0)
        _2b0.erase(index);
}

}  // namespace ksys::phys
