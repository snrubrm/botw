#include "Game/AI/Action/actionPlayerDemoAirWait.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actCCAccessor.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"

namespace uking::action {

PlayerDemoAirWait::PlayerDemoAirWait(const InitArg& arg) : PlayerAction(arg) {}

void PlayerDemoAirWait::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerDemoAirWait::leave_() {
    if (auto* controller = mActor->getCharacterController())
        controller->sub_7100F5F458(ksys::act::MotionType::_1);
}

void PlayerDemoAirWait::calc_() {
    auto* player = static_cast<ksys::act::Player*>(mActor);
    player->_20bc.value = 0;
    player->_20bc.prev_value = 0;
    static_cast<ksys::act::Player*>(mActor)->actionCommon();
    if (static_cast<ksys::act::Player*>(mActor)->_17f0)
        return;
    if (static_cast<ksys::act::Player*>(mActor)->isShootingBow()) {
        if (mActor->getASList()->x_4(1, 1)) {
            static_cast<ksys::act::Player*>(mActor)->x_18(true);
            auto* proc = static_cast<ksys::act::Player*>(mActor)->_2c28.getProc(nullptr, nullptr);
            if (auto* actor = sead::DynamicCast<ksys::act::Actor>(proc))
                actor->wakeUp(ksys::act::BaseProc::SleepWakeReason::_0);
            static_cast<ksys::act::Player*>(mActor)->switchToAnimSequenceMaybe("ParaEquipOn", true,
                                                                               -1.0f);
            static_cast<ksys::act::Player*>(mActor)->_cec.set(0x8000);
        }
    } else if (mActor->getASList()->x_1(0, 0) == "ParaEquipOn") {
        if (mActor->getASList()->x_4(0, 0))
            static_cast<ksys::act::Player*>(mActor)->switchToAnimSequenceMaybe("ParashawlGlide", true,
                                                                               -1.0f);
    }
}

bool PlayerDemoAirWait::isChangeable() const {
    return false;
}

}  // namespace uking::action
