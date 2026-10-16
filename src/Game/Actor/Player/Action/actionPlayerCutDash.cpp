#include "Game/Actor/Player/Action/actionPlayerCutDash.h"
#include "Game/Actor/actWeapon.h"
#include "Game/Actor/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"
#include "Game/gameUnk_710246d058.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/Resource/Actor/resResourceGParamList.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectPlayer.h"

namespace uking::action {

PlayerCutDash::PlayerCutDash(const InitArg& arg) : PlayerAction(arg) {}

void PlayerCutDash::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerCutDash::leave_() {
    static_cast<ksys::act::Player*>(mActor)->_14c0 = false;
    sub_71005D79AC(mActor, static_cast<ksys::act::Player*>(mActor)->playerWeapons_return0(), act::Unk_71002edaec(1));
}

void PlayerCutDash::loadParams_() {
    getStaticParam(&mSearchAngle_s, "SearchAngle");
}

// NON_MATCHING: stack slots of the AS query and the controller position (as in PlayerCutAfterJump::calc_).
void PlayerCutDash::calc_() {
    static_cast<ksys::act::Player*>(mActor)->sub_7100893F1C();

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

    static_cast<ksys::act::Player*>(mActor)->sub_7100877BD8();
    if (hasAttackInfo(mActor)) {
        auto* gparams = mActor->getParam()->getRes().mGParamList->getPlayer();
        static_cast<ksys::act::Player*>(mActor)->_1db8.reset(gparams->mHitSlowTimeS.ref() *
                                                              gparams->mHitSlowRate.ref());
        static_cast<ksys::act::Player*>(mActor)->_cf8.setBit(2);
    }
    m32();

    if (auto* controller = mActor->getCharacterController()) {
        sead::Vector3f pos;
        if (controller->sub_7100F5F234(&pos))
            static_cast<ksys::act::Player*>(mActor)->_1810 = pos;
        static_cast<ksys::act::Player*>(mActor)->sub_7100881DFC(
            static_cast<ksys::act::Player*>(mActor)->_1810.y, false);
    }
    static_cast<ksys::act::Player*>(mActor)->actionCommon();
    if (static_cast<ksys::act::Player*>(mActor)->sub_71008737E4(0, 0))
        setFinished();
}

bool PlayerCutDash::isChangeable() const {
    return _1c;
}

}  // namespace uking::action
