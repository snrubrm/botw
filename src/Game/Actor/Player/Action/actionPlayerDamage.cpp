#include "Game/Actor/Player/Action/actionPlayerDamage.h"
#include <cstring>
#include "Game/Actor/Damage/dmgDamageManager.h"
#include "Game/Actor/aiUnk_710072BA90.h"
#include "Game/gameRumble.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"
#include "Game/gameUnk_71008ba8d8.h"

namespace uking::action {

PlayerDamage::PlayerDamage(const InitArg& arg) : PlayerAction(arg) {
    std::memset(&mBaseInitSpeedNSword_s, 0, 0x80);
}

// NON_MATCHING: same as PlayerGuardSlip::enter_ (per-weapon parameter loads sunk below the switch).
void PlayerDamage::enter_(ksys::act::ai::InlineParamPack* params) {
    if (static_cast<ksys::act::Player*>(mActor)->_cec.isOnBit(19)) {
        sead::Matrix34f mtx;
        if (auto* controller = mActor->getCharacterController())
            controller->physicsXXXGetMtx_1(&mtx);
        static_cast<ksys::act::Player*>(mActor)->_1b18 = mtx;
    }
    PlayerAction::enter_(params);
    static_cast<ksys::act::Player*>(mActor)->_cec.set(0x80000000);
    static_cast<ksys::act::Player*>(mActor)->_cf0.set(0x80);
    static_cast<ksys::act::Player*>(mActor)->_c50.setBit(13);
    if (!static_cast<ksys::act::Player*>(mActor)->stillAlive())
        static_cast<ksys::act::Player*>(mActor)->_cf0.set(0x100);
    static_cast<ksys::act::Player*>(mActor)->_1800 = 0;

    f32 speed = 0.0f;
    if (auto* manager = sub_710072BA90(mActor)) {
        const s32 count = manager->getField48();
        f32 value;
        f32 limit;
        const f32* const* dec;
        switch (manager->getField50()) {
        case 2:
            value = *mBaseInitSpeedSpear_s + f32(count) * *mAddSpeedSpear_s;
            limit = *mMaxSpeedSpear_s;
            dec = &mDecSpeedSpear_s;
            break;
        case 1:
            value = *mBaseInitSpeedLSword_s + f32(count) * *mAddSpeedLSword_s;
            limit = *mMaxSpeedLSword_s;
            dec = &mDecSpeedLSword_s;
            break;
        case 0:
            value = *mBaseInitSpeedNSword_s + f32(count) * *mAddSpeedNSword_s;
            limit = *mMaxSpeedNSword_s;
            dec = &mDecSpeedNSword_s;
            break;
        default:
            value = *mBaseInitSpeedOther_s + f32(count) * *mAddSpeedOther_s;
            limit = *mMaxSpeedOther_s;
            dec = &mDecSpeedOther_s;
            break;
        }
        speed = value > limit ? limit : value;
        static_cast<ksys::act::Player*>(mActor)->_1800 = **dec;
    }

    static_cast<ksys::act::Player*>(mActor)->_20c8 = speed;
    auto* player = static_cast<ksys::act::Player*>(mActor);
    player->_20bc.value = speed;
    player->_20bc.prev_value = speed;
    static_cast<ksys::act::Player*>(mActor)->sub_7100884FCC();
    static_cast<ksys::act::Player*>(mActor)->switchToAnimSequenceMaybe("DamageS", true, -1.0f);
    Rumble::instance()->sub_7100897FE4(0, 1);
}

void PlayerDamage::leave_() {
    auto* player = static_cast<ksys::act::Player*>(mActor);
    player->_20bc.value = 0;
    player->_20bc.prev_value = 0;
}

void PlayerDamage::loadParams_() {
    getStaticParam(&mBaseInitSpeedNSword_s, "BaseInitSpeedNSword");
    getStaticParam(&mBaseInitSpeedLSword_s, "BaseInitSpeedLSword");
    getStaticParam(&mBaseInitSpeedSpear_s, "BaseInitSpeedSpear");
    getStaticParam(&mBaseInitSpeedOther_s, "BaseInitSpeedOther");
    getStaticParam(&mAddSpeedNSword_s, "AddSpeedNSword");
    getStaticParam(&mAddSpeedLSword_s, "AddSpeedLSword");
    getStaticParam(&mAddSpeedSpear_s, "AddSpeedSpear");
    getStaticParam(&mAddSpeedOther_s, "AddSpeedOther");
    getStaticParam(&mMaxSpeedNSword_s, "MaxSpeedNSword");
    getStaticParam(&mMaxSpeedLSword_s, "MaxSpeedLSword");
    getStaticParam(&mMaxSpeedSpear_s, "MaxSpeedSpear");
    getStaticParam(&mMaxSpeedOther_s, "MaxSpeedOther");
    getStaticParam(&mDecSpeedNSword_s, "DecSpeedNSword");
    getStaticParam(&mDecSpeedLSword_s, "DecSpeedLSword");
    getStaticParam(&mDecSpeedSpear_s, "DecSpeedSpear");
    getStaticParam(&mDecSpeedOther_s, "DecSpeedOther");
}

void PlayerDamage::calc_() {
    if (!static_cast<ksys::act::Player*>(mActor)->stillAlive())
        callPlayerGameOverDemo(mActor);
    static_cast<ksys::act::Player*>(mActor)->_20bc.chase(0.0f,
                                                         static_cast<ksys::act::Player*>(mActor)->_1800);
    m32();
    static_cast<ksys::act::Player*>(mActor)->actionCommon();
}

bool PlayerDamage::isChangeable() const {
    return _1c;
}

}  // namespace uking::action
