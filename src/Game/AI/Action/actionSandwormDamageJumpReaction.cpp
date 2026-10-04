#include "Game/AI/Action/actionSandwormDamageJumpReaction.h"
#include "Game/AI/aiUnk_71007377D4.h"
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

// 0x710023fb98
bool SandwormDamageJumpReaction::isFinished() const {
    return ksys::act::ai::Action::isFinished() || sub_710023F818();
}

void SandwormDamageJumpReaction::calc_() {
    if (!isFinished() && sub_710023F818())
        setFinished();
    if (_68)
        _68 = false;
    auto* actor = mActor;
    const sead::Vector3f gravity = getGravity(actor) * (1.0f / 900.0f);
    if (auto* controller = actor->getCharacterController()) {
        sub_7100737C0C(controller, *mReduceGravityRate_s, gravity);
        sub_7100738660(controller, *mReduceRotRate_s);
    }
}

}  // namespace uking::action
