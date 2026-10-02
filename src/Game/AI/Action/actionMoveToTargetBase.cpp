#include "Game/AI/Action/actionMoveToTargetBase.h"
#include <cmath>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actTag.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Physics/StaticCompound/physStaticCompoundMgr.h"
#include "KingSystem/Physics/System/physSystem.h"
#include "KingSystem/System/VFR.h"

namespace uking::action {

MoveToTargetBase::MoveToTargetBase(const InitArg& arg) : ksys::act::ai::Action(arg) {}

MoveToTargetBase::~MoveToTargetBase() = default;

bool MoveToTargetBase::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void MoveToTargetBase::enter_(ksys::act::ai::InlineParamPack* params) {
    _30.set(*mDynStartPos_d);
    mFlags.set(Flag::Changeable);
}

void MoveToTargetBase::leave_() {
    ksys::act::ai::Action::leave_();
}

void MoveToTargetBase::loadParams_() {
    getDynamicParam(&mDynTargetPos_d, "DynTargetPos");
    getDynamicParam(&mDynStartPos_d, "DynStartPos");
}

// NON_MATCHING: the original builds the identity part of `mtx` with scalar stores (elements 0x30..0x58 of
// the frame) instead of copying sead::Matrix34f::ident; everything else is identical.
void MoveToTargetBase::calc_() {
    auto* actor = mActor;
    if (ksys::act::hasTag(actor, ksys::act::tags::IsCurrentSuspendRigidBody)) {
        if (auto* body = actor->getMainBody())
            body->getPosition(&_30);
    }

    if (m32(&_30, mDynTargetPos_d))
        setFinished();

    sead::Matrix34f home_mtx;
    actor->getHomeMtx(&home_mtx);
    sead::Matrix34f mtx = sead::Matrix34f::ident;
    mtx.setTranslation(_30);
    if (auto* body = actor->getMainBody()) {
        if (auto* mgr = ksys::phys::System::instance()->getStaticCompoundMgr())
            mtx = mgr->getTransformedMatrix(actor->getFieldBodyGroup(), mtx);
        sead::Vector3f translation;
        mtx.getTranslation(translation);
        home_mtx.setTranslation(translation);
        body->changePositionAndRotation(home_mtx, sead::Mathf::epsilon());
    }
}

bool MoveToTargetBase::m32(sead::Vector3f* pos, const sead::Vector3f* target) {
    const f32 step = m33() * ksys::VFR::instance()->getDeltaFrame();
    const sead::Vector3f diff = *target - *pos;
    const f32 len = diff.length();
    if (len <= step) {
        pos->set(*target);
        return true;
    }
    const sead::Vector3f dir = diff * (1.0f / len);
    pos->setScaleAdd(step, dir, *pos);
    return false;
}

}  // namespace uking::action
