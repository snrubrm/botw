#include "Game/AI/Action/actionPlayerSelfCamera.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"
#include "Game/Actor/actCameraUtil.h"

namespace uking::action {

PlayerSelfCamera::PlayerSelfCamera(const InitArg& arg) : PlayerAction(arg) {}

void PlayerSelfCamera::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
    static_cast<ksys::act::Player*>(mActor)->_cf4.set(0x1);
    static_cast<ksys::act::Player*>(mActor)->_cec.set(0x1);
    static_cast<ksys::act::Player*>(mActor)->_cf0.set(0x4);
    static_cast<ksys::act::Player*>(mActor)->_cf0.set(0x80000);
    auto* player = static_cast<ksys::act::Player*>(mActor);
    player->_20bc.value = 0;
    player->_20bc.prev_value = 0;
    static_cast<ksys::act::Player*>(mActor)->switchToAnimSequenceMaybe("Wait", true, -1.0f);
    static_cast<ksys::act::Player*>(mActor)->_17f0 = 1;
    const u32 angle = sub_710092DBA4().value ^ 0x80000000;
    static_cast<ksys::act::Player*>(mActor)->_1834 =
        ksys::util::Unk_7101EC6BAC(ksys::util::sUnk_7101EC6BA0 & angle);
}

void PlayerSelfCamera::leave_() {}

void PlayerSelfCamera::calc_() {
    PlayerAction::calc_();
}

bool PlayerSelfCamera::isChangeable() const {
    return true;
}

}  // namespace uking::action
