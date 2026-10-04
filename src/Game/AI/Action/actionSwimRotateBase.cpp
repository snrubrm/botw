#include "Game/AI/Action/actionSwimRotateBase.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "Game/AI/aiUnk_710073fa90.h"

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

}  // namespace uking::action
