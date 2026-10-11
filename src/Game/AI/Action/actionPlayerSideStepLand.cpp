#include "Game/AI/Action/actionPlayerSideStepLand.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"
#include "KingSystem/ActorSystem/Attention/actAttentionSingleton.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "Game/gameUnk_710246d058.h"

namespace uking::action {

PlayerSideStepLand::PlayerSideStepLand(const InitArg& arg) : PlayerAction(arg) {}

void PlayerSideStepLand::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
    static_cast<ksys::act::Player*>(mActor)->_cec.set(0x10000000);
    static_cast<ksys::act::Player*>(mActor)->_cec.set(0x1);
    static_cast<ksys::act::Player*>(mActor)->_cec.set(0x8000000);
    static_cast<ksys::act::Player*>(mActor)->_cf0.set(0x4);
    static_cast<ksys::act::Player*>(mActor)->_cf4.set(0x1000000);

    auto* player = static_cast<ksys::act::Player*>(mActor);
    if (player->_c40.isOnBit(8)) {
        player->_cf0.set(0x2000000);
        static_cast<ksys::act::Player*>(mActor)->_cf4.set(0x10000000);
        player = static_cast<ksys::act::Player*>(mActor);
    }
    if (player->_c98.isOnBit(17)) {
        player->_c4c.set(0x4);
        player = static_cast<ksys::act::Player*>(mActor);
    }
    if (player->_c44.isOnBit(8) && !player->_d11)
        player->switchToAnimSequenceMaybe("StepLandLower", true, -1.0f);
    else
        player->switchToAnimSequenceMaybe("StepLand", true, -1.0f);

    player = static_cast<ksys::act::Player*>(mActor);
    player->_17f1 = player->_d1c > 1;
    player = static_cast<ksys::act::Player*>(mActor);
    player->_c50.set(0x1);
    player = static_cast<ksys::act::Player*>(mActor);
    player->_20bc.value = 0;
    player->_20bc.prev_value = 0;
    static_cast<ksys::act::Player*>(mActor)->_1c68 = static_cast<ksys::act::Player*>(mActor)->x_5();
    static_cast<ksys::act::Player*>(mActor)->_17f0 = 0;
    static_cast<ksys::act::Player*>(mActor)->_211c = 0;

    player = static_cast<ksys::act::Player*>(mActor);
    if (player->_c40.isOnBit(9))
        player->_1d70 = ksys::Timer(9999.0f, 9999.0f);
}

void PlayerSideStepLand::leave_() {
    static_cast<ksys::act::Player*>(mActor)->_1d70 = ksys::Timer(0, 0);
}

// NON_MATCHING: accessor and angle temporaries use different stack slots; angle-add loads
// are scheduled differently.
void PlayerSideStepLand::calc_() {
    auto* player = static_cast<ksys::act::Player*>(mActor);
    if (player->_c40.isOnBit(9)) {
        player->_1cb0 = 78;
        ksys::act::Attention::instance()->sub_7100D744B8(
            static_cast<ksys::act::Player*>(mActor)->get1280());
        player = static_cast<ksys::act::Player*>(mActor);
    }
    if (player->_d10 && player->_17f1) {
        sead::Vector3f target = sead::Vector3f::zero;
        if (!ksys::act::Attention::instance()->sub_7100D742E8(1)) {
            ksys::act::ActorLinkConstDataAccess accessor;
            if (ksys::act::Attention::instance()->x_0(1, 0, &accessor))
                target = accessor.getActorMtx().getTranslation();
        }
        player = static_cast<ksys::act::Player*>(mActor);
        const f32 angle = sead::Mathf::atan2(target.x - player->_1770.x,
                                           target.z - player->_1770.z);
        static_cast<ksys::act::Player*>(mActor)->x_53(
            ksys::act::Player::Unk1(sead::Mathf::rad2idx(angle)));
        const auto current = static_cast<ksys::act::Player*>(mActor)->x_5();
        player = static_cast<ksys::act::Player*>(mActor);
        player->_1c68.value = ksys::util::sUnk_7101EC6BA0 & (player->_1834.value + current.value);
        player = static_cast<ksys::act::Player*>(mActor);
    }
    if (!player->_c40.isOnBit(8)) {
        player->sub_71008931C4();
        static_cast<ksys::act::Player*>(mActor)->sub_71008893B8(false);
        player = static_cast<ksys::act::Player*>(mActor);
    }
    if (player->_c44.isOnBit(8) && !player->_d11) {
        player->x_37();
        player = static_cast<ksys::act::Player*>(mActor);
    }
    if (player->m179()) {
        static_cast<ksys::act::Player*>(mActor)->sub_71008824AC(false);
        if (ksys::act::playerIsReloadingOrChargingOrShootingBow(
                static_cast<ksys::act::Player*>(mActor)))
            static_cast<ksys::act::Player*>(mActor)->x_37();
    }
    static_cast<ksys::act::Player*>(mActor)->actionCommon();
    if (static_cast<ksys::act::Player*>(mActor)->_17d0->controllerCheckPressedMaybe(2))
        static_cast<ksys::act::Player*>(mActor)->_17f0 = 1;
    if (mActor->getASList()->x_4(0, 0)) {
        setFinished();
    } else {
        const bool landed = mActor->getASList()->x(
            2, nullptr, 0, 0, &ksys::as::ASList::Unk2::sub_710116383C, true);
        player = static_cast<ksys::act::Player*>(mActor);
        if (landed) {
            if (player->_c40.isOnBit(8) || player->_c40.isOnBit(9)) {
                setFailed();
                return;
            }
            _1c = true;
        }
        player->sub_71008B5B8();
    }
}

bool PlayerSideStepLand::isChangeable() const {
    return _1c;
}

}  // namespace uking::action
