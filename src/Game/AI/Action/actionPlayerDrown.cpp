#include "Game/AI/Action/actionPlayerDrown.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"
#include "KingSystem/XLink/xlinkActorUtil.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"

namespace uking::action {

PlayerDrown::PlayerDrown(const InitArg& arg) : PlayerAction(arg) {}

void PlayerDrown::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
    static_cast<ksys::act::Player*>(mActor)->_cec.setBit(10);
    static_cast<ksys::act::Player*>(mActor)->_cec.setBit(31);
    static_cast<ksys::act::Player*>(mActor)->_cf4.setBit(7);
    static_cast<ksys::act::Player*>(mActor)->_cf4.setBit(8);
    static_cast<ksys::act::Player*>(mActor)->x_8(false, false);
    if (!static_cast<ksys::act::Player*>(mActor)->x_2())
        static_cast<ksys::act::Player*>(mActor)->switchToAnimSequenceMaybe("SwimDead", true, -1.0f);
    ksys::eft::searchAndEmitSLink(mActor, "warp", false);
    auto* player = static_cast<ksys::act::Player*>(mActor);
    player->_20bc = 0;
    player->_20c0 = 0;
    if (auto* controller = mActor->getCharacterController())
        controller->sub_7100F5F6FC(sead::Vector3f::zero);
    static_cast<ksys::act::Player*>(mActor)->_17f0 = 0;
}

void PlayerDrown::leave_() {
    PlayerAction::leave_();
}

void PlayerDrown::loadParams_() {}

void PlayerDrown::calc_() {
    PlayerAction::calc_();
}

bool PlayerDrown::isChangeable() const {
    return false;
}

}  // namespace uking::action
