#include "Game/AI/Action/actionPlayerLadderDownStart.h"
#include "Game/AI/aiUnk_7101e7c5d0.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/Utils/MathUtil.h"

namespace uking::action {

PlayerLadderDownStart::PlayerLadderDownStart(const InitArg& arg) : PlayerAction(arg) {}

void PlayerLadderDownStart::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
    static_cast<ksys::act::Player*>(mActor)->_cf0.set(0x200000);
    static_cast<ksys::act::Player*>(mActor)->_cec.set(0x10);
    static_cast<ksys::act::Player*>(mActor)->_cf0.set(0x200);
    static_cast<ksys::act::Player*>(mActor)->sub_71008697E4();
    static_cast<ksys::act::Player*>(mActor)->switchToAnimSequenceMaybe("LadderDownSt", true, -1.0f);
    static_cast<ksys::act::Player*>(mActor)->_17f0 = 0;

    auto* player = static_cast<ksys::act::Player*>(mActor);
    player->_181c = player->_1770;
    player = static_cast<ksys::act::Player*>(mActor);
    player->_1810 = player->_22f4;
    player = static_cast<ksys::act::Player*>(mActor);
    player->_1810.y = player->_1770.y;
    player = static_cast<ksys::act::Player*>(mActor);
    ksys::util::sub_71011EEEE0(&player->_1810, player->_1c84, 0.4f);

    if (auto* controller = mActor->getCharacterController())
        controller->enableContactLayer(ksys::phys::ContactLayer::EntityGround);

    player = static_cast<ksys::act::Player*>(mActor);
    const u32 reversed = player->_1c84 + 0x80000000u;
    const ksys::act::Player::Unk1 angle(ksys::util::sUnk_7101EC6BA0 & reversed);
    player->x_53(angle);
    player = static_cast<ksys::act::Player*>(mActor);
    player->_1c68 = player->_1c84;
}

void PlayerLadderDownStart::leave_() {
    if (auto* controller = mActor->getCharacterController())
        controller->disableContactLayer(ksys::phys::ContactLayer::EntityGround);
    static_cast<ksys::act::Player*>(mActor)->_1c70 = 0x80000000;
    static_cast<ksys::act::Player*>(mActor)->_d1c = 1;
    auto* player = static_cast<ksys::act::Player*>(mActor);
    const u32 reversed = player->_1c84 + 0x80000000u;
    player->_1c84 = ksys::util::sUnk_7101EC6BA0 & reversed;
    player = static_cast<ksys::act::Player*>(mActor);
    ksys::util::sub_71011EEEE0(&player->_22f4, player->_1c84, sUnk_7101e7c5d8);
}

void PlayerLadderDownStart::calc_() {
    PlayerAction::calc_();
}

bool PlayerLadderDownStart::isChangeable() const {
    return _1c;
}

}  // namespace uking::action
