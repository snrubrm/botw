#include "Game/Actor/Action/actionSwimRotateBase.h"
#include <cmath>
#include "Game/Actor/aiUnk_71007377D4.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/System/VFR.h"
#include "KingSystem/Utils/MathUtil.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "Game/Actor/aiUnk_710073fa90.h"

namespace uking::action {

SwimRotateBase::SwimRotateBase(const InitArg& arg) : WaterFloatBase(arg) {}

SwimRotateBase::~SwimRotateBase() = default;

bool SwimRotateBase::init_(sead::Heap* heap) {
    return WaterFloatBase::init_(heap);
}

void SwimRotateBase::enter_(ksys::act::ai::InlineParamPack* params) {
    WaterFloatBase::enter_(params);
    const f32 speed = mActor->getAngVelocity().length();
    _9c.value = speed;
    _9c.prev_value = speed;
    sub_710073FA90(&_78, mActor);
    mFlags.set(Flag::Changeable);
}

void SwimRotateBase::leave_() {
    WaterFloatBase::leave_();
}

void SwimRotateBase::loadParams_() {
    WaterFloatBase::loadParams_();
    getStaticParam(&mPosReduceRatio_s, "PosReduceRatio");
    getStaticParam(&mRotSpeed_s, "RotSpeed");
    getStaticParam(&mRotRatio_s, "RotRatio");
}

void SwimRotateBase::calc_() {
    WaterFloatBase::calc_();
    sub_710028B750();
}

// NON_MATCHING: target components load before the first direction stores.
void SwimRotateBase::sub_710028B750() {
    auto* actor = mActor;
    auto* controller = actor->getCharacterController();
    if (!controller) {
        setFailed();
        return;
    }
    const f32 delta = ksys::VFR::instance()->getDeltaFrame();
    sead::Vector3f velocity;
    controller->sub_7100F5F598(&velocity);
    const f32 decay = std::pow(*mPosReduceRatio_s, delta);
    velocity.x *= decay;
    velocity.z *= decay;
    velocity.y = _50;
    controller->sub_7100F5F6FC(velocity);
    const sead::Vector3f up = getReverseDirOrUp(controller->get70());
    sub_710073FA94(&_78, actor);
    const sead::Vector3f position = actor->getMtx().getTranslation();
    sead::Vector3f target;
    m32(&target);
    sead::Vector3f direction = target - position;
    ksys::util::sub_71011EFA00(&direction, direction, up);
    direction.normalize();
    _9c.lerp(*mRotSpeed_s, *mRotRatio_s, *mRotSpeed_s / 10.0f);
    _9c.updateStats();
    const f32 speed = _9c.value;
    sead::Vector3f forward;
    mActor->getMtx().getBase(forward, 2);
    ksys::util::sub_71011EFA00(&forward, forward, up);
    forward.normalize();
    sub_710074006C(&_78, direction, up, true, *mRotRatio_s, speed, speed / 10.0f);
    sub_7100740E04(_78, controller);
}

}  // namespace uking::action
