#include "Game/AI/Action/actionPlayerSquatMove.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/Awareness/actAwarenessInstance.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"

namespace uking::action {

PlayerSquatMove::PlayerSquatMove(const InitArg& arg) : PlayerAction(arg) {}

void PlayerSquatMove::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
    static_cast<ksys::act::Player*>(mActor)->_cec.set(0x8000000);
    static_cast<ksys::act::Player*>(mActor)->_cec.set(0x10000000);
    static_cast<ksys::act::Player*>(mActor)->_cec.set(0x4);
    static_cast<ksys::act::Player*>(mActor)->_cf4.set(0x40000);
    static_cast<ksys::act::Player*>(mActor)->_cf0.set(0x4);
    static_cast<ksys::act::Player*>(mActor)->_cf4.set(0x10);
    static_cast<ksys::act::Player*>(mActor)->_cf0.set(0x200);
    static_cast<ksys::act::Player*>(mActor)->_cf4.set(0x400000);
    static_cast<ksys::act::Player*>(mActor)->_cf4.set(0x4000);
    if (auto* controller = mActor->getCharacterController())
        controller->sub_7100F5F270(static_cast<ksys::act::Player*>(mActor)->_1cd8);
    mActor->get548()->m8()->m10(0, true);
}

void PlayerSquatMove::leave_() {
    if (auto* controller = mActor->getCharacterController())
        controller->sub_7100F5F270(static_cast<ksys::act::Player*>(mActor)->_1cd4);
    mActor->get548()->m8()->m10(0, false);
    if (mActor->getASList()->x_1(1, 1) == "SquatMoveUpper")
        static_cast<ksys::act::Player*>(mActor)->x_18(true);
}

void PlayerSquatMove::calc_() {
    PlayerAction::calc_();
}

bool PlayerSquatMove::isChangeable() const {
    return true;
}

}  // namespace uking::action
