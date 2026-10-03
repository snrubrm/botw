#include "Game/AI/Action/actionPlayerSquatWait.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/Awareness/actAwarenessInstance.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"

namespace uking::action {

PlayerSquatWait::PlayerSquatWait(const InitArg& arg) : PlayerAction(arg) {}

void PlayerSquatWait::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerSquatWait::leave_() {
    if (auto* controller = mActor->getCharacterController())
        controller->sub_7100F5F270(static_cast<ksys::act::Player*>(mActor)->_1cd4);
    mActor->get548()->m8()->m10(0, false);
    static_cast<ksys::act::Player*>(mActor)->x_19(-1.0f);
    if (mActor->getASList()->x_1(1, 1) == "SquatWaitUpper")
        static_cast<ksys::act::Player*>(mActor)->x_18(true);
}

void PlayerSquatWait::loadParams_() {
    getStaticParam(&mWaitTime_s, "WaitTime");
    getStaticParam(&mAtnTurnDiffAng_s, "AtnTurnDiffAng");
}

void PlayerSquatWait::calc_() {
    PlayerAction::calc_();
}

bool PlayerSquatWait::isChangeable() const {
    return _1c;
}

}  // namespace uking::action
