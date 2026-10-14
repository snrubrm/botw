#include "Game/Actor/Action/actionTurnIgnite.h"
#include "Game/Actor/aiUnk_71007377D4.h"
#include "Game/Actor/aiUnk_710073fa90.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/Utils/MathUtil.h"

namespace uking::action {

TurnIgnite::TurnIgnite(const InitArg& arg) : StopASIgnite(arg) {}

TurnIgnite::~TurnIgnite() = default;

bool TurnIgnite::init_(sead::Heap* heap) {
    return StopASIgnite::init_(heap);
}

void TurnIgnite::enter_(ksys::act::ai::InlineParamPack* params) {
    StopASIgnite::enter_(params);
    auto* controller = mActor->getCharacterController();
    if (!controller)
        return;
    const sead::Vector3f up = getUpDir(controller->get70());
    sead::Vector3f velocity = mActor->getVelocity();
    ksys::util::sub_71011EFA00(&velocity, velocity, up);
    _c0.value = velocity.normalize();
    _c0.prev_value = _c0.value;
    sub_710072C1B4(controller, velocity);
    _90.value = mActor->getAngVelocity().length();
    _90.prev_value = _90.value;
    sub_710073FA90(&_9c, mActor);
    sead::Vector3f target = *mTargetPos_d;
    target -= mActor->getMtx().getTranslation();
    ksys::util::sub_71011EFA00(&target, target, up);
    target.normalize();
    sead::Vector3f forward;
    mActor->getMtx().getBase(forward, 2);
    ksys::util::sub_71011EFA00(&forward, forward, up);
    forward.normalize();
    sead::Vector3f axis;
    f32 angle;
    ksys::util::sub_71011EEB08(&axis, &angle, forward, target, sead::Vector3f::ey);
    mActor->getASList()->x_6(9, 0, sead::Mathf::rad2deg(angle) * axis.y);
    mFlags.set(Flag::Changeable);
}

void TurnIgnite::leave_() {
    StopASIgnite::leave_();
}

void TurnIgnite::loadParams_() {
    StopASIgnite::loadParams_();
    getStaticParam(&mRotSpd_s, "RotSpd");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

void TurnIgnite::calc_() {
    StopASIgnite::calc_();
    auto* controller = mActor->getCharacterController();
    if (!controller)
        return;
    const sead::Vector3f up = getUpDir(controller->get70());
    sub_710073FA94(&_9c, mActor);
    _c0 *= 0.7f;
    _c0.updateStats();
    sead::Vector3f dir = *mTargetPos_d;
    const sead::Vector3f pos = mActor->getMtx().getTranslation();
    dir -= pos;
    ksys::util::sub_71011EFA00(&dir, dir, up);
    dir.normalize();
    _90.lerp(*mRotSpd_s, 0.16f, *mRotSpd_s / 10.0f);
    _90.updateStats();
    sub_710074006C(&_9c, dir, up, true, 0.16f, _90.value, _90.value / 10.0f);
    controller->sub_7100F5E7F0(_c0.value * 30.0f);
    sub_7100740E04(_9c, controller);
}

}  // namespace uking::action
