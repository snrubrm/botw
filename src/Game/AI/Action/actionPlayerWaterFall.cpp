#include "Game/AI/Action/actionPlayerWaterFall.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actCCAccessor.h"

namespace uking::action {

PlayerWaterFall::PlayerWaterFall(const InitArg& arg) : PlayerAction(arg) {}

PlayerWaterFall::~PlayerWaterFall() = default;

void PlayerWaterFall::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerWaterFall::leave_() {
    if (auto* controller = mActor->getCharacterController()) {
        controller->sub_7100F5F458(ksys::act::MotionType::_1);
        controller->mFlags.reset(0x20000);
    }
}

void PlayerWaterFall::loadParams_() {
    getStaticParam(&mSpeedClimb_s, "SpeedClimb");
    getDynamicParam(&mRailPtr_d, "RailPtr");
    getDynamicParam(&mFrontDir_d, "FrontDir");
}

void PlayerWaterFall::calc_() {
    PlayerAction::calc_();
}

bool PlayerWaterFall::isChangeable() const {
    return false;
}

}  // namespace uking::action
