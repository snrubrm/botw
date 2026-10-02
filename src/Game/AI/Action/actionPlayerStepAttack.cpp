#include "Game/AI/Action/actionPlayerStepAttack.h"
#include "Game/Actor/actWeapon.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"
#include "KingSystem/ActorSystem/actActorWeapons.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"

namespace uking::action {

PlayerStepAttack::PlayerStepAttack(const InitArg& arg) : PlayerAction(arg) {}

void PlayerStepAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
    static_cast<ksys::act::Player*>(mActor)->_cec.setBit(1);
    static_cast<ksys::act::Player*>(mActor)->_cf0.setBit(25);
    static_cast<ksys::act::Player*>(mActor)->_cf0.setBit(26);
    static_cast<ksys::act::Player*>(mActor)->_c40.setBit(24);

    auto* player = static_cast<ksys::act::Player*>(mActor);
    if (player->_d30 != player->getEquipmentTypeName(1))
        static_cast<ksys::act::Player*>(mActor)->x_38(1);

    player = static_cast<ksys::act::Player*>(mActor);
    const int weapon_idx = player->playerWeapons_return0();
    if (auto* weapon = sead::DynamicCast<act::Weapon>(
            player->getWeapons()->getEquippedWeapon(weapon_idx))) {
        mActor->getASList()->goLimpFromHeadShotMaybe(0x2c, weapon->getProfile(), 0);
    }

    static_cast<ksys::act::Player*>(mActor)->switchToAnimSequenceMaybe("CutStep", true, -1.0f);
    if (auto* controller = mActor->getCharacterController()) {
        controller->sub_7100F5EF08(true);
        controller->sub_7100F62B70(*mJumpHeight_s *
                                   static_cast<ksys::act::Player*>(mActor)->getStatusEffectSpeed());
    }
}

void PlayerStepAttack::leave_() {
    sub_71005D79AC(mActor, static_cast<ksys::act::Player*>(mActor)->playerWeapons_return0(), act::Unk_71002edaec(1));
}

void PlayerStepAttack::loadParams_() {
    getStaticParam(&mJumpHeight_s, "JumpHeight");
}

void PlayerStepAttack::calc_() {
    PlayerAction::calc_();
}

bool PlayerStepAttack::isChangeable() const {
    return _1c;
}

}  // namespace uking::action
