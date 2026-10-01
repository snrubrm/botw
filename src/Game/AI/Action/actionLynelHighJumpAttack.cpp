#include "Game/AI/Action/actionLynelHighJumpAttack.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

LynelHighJumpAttack::LynelHighJumpAttack(const InitArg& arg) : JumpAttack(arg) {}

LynelHighJumpAttack::~LynelHighJumpAttack() = default;

bool LynelHighJumpAttack::init_(sead::Heap* heap) {
    return JumpAttack::init_(heap);
}

void LynelHighJumpAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    JumpAttack::enter_(params);
}

void LynelHighJumpAttack::leave_() {
    JumpAttack::leave_();
}

void LynelHighJumpAttack::loadParams_() {
    JumpAttack::loadParams_();
}

void LynelHighJumpAttack::calc_() {
    JumpAttack::calc_();
}

f32 LynelHighJumpAttack::m33() {
    return mActor->getVelocity().y < -0.1f ? 0.99f : 1.0f;
}

}  // namespace uking::action
