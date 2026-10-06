#include "Game/AI/Action/actionPlayerWait.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"

namespace uking::action {

PlayerWait::PlayerWait(const InitArg& arg) : PlayerAction(arg) {}

void PlayerWait::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerWait::leave_() {
    static_cast<ksys::act::Player*>(mActor)->_c48.reset(0x80);
    auto* player = static_cast<ksys::act::Player*>(mActor);
    player->_1e90 = 0.0f;
    player->_1e94 = 0.0f;
    player->_1e98 = -1.0f;
    if (mActor->getASList()->x_1(1, 1) == "WaitUpper" ||
        mActor->getASList()->x_1(1, 1) == "WaitAttentionUpper")
        static_cast<ksys::act::Player*>(mActor)->x_18(true);
    static_cast<ksys::act::Player*>(mActor)->x_19(-1.0f);
    static_cast<ksys::act::Player*>(mActor)->sub_710086952C();
}

void PlayerWait::calc_() {
    PlayerAction::calc_();
}

bool PlayerWait::isChangeable() const {
    return _1c;
}

}  // namespace uking::action
