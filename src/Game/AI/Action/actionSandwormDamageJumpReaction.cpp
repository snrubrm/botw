#include "Game/AI/Action/actionSandwormDamageJumpReaction.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "Game/Actor/actSandworm.h"

namespace uking::action {

SandwormDamageJumpReaction::SandwormDamageJumpReaction(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

SandwormDamageJumpReaction::~SandwormDamageJumpReaction() = default;

bool SandwormDamageJumpReaction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void SandwormDamageJumpReaction::enter_(ksys::act::ai::InlineParamPack* params) {
    _68 = true;
    if (auto* sandworm = sead::DynamicCast<act::Sandworm>(mActor)) {
        sandworm->_15b0 = *mTargetSandOffset_s;
        sandworm->_1638 = 1;
        sandworm->_15ac = *mSandOffsetSpeed_s;
        sandworm->_1638 = 1;
    }
    if (auto* controller = mActor->getCharacterController()) {
        controller->sub_7100F5EF08(true);
        controller->sub_7100F62B70(*mJumpHeight_s);
    }
    if (!mASName_s.isEmpty())
        playAS(mASName_s.cstr(), true, 0, 0, -1.0f);
}

void SandwormDamageJumpReaction::leave_() {
    ksys::act::ai::Action::leave_();
}

void SandwormDamageJumpReaction::loadParams_() {
    getStaticParam(&mTargetSandOffset_s, "TargetSandOffset");
    getStaticParam(&mSandOffsetSpeed_s, "SandOffsetSpeed");
    getStaticParam(&mJumpHeight_s, "JumpHeight");
    getStaticParam(&mReduceGravityRate_s, "ReduceGravityRate");
    getStaticParam(&mReduceRotRate_s, "ReduceRotRate");
    getStaticParam(&mWaitASFinish_s, "WaitASFinish");
    getStaticParam(&mWaitSandOffset_s, "WaitSandOffset");
    getStaticParam(&mASName_s, "ASName");
}

void SandwormDamageJumpReaction::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
