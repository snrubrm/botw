#include "Game/AI/Action/actionPlayerCutReverse.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"
#include "Game/gameRumble.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

PlayerCutReverse::PlayerCutReverse(const InitArg& arg) : PlayerAction(arg) {}

void PlayerCutReverse::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
    static_cast<ksys::act::Player*>(mActor)->_cec.set(0x1000000);
    auto* player = static_cast<ksys::act::Player*>(mActor);
    player->_20bc.value = 0;
    player->_20bc.prev_value = 0;
    static_cast<ksys::act::Player*>(mActor)->switchToAnimSequenceMaybe("CutReverse", true, -1.0f);
    static_cast<ksys::act::Player*>(mActor)->_1c68 = static_cast<ksys::act::Player*>(mActor)->x_5();
    static_cast<ksys::act::Player*>(mActor)->actionCommon();
    Rumble::instance()->sub_7100897FE4(1, 1);
}

void PlayerCutReverse::leave_() {}

void PlayerCutReverse::calc_() {
    static_cast<ksys::act::Player*>(mActor)->sub_7100877BD8();
    m32();
    static_cast<ksys::act::Player*>(mActor)->actionCommon();
}

bool PlayerCutReverse::isChangeable() const {
    return _1c;
}

}  // namespace uking::action
