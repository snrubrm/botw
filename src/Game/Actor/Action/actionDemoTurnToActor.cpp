#include "Game/Actor/Action/actionDemoTurnToActor.h"
#include <prim/seadDelegate.h>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorUniqueNameSearch.h"
#include "KingSystem/ActorSystem/actBaseProcMgr.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"

namespace uking::action {

DemoTurnToActor::DemoTurnToActor(const InitArg& arg) : TurnToActor(arg) {}

DemoTurnToActor::~DemoTurnToActor() = default;

bool DemoTurnToActor::init_(sead::Heap* heap) {
    return TurnToActor::init_(heap);
}

// NON_MATCHING: the accessor address is kept in a register around the final calls.
void DemoTurnToActor::enter_(ksys::act::ai::InlineParamPack* params) {
    TurnToActor::enter_(params);
    mFlags.set(Flag::Changeable);
    auto* actor = mActor;
    sub_71000EBE30(&_80, mActorName_d, mUniqueName_d);
    ksys::act::ActorLinkConstDataAccess accessor;
    ksys::act::acquireActor(&_80, &accessor);
    if (accessor.hasProc()) {
        sead::Vector3f position;
        actor->getMtx().getTranslation(position);
        sead::Vector3f direction = accessor.getActorMtx().getTranslation() - position;
        direction.y = 0.0f;
        direction.normalize();
        if (direction.isNan() ||
            (direction.x == 0.0f && direction.y == 0.0f && direction.z == 0.0f))
            direction = actor->getMtx().getBase(2);
        sead::Vector3f side = sead::Vector3f::ey.cross(direction);
        side.normalize();
        _90.setBase(0, side);
        _90.setBase(1, sead::Vector3f::ey);
        _90.setBase(2, direction);
        _90.setTranslation(position);

        if (auto* controller = mActor->getCharacterController()) {
            const sead::Vector3f forward = _90.getBase(2);
            controller->sub_7100F5EDBC(forward);
            controller->sub_7100F60500(_90);
        } else if (auto* body = mActor->getMainBody()) {
            body->setTransform(_90, ksys::phys::PropagateToLinkedMotions{true});
        } else {
            mActor->sub_71011C88C0(_90);
        }
    } else {
        _90 = actor->getMtx();
    }
}

// NON_MATCHING: stack placement of the delegate and unique-name search differs.
void DemoTurnToActor::sub_71000EBE30(ksys::act::BaseProcLink* link,
                                  const sead::SafeString& name,
                                  const sead::SafeString& unique_name) {
    auto* mgr = ksys::act::BaseProcMgr::instance();
    if (!mgr)
        return;
    if (unique_name.isEmpty()) {
        auto* proc = mgr->getProc(name, ksys::act::BaseProcMgr::ProcFilters(8));
        if (proc && sead::IsDerivedFrom<ksys::act::Actor>(proc))
            link->acquire(proc, false);
    } else {
        ksys::act::ActorUniqueNameSearch search(unique_name);
        sead::Delegate1<ksys::act::ActorUniqueNameSearch, ksys::act::BaseProc*> callback(
            &search, &ksys::act::ActorUniqueNameSearch::sub_7100EDCC10);
        mgr->forEachProc(name, callback, ksys::act::BaseProcMgr::ProcFilters(8));
        if (search.mLink.hasProc())
            *link = search.mLink;
    }
}

void DemoTurnToActor::leave_() {
    TurnToActor::leave_();
}

void DemoTurnToActor::loadParams_() {
    TurnToActor::loadParams_();
    getDynamicParam(&mActorName_d, "ActorName");
    getDynamicParam(&mUniqueName_d, "UniqueName");
}

void DemoTurnToActor::calc_() {
    TurnToActor::calc_();
}

sead::Matrix34f DemoTurnToActor::m33() {
    sead::Matrix34f mtx = _90;
    mtx.setTranslation(TurnToActor::m33().getTranslation());
    return mtx;
}

}  // namespace uking::action
