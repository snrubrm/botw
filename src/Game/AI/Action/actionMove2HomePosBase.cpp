#include "Game/AI/Action/actionMove2HomePosBase.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

Move2HomePosBase::Move2HomePosBase(const InitArg& arg) : ksys::act::ai::Action(arg) {}

Move2HomePosBase::~Move2HomePosBase() = default;

bool Move2HomePosBase::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void Move2HomePosBase::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void Move2HomePosBase::leave_() {
    if (auto* body = m32()) {
        body->setLinearVelocity(sead::Vector3f::zero);
        body->setAngularVelocity(sead::Vector3f::zero);
    }
}

void Move2HomePosBase::loadParams_() {
    getStaticParam(&mIsReturn_s, "IsReturn");
    getDynamicParam(&mDynMoveDis_d, "DynMoveDis");
    getDynamicParam(&mDynMoveSpeed_d, "DynMoveSpeed");
}

void Move2HomePosBase::calc_() {
    ksys::act::ai::Action::calc_();
}

ksys::phys::RigidBody* Move2HomePosBase::m32() {
    return mActor->getMainBody();
}

}  // namespace uking::action
