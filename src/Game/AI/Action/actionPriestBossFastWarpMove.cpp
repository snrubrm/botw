#include "Game/AI/Action/actionPriestBossFastWarpMove.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"

namespace uking::action {

// NON_MATCHING: the compiler removes redundant record zero stores after the bulk clear;
// default and explicit payload value initialization produce the same result.
PriestBossFastWarpMove::PriestBossFastWarpMove(const InitArg& arg) : PriestBossWarpOrVanish(arg) {}

PriestBossFastWarpMove::~PriestBossFastWarpMove() = default;

bool PriestBossFastWarpMove::init_(sead::Heap* heap) {
    return PriestBossWarpOrVanish::init_(heap);
}

void PriestBossFastWarpMove::enter_(ksys::act::ai::InlineParamPack* params) {
    PriestBossWarpOrVanish::enter_(params);
}

void PriestBossFastWarpMove::leave_() {
    PriestBossWarpOrVanish::leave_();
    if (auto* controller = mActor->getCharacterController()) {
        controller->sub_7100F60604();
        controller->sub_7100F5E764(true);
        controller->sub_7100F62CA8(true);
    }
    mActor->getActorFlags2().reset(ksys::act::Actor::ActorFlag2::_20);
}

void PriestBossFastWarpMove::loadParams_() {
    PriestBossWarpOrVanish::loadParams_();
    getStaticParam(&mAfterImage0AppearFrame_s, "AfterImage0AppearFrame");
    getStaticParam(&mAfterImage1AppearFrame_s, "AfterImage1AppearFrame");
    getStaticParam(&mAppearFrame_s, "AppearFrame");
    getStaticParam(&mASName_s, "ASName");
    getDynamicParam(&mCurrentFrame_d, "CurrentFrame");
    getDynamicParam(&mIsCloseMove_d, "IsCloseMove");
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getDynamicParam(&mMoveDstPos_d, "MoveDstPos");
    getDynamicParam(&mAfterImage0Pos_d, "AfterImage0Pos");
    getDynamicParam(&mAfterImage1Pos_d, "AfterImage1Pos");
}

void PriestBossFastWarpMove::calc_() {
    PriestBossWarpOrVanish::calc_();
}

}  // namespace uking::action
