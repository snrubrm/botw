#include "Game/AI/Action/actionPlayerSkin.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/ActorSystem/Attention/actAttentionSingleton.h"
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
    player->_20bc.value = 0;
    player->_20bc.prev_value = 0;
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
    auto* player = static_cast<ksys::act::Player*>(mActor);
    player->_20bc.value = 0;
    player->_20bc.prev_value = 0;
    static_cast<ksys::act::Player*>(mActor)->actionCommon();
    player = static_cast<ksys::act::Player*>(mActor);
    if (!player->_17f0) {
        if (!(player->_1850.value <= sead::Mathf::epsilon())) {
            player->_1850.update();
        } else {
            if (ksys::act::Attention::instance()->sub_7100D748FC(0x180000a))
                ksys::act::Attention::instance()->sub_7100D74530(0x180000a, nullptr);
            static_cast<ksys::act::Player*>(mActor)->_17f0 = 1;
        }
    }
    player = static_cast<ksys::act::Player*>(mActor);
    if (!(player->_1844.value <= sead::Mathf::epsilon())) {
        player->_1844.update();
        return;
    }
    _1c = true;
    if (ksys::act::sub_710086B194() != 0x180000a)
        setFinished();
}

bool PlayerSkin::isChangeable() const {
    return _1c;
}

}  // namespace uking::action
