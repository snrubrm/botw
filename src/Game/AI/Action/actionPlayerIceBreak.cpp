#include "Game/AI/Action/actionPlayerIceBreak.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/Awareness/actAwarenessInstance.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"

namespace uking::action {

PlayerIceBreak::PlayerIceBreak(const InitArg& arg) : PlayerAction(arg) {}

void PlayerIceBreak::enter_(ksys::act::ai::InlineParamPack* params) {
    const bool is_199 = static_cast<ksys::act::Player*>(mActor)->m199();
    PlayerAction::enter_(params);
    if (is_199)
        static_cast<ksys::act::Player*>(mActor)->_cec.set(0x4);
    if (static_cast<ksys::act::Player*>(mActor)->m199()) {
        if (auto* controller = mActor->getCharacterController())
            controller->sub_7100F5F270(static_cast<ksys::act::Player*>(mActor)->_1cd8);
        mActor->get548()->m8()->m10(0, true);
    }
    static_cast<ksys::act::Player*>(mActor)->switchToAnimSequenceMaybe("FreezeBreak", true, -1.0f);
}

void PlayerIceBreak::leave_() {
    if (static_cast<ksys::act::Player*>(mActor)->m199()) {
        static_cast<ksys::act::Player*>(mActor)->x_18(true);
        if (auto* controller = mActor->getCharacterController())
            controller->sub_7100F5F270(static_cast<ksys::act::Player*>(mActor)->_1cd4);
        mActor->get548()->m8()->m10(0, false);
    }
}

void PlayerIceBreak::calc_() {
    auto* player = static_cast<ksys::act::Player*>(mActor);
    player->_20bc.value = 0;
    player->_20bc.prev_value = 0;
    static_cast<ksys::act::Player*>(mActor)->actionCommon();
    m32();
}

bool PlayerIceBreak::isChangeable() const {
    return _1c;
}

}  // namespace uking::action
