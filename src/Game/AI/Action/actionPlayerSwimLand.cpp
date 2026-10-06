#include "Game/AI/Action/actionPlayerSwimLand.h"
#include <math/seadMathCalcCommon.h>
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"

namespace uking::action {

PlayerSwimLand::PlayerSwimLand(const InitArg& arg) : PlayerAction(arg) {}

void PlayerSwimLand::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
    static_cast<ksys::act::Player*>(mActor)->_cec.set(0x400);
    static_cast<ksys::act::Player*>(mActor)->switchToAnimSequenceMaybe("SwimWait", true, -1.0f);
    auto* player = static_cast<ksys::act::Player*>(mActor);
    player->_20bc.value = 0.3f;
    player->_20bc.prev_value = 0.3f;
    static_cast<ksys::act::Player*>(mActor)->_1844 = ksys::Timer(15.0f, 15.0f);
}

void PlayerSwimLand::leave_() {}

// NON_MATCHING: scheduling of the Matrix34f(_1b6c * _1b48) multiply (same operations); see PlayerWaterDivingJump::calc_.
void PlayerSwimLand::calc_() {
    auto* controller = mActor->getCharacterController();
    if (!controller)
        return;
    // discarded call (in the target)
    controller->sub_7100F61A34()->getCenterOfMassInWorld();
    auto* player = static_cast<ksys::act::Player*>(mActor);
    player->_1b18 = player->_1b6c * sead::Matrix34f(player->_1b48);
    static_cast<ksys::act::Player*>(mActor)->actionCommon();
    auto& timer = static_cast<ksys::act::Player*>(mActor)->_1844;
    if (timer.value <= sead::Mathf::epsilon())
        setFinished();
    else
        timer.update();
}

bool PlayerSwimLand::isChangeable() const {
    return false;
}

}  // namespace uking::action
