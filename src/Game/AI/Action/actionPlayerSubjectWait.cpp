#include "Game/AI/Action/actionPlayerSubjectWait.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"

namespace uking::action {

PlayerSubjectWait::PlayerSubjectWait(const InitArg& arg) : PlayerAction(arg) {}

void PlayerSubjectWait::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerSubjectWait::leave_() {
    static_cast<ksys::act::PlayerBase*>(mActor)->_c44.resetBit(15);
    static_cast<ksys::act::Player*>(mActor)->_1c68 = static_cast<ksys::act::Player*>(mActor)->x_5();
    if (!static_cast<ksys::act::PlayerBase*>(mActor)->_d11)
        static_cast<ksys::act::Player*>(mActor)->x_18(true);
}

void PlayerSubjectWait::calc_() {
    PlayerAction::calc_();
}

bool PlayerSubjectWait::isChangeable() const {
    return true;
}

}  // namespace uking::action
