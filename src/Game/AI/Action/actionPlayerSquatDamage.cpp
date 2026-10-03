#include "Game/AI/Action/actionPlayerSquatDamage.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/ActorSystem/Awareness/actAwarenessInstance.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

PlayerSquatDamage::PlayerSquatDamage(const InitArg& arg) : PlayerAction(arg) {}

void PlayerSquatDamage::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
    static_cast<ksys::act::Player*>(mActor)->_cec.set(0x4);
    static_cast<ksys::act::Player*>(mActor)->_cec.set(0x80000000);
    static_cast<ksys::act::Player*>(mActor)->switchToAnimSequenceMaybe("SquatDamage", true, -1.0f);
    auto* player = static_cast<ksys::act::Player*>(mActor);
    player->_20bc.value = 0;
    player->_20bc.prev_value = 0;
    if (auto* controller = mActor->getCharacterController())
        controller->sub_7100F5F270(static_cast<ksys::act::Player*>(mActor)->_1cd8);
    mActor->get548()->m8()->m10(0, true);
}

void PlayerSquatDamage::leave_() {
    if (auto* controller = mActor->getCharacterController())
        controller->sub_7100F5F270(static_cast<ksys::act::Player*>(mActor)->_1cd4);
    mActor->get548()->m8()->m10(0, false);
}

void PlayerSquatDamage::calc_() {
    static_cast<ksys::act::Player*>(mActor)->sub_7100877BD8();
    m32();
    static_cast<ksys::act::Player*>(mActor)->actionCommon();
}

bool PlayerSquatDamage::isChangeable() const {
    return _1c;
}

}  // namespace uking::action
