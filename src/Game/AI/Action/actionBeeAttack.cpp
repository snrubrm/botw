#include "Game/AI/Action/actionBeeAttack.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

BeeAttack::BeeAttack(const InitArg& arg) : FlyMoveBase(arg) {}

BeeAttack::~BeeAttack() = default;

bool BeeAttack::init_(sead::Heap* heap) {
    return FlyMoveBase::init_(heap);
}

void BeeAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    FlyMoveBase::enter_(params);
    sead::Vector3f target;
    FlyMoveBase::m32(&target);
    sead::Vector3f pos;
    mActor->getMtx().getTranslation(pos);
    sead::Vector3f dir = target;
    dir -= pos;
    dir.normalize();
    _c8.setScaleAdd(*mThroughDist_s, dir, target);
}

void BeeAttack::leave_() {
    FlyMoveBase::leave_();
}

void BeeAttack::loadParams_() {
    FlyMoveBase::loadParams_();
    getStaticParam(&mThroughDist_s, "ThroughDist");
}

void BeeAttack::calc_() {
    FlyMoveBase::calc_();
}

void BeeAttack::m32(sead::Vector3f* target) {
    *target = _c8;
}

}  // namespace uking::action
