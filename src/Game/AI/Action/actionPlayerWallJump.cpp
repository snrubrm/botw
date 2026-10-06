#include "Game/AI/Action/actionPlayerWallJump.h"
#include "Game/gameUnk_710246d058.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Utils/MathUtil.h"

namespace uking::action {

PlayerWallJump::PlayerWallJump(const InitArg& arg) : PlayerAction(arg) {}

void PlayerWallJump::sub_7100823C4C() {
    auto* as_list = mActor->getASList();
    auto* player = static_cast<ksys::act::Player*>(mActor);
    as_list->sub_710115EFD0(0, true, false, player->get17d0()->getLeftStick().length());
    if (static_cast<ksys::act::Player*>(mActor)->get17d0()->sub_71008BD364() == 0.0f) {
        static_cast<ksys::act::Player*>(mActor)->getASList()->x_6(6, 0, 0.0f);
    } else {
        auto* current = static_cast<ksys::act::Player*>(mActor);
        current->getASList()->x_6(6, 0,
                                  ksys::util::sub_71011EE4B8(ksys::util::angleDiff(
                                      current->_1c74, current->x_5())) *
                                      ksys::util::sUnk_7101EC6BA4);
    }
}

void PlayerWallJump::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerWallJump::leave_() {}

void PlayerWallJump::loadParams_() {
    getStaticParam(&mJumpHeight_s, "JumpHeight");
    getStaticParam(&mJumpSpeedF_s, "JumpSpeedF");
}

void PlayerWallJump::calc_() {
    PlayerAction::calc_();
}

bool PlayerWallJump::isChangeable() const {
    return true;
}

bool PlayerWallJump::isFinished() const {
    if (static_cast<ksys::act::Player*>(mActor)->isSurfingOnGround())
        return true;
    auto* player = static_cast<ksys::act::Player*>(mActor);
    return player->_1770.y < player->_2158 - 0.5f;
}

}  // namespace uking::action
