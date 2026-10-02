#include "Game/AI/Action/actionPlayerCutAfterJump.h"
#include "Game/Actor/actWeapon.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/gameUnk_710246d058.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActorWeapons.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"

namespace uking::action {

PlayerCutAfterJump::PlayerCutAfterJump(const InitArg& arg) : PlayerAction(arg) {}

void PlayerCutAfterJump::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
    static_cast<ksys::act::Player*>(mActor)->_cf0.setBit(25);
    static_cast<ksys::act::Player*>(mActor)->_cf4.setBit(31);

    auto* player = static_cast<ksys::act::Player*>(mActor);
    if (!player->_17d0->playerCheckController(13) || player->m202() || player->_c44.isOnBit(13) ||
        player->m178()) {
        static_cast<ksys::act::Player*>(mActor)->_cf0.setBit(26);
    }

    player = static_cast<ksys::act::Player*>(mActor);
    if (player->_d30 != player->getEquipmentTypeName(1))
        static_cast<ksys::act::Player*>(mActor)->x_38(1);

    player = static_cast<ksys::act::Player*>(mActor);
    const int weapon_idx = player->playerWeapons_return0();
    if (auto* weapon = sead::DynamicCast<act::Weapon>(
            player->getWeapons()->getEquippedWeapon(weapon_idx))) {
        mActor->getASList()->goLimpFromHeadShotMaybe(0x2c, weapon->getProfile(), 0);
    }

    const u8 type = static_cast<ksys::act::Player*>(mActor)->_d1c;
    if (type == 2)
        mActor->getASList()->x_6(9, 0, 90.0f);
    else if (type == 3)
        mActor->getASList()->x_6(9, 0, -90.0f);
    else if (type == 1)
        mActor->getASList()->x_6(9, 0, -180.0f);
    else
        mActor->getASList()->x_6(9, 0, 0.0f);

    static_cast<ksys::act::Player*>(mActor)->switchToAnimSequenceMaybe("CutAfterJump", true, -1.0f);
}

void PlayerCutAfterJump::leave_() {
    static_cast<ksys::act::Player*>(mActor)->_14c0 = false;
    sub_71005D79AC(mActor, static_cast<ksys::act::Player*>(mActor)->playerWeapons_return0(), act::Unk_71002edaec(1));
}

void PlayerCutAfterJump::loadParams_() {}

void PlayerCutAfterJump::calc_() {
    PlayerAction::calc_();
}

bool PlayerCutAfterJump::isChangeable() const {
    return _1c;
}

}  // namespace uking::action
