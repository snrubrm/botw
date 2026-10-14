#include "Game/Actor/Player/Action/actionPlayerCutAfterJump.h"
#include "Game/Actor/actWeapon.h"
#include "Game/Actor/aiUnk_71005D6D10.h"
#include "Game/gameUnk_710246d058.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActorWeapons.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/Resource/Actor/resResourceGParamList.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectPlayer.h"

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

// NON_MATCHING: stack slot of the controller position; mActor is loaded before the AS query branch.
void PlayerCutAfterJump::calc_() {
    static_cast<ksys::act::Player*>(mActor)->sub_7100893F1C();
    static_cast<ksys::act::Player*>(mActor)->sub_7100877BD8();
    if (auto* controller = mActor->getCharacterController()) {
        sead::Vector3f pos;
        if (controller->sub_7100F5F234(&pos))
            static_cast<ksys::act::Player*>(mActor)->_1810 = pos;
        static_cast<ksys::act::Player*>(mActor)->sub_7100881DFC(
            static_cast<ksys::act::Player*>(mActor)->_1810.y, false);
    }
    static_cast<ksys::act::Player*>(mActor)->actionCommon();
    m32();

    ksys::as::ASList::Unk4 query;
    if (mActor->getASList()->x(3, &query, 0, 0, &ksys::as::ASList::Unk2::sub_710116383C, true)) {
        static_cast<ksys::act::Player*>(mActor)->sub_7100892F5C(&query);
        const sead::BitFlag8 flags(0x10);
        auto* player = static_cast<ksys::act::Player*>(mActor);
        sub_71005D7F4C(player, player->playerWeapons_return0(), 0, &query.name, &flags, 1, 1.0f,
                       1.0f);
    } else if (mActor->getASList()->x(3, nullptr, 0, 0, &ksys::as::ASList::Unk2::sub_710116388C,
                                      true)) {
        auto* player = static_cast<ksys::act::Player*>(mActor);
        sub_71005D79AC(player, player->playerWeapons_return0(), act::Unk_71002edaec(1));
    }

    if (hasAttackInfo(mActor)) {
        auto* gparams = mActor->getParam()->getRes().mGParamList->getPlayer();
        static_cast<ksys::act::Player*>(mActor)->_1db8.reset(gparams->mHitSlowTimeS.ref() *
                                                              gparams->mHitSlowRate.ref());
        static_cast<ksys::act::Player*>(mActor)->_cf8.setBit(2);
    }

    if (static_cast<ksys::act::Player*>(mActor)->sub_71008737E4(0, 0))
        setFinished();
}

bool PlayerCutAfterJump::isChangeable() const {
    return _1c;
}

}  // namespace uking::action
