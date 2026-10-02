#include "Game/AI/Action/actionPlayerHorseGetOff.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actCCAccessor.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"

namespace uking::action {

PlayerHorseGetOff::PlayerHorseGetOff(const InitArg& arg) : PlayerAction(arg) {}

void PlayerHorseGetOff::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
    static_cast<ksys::act::Player*>(mActor)->_cec.set(0x2);
    static_cast<ksys::act::Player*>(mActor)->_cec.set(0x200000);
    static_cast<ksys::act::Player*>(mActor)->_c44.set(0x2);
    static_cast<ksys::act::Player*>(mActor)->x_18(true);
    static_cast<ksys::act::Player*>(mActor)->switchToAnimSequenceMaybe("DismountHorse", true, -1.0f);
    if (auto* controller = mActor->getCharacterController())
        controller->sub_7100F5F458(ksys::act::MotionType::Hover);
    _28 = 0;
    static_cast<ksys::act::Player*>(mActor)->_17f1 = true;
    static_cast<ksys::act::Player*>(mActor)->_1844 = ksys::Timer(30.0f, 30.0f);
}

void PlayerHorseGetOff::leave_() {
    if (auto* controller = mActor->getCharacterController())
        controller->sub_7100F5F458(ksys::act::MotionType::_1);
}

void PlayerHorseGetOff::loadParams_() {
    getStaticParam(&mSideFallSpeed_s, "SideFallSpeed");
}

void PlayerHorseGetOff::calc_() {
    PlayerAction::calc_();
}

bool PlayerHorseGetOff::isChangeable() const {
    return false;
}

}  // namespace uking::action
