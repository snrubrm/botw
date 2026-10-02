#include "Game/AI/Action/actionPlayerCleaningAround.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actCCAccessor.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"

namespace uking::action {

PlayerCleaningAround::PlayerCleaningAround(const InitArg& arg) : PlayerAction(arg) {}

PlayerCleaningAround::~PlayerCleaningAround() = default;

bool PlayerCleaningAround::init_(sead::Heap* heap) {
    return PlayerAction::init_(heap);
}

void PlayerCleaningAround::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerCleaningAround::leave_() {
    if (auto* controller = mActor->getCharacterController()) {
        controller->sub_7100F5EEB8(1.0f);
        controller->sub_7100F63388(false, -1);
        controller->sub_7100F5F458(ksys::act::MotionType::_0);
    }
}

void PlayerCleaningAround::loadParams_() {
    getStaticParam(&mCleaningTime_s, "CleaningTime");
}

void PlayerCleaningAround::calc_() {
    PlayerAction::calc_();
}

}  // namespace uking::action
