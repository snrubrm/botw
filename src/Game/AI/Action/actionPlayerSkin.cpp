#include "Game/AI/Action/actionPlayerSkin.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

PlayerSkin::PlayerSkin(const InitArg& arg) : PlayerAction(arg) {}

// NON_MATCHING: the original loads mActor between the WaitTime pointer and its value; regalloc
void PlayerSkin::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
    static_cast<ksys::act::Player*>(mActor)->_cec.set(0x1);
    static_cast<ksys::act::Player*>(mActor)->_1844 = ksys::Timer(*mWaitTime_s, *mWaitTime_s);
    const f32 time = sead::Mathf::min(*mWaitTime_s, 5.0f);
    static_cast<ksys::act::Player*>(mActor)->_1850 = ksys::Timer(time, time);
    static_cast<ksys::act::Player*>(mActor)->_17f0 = 0;
    static_cast<ksys::act::Player*>(mActor)->switchToAnimSequenceMaybe("SquatWait", true, -1.0f);
    auto* player = static_cast<ksys::act::Player*>(mActor);
    player->_20bc = 0;
    player->_20c0 = 0;
    if (auto* controller = mActor->getCharacterController())
        controller->sub_7100F5F270(static_cast<ksys::act::Player*>(mActor)->_1cd8);
}

void PlayerSkin::leave_() {
    if (auto* controller = mActor->getCharacterController())
        controller->sub_7100F5F270(static_cast<ksys::act::Player*>(mActor)->_1cd4);
}

void PlayerSkin::loadParams_() {
    getStaticParam(&mWaitTime_s, "WaitTime");
}

void PlayerSkin::calc_() {
    PlayerAction::calc_();
}

bool PlayerSkin::isChangeable() const {
    return _1c;
}

}  // namespace uking::action
