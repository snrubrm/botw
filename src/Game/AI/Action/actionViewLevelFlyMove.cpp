#include "Game/AI/Action/actionViewLevelFlyMove.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/System/VFR.h"
#include "KingSystem/Utils/MathUtil.h"

namespace uking::action {

ViewLevelFlyMove::ViewLevelFlyMove(const InitArg& arg) : WizzrobeVisibleWalk(arg) {}

ViewLevelFlyMove::~ViewLevelFlyMove() = default;

bool ViewLevelFlyMove::init_(sead::Heap* heap) {
    return WizzrobeVisibleWalk::init_(heap);
}

void ViewLevelFlyMove::enter_(ksys::act::ai::InlineParamPack* params) {
    WizzrobeVisibleWalk::enter_(params);
}

void ViewLevelFlyMove::leave_() {
    WizzrobeVisibleWalk::leave_();
}

void ViewLevelFlyMove::loadParams_() {
    WizzrobeVisibleWalk::loadParams_();
    getDynamicParam(&mAttPos_d, "AttPos");
}

void ViewLevelFlyMove::calc_() {
    WizzrobeVisibleWalk::calc_();
}

void ViewLevelFlyMove::m36(sead::Vector3f* dir) {
    const sead::Vector3f& target = *mAttPos_d;
    sead::Vector3f pos;
    mActor->getMtx().getTranslation(pos);
    *dir = {target.x - pos.x, 0, target.z - pos.z};
}

// NON_MATCHING: vector temporaries, registers and stack layout.
void ViewLevelFlyMove::m37(sead::Vector3f* dir) {
    sead::Vector3f target;
    m34(&target);
    target.x -= mActor->getMtx().getTranslation().x;
    target.z -= mActor->getMtx().getTranslation().z;
    target.y = 0.0f;
    sead::Vector3f velocity = mActor->getVelocity();
    velocity.y = 0.0f;
    if (target.x == 0.0f && target.z == 0.0f) {
        if (velocity.x == 0.0f && velocity.z == 0.0f)
            return;
    } else {
        target.normalize();
        if (velocity.x == 0.0f && velocity.z == 0.0f) {
            *dir = target;
            return;
        }
        velocity.normalize();
        static_cast<void>(ksys::util::sub_71011EECAC(
            &velocity, velocity, target,
            ksys::VFR::instance()->getDeltaFrame() * sead::Mathf::deg2rad(4.0f)));
    }
    velocity.normalize();
    *dir = velocity;
}

}  // namespace uking::action
