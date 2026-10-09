#include "KingSystem/ActorSystem/actActorSystem.h"
#include <heap/seadExpHeap.h>
#include <mc/seadCoreInfo.h>
#include <thread/seadThread.h>
#include "KingSystem/ActorSystem/Profiles/actPlayerLink.h"
#include "KingSystem/Resource/resResourceMgrTask.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/Framework/frmWorkerSupportThreadMgr.h"
#include "KingSystem/Map/mapPlacementMgr.h"
#include "KingSystem/Terrain/teraSystem.h"

namespace ksys::act {

SEAD_SINGLETON_DISPOSER_IMPL(ActorSystem)

// NON_MATCHING: switch branch layout.
MessageTransceiverBase* ActorSystem::sub_7100D5D80C() {
    switch (sead::CoreInfo::getCurrentCoreId()) {
    case 1:
        return &_1c8;
    case 2:
        return &_220;
    default:
        return &_170;
    }
}

bool ActorSystem::callAutoPlacementMgrPreCalcFn(void*) {
    if (_298)
        _298->invoke();
    return true;
}

void ActorSystem::allocEmergencyHeap(sead::Heap* heap) {
    mEmergencyHeap = sead::ExpHeap::create(0x500000, "EmergencyHeap", heap, sizeof(void*),
                                           sead::Heap::cHeapDirection_Forward, false);
    mEmergencyHeap->enableLock(true);
}

void ActorSystem::insertActiveActor(Actor* actor) {
    if (!tera::checkTeraSystemStatus()) {
        auto* thread = sead::ThreadMgr::instance()->getCurrentThread();
        thread->getPriority();
    }
    if (!mActiveActors.isNodeLinked(actor))
        mActiveActors.pushBack(actor);
}

void ActorSystem::eraseFromActiveActorList(Actor* actor) {
    if (!tera::checkTeraSystemStatus()) {
        auto* thread = sead::ThreadMgr::instance()->getCurrentThread();
        thread->getPriority();
    }
    if (mActiveActors.isNodeLinked(actor))
        mActiveActors.erase(actor);
}

void ActorSystem::registerActorThatLostPlacementObj(Actor* actor) {
    if (!tera::checkTeraSystemStatus()) {
        auto* thread = sead::ThreadMgr::instance()->getCurrentThread();
        thread->getPriority();
    }
    if (actor->isDelete())
        return;
    if (!mActorsThatLostPlacementObj.isNodeLinked(actor))
        mActorsThatLostPlacementObj.pushBack(actor);
}

void ActorSystem::eraseActorThatLostPlacementObj(Actor* actor) {
    if (!tera::checkTeraSystemStatus()) {
        auto* thread = sead::ThreadMgr::instance()->getCurrentThread();
        thread->getPriority();
    }
    if (mActorsThatLostPlacementObj.isNodeLinked(actor))
        mActorsThatLostPlacementObj.erase(actor);
}

Actor* ActorSystem::getActorThatLostPlacementObj(const u32& hash_id) {
    if (!tera::checkTeraSystemStatus()) {
        auto* thread = sead::ThreadMgr::instance()->getCurrentThread();
        thread->getPriority();
    }
    for (auto& actor : mActorsThatLostPlacementObj) {
        if (hash_id == actor.mHashId)
            return &actor;
    }
    return nullptr;
}

bool ActorSystem::getAutoPlacementActorPos(const sead::SafeString& name,
                                           sead::Vector3f* pos) const {
    if (!_290)
        return false;
    return _290->invoke(name, pos);
}

void ActorSystem::invokeRadarMgrInvoker() {
    if (_278)
        _278->invoke(0);
}

void ActorSystem::invokeAutoPlacementMgrInvoker3() {
    if (_280)
        _280->invoke(0);
}

bool ActorSystem::getPlayer(ActorConstDataAccess* accessor) {
    if (_c0)
        return _c0->getActorViaAccessor(accessor);
    return accessor->acquire(nullptr);
}

PlayerBase* ActorSystem::getPlayer() {
    if (!_c0)
        return nullptr;
    return _c0->getPlayer();
}

void ActorSystem::handleActorCreateFailure() {
    _138 = true;
    ksys::res::ResourceMgrTask::instance()->sub_7101208400();
}

bool ActorSystem::getPlayerPosition(sead::Vector3f* out) {
    ActorConstDataAccess accessor;
    ActorSystem::instance()->getPlayer(&accessor);
    if (!accessor.hasProc())
        return false;
    accessor.getActorMtx().getTranslation(*out);
    return true;
}

bool ActorSystem::a() {
    if (!_278)
        return true;
    return _278->invoke(1);
}

bool ActorSystem::auto1() {
    if (!_280)
        return true;
    return _280->invoke(1);
}

void ActorSystem::callRadarMgrInvoker() {
    if (_278)
        _278->invoke(2);
}

void ActorSystem::callAutoPlacementInvoker3() {
    if (_280)
        _280->invoke(2);
}

void ActorSystem::auto4(void* a1, void* a2) {
    if (_288)
        _288->invoke(a1, a2);
}

bool ActorSystem::isPlacementMgrDynamicHeapOom() const {
    auto* mgr = map::PlacementMgr::instance();
    if (mgr) {
        sead::Heap* heap = mgr->mDynamicHeap;
        if (static_cast<f32>(heap->getFreeSize()) / static_cast<f32>(heap->getSize()) < 0.05f)
            return true;
    }
    return false;
}

void ActorSystem::submitReqCallAutoPlacementMgrFn() {
    frm::WorkerSupportThreadMgr::instance()->submitRequest(7, &_2a0);
}

}  // namespace ksys::act
