#include "Game/Actor/Player/Action/actionPlayerStepAttack.h"
#include "Game/Actor/actWeapon.h"
#include "Game/Actor/aiUnk_71005D6D10.h"
#include "Game/gameUnk_710246d058.h"
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

// NON_MATCHING: mActor is loaded before the second AS query branch (same as PlayerCutAfterJump::calc_).
void PlayerStepAttack::calc_() {
    if (static_cast<ksys::act::Player*>(mActor)->isSurfingOnGround()) {
        auto* player = static_cast<ksys::act::Player*>(mActor);
        if (player->_cec.isOnBit(1))
            player->_cec.resetBit(1);
        player = static_cast<ksys::act::Player*>(mActor);
        player->_20bc.value = 0;
        player->_20bc.prev_value = 0;
        if (mActor->getASList()->x_1(0, 0) == "CutStep") {
            if (mActor->getASList()->x_4(0, 0)) {
                static_cast<ksys::act::Player*>(mActor)->switchToAnimSequenceMaybe("CutStepLand",
                                                                                   true, -1.0f);
                static_cast<ksys::act::Player*>(mActor)->sub_7100877BD8();
            }
        } else {
            static_cast<ksys::act::Player*>(mActor)->sub_7100877BD8();
            m32();
        }
    }
    if (static_cast<ksys::act::Player*>(mActor)->_d10)
        static_cast<ksys::act::Player*>(mActor)->sub_7100856A7C();
    static_cast<ksys::act::Player*>(mActor)->actionCommon();

    ksys::as::ASList::Unk4 query;
    if (mActor->getASList()->x(3, &query, 0, 0, &ksys::as::ASList::Unk2::sub_710116383C, true)) {
        static_cast<ksys::act::Player*>(mActor)->sub_7100892F5C(&query);
        auto* player = static_cast<ksys::act::Player*>(mActor);
        sub_71005D7F4C(player, player->playerWeapons_return0(), 0, &query.name, nullptr, 1, 1.0f,
                       1.0f);
    } else if (mActor->getASList()->x(3, nullptr, 0, 0, &ksys::as::ASList::Unk2::sub_710116388C,
                                      true)) {
        auto* player = static_cast<ksys::act::Player*>(mActor);
        sub_71005D79AC(player, player->playerWeapons_return0(), act::Unk_71002edaec(1));
    }

    if (static_cast<ksys::act::Player*>(mActor)->_c40.isOnBit(24)) {
        if (!static_cast<ksys::act::Player*>(mActor)->_17d0->playerCheckController(3))
            static_cast<ksys::act::Player*>(mActor)->_c40.resetBit(24);
        if (mActor->getASList()->x(55, nullptr, 0, 0, &ksys::as::ASList::Unk2::sub_71011637EC,
                                   true) &&
            static_cast<ksys::act::Player*>(mActor)->_17d0->playerCheckController(3))
            setFinished();
    }
}

bool PlayerStepAttack::isChangeable() const {
    return _1c;
}

}  // namespace uking::action
