#include "Game/AI/Action/actionPlayerGuardSlip.h"
#include "Game/AI/aiUnk_710072BA90.h"
#include "Game/Damage/dmgDamageManager.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"
#include <cstring>

namespace uking::action {

PlayerGuardSlip::PlayerGuardSlip(const InitArg& arg) : PlayerAction(arg) {
    std::memset(&mBaseInitSpeedNSword_s, 0, 0x80);
}

// NON_MATCHING: clang sinks the per-weapon parameter loads below the switch (the original keeps them in
// the four arms and compares the weapon type in the order 0, 1, 2)
void PlayerGuardSlip::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
    static_cast<ksys::act::Player*>(mActor)->_cec.set(0x8000000);
    static_cast<ksys::act::Player*>(mActor)->_cf4.set(0x4000000);
    if (!static_cast<ksys::act::Player*>(mActor)->isSurfingOnGround())
        static_cast<ksys::act::Player*>(mActor)->_cec.set(0x2);

    auto* player = static_cast<ksys::act::Player*>(mActor);
    if (!player->_c40.isOnBit(3) && player->sub_7100888294())
        static_cast<ksys::act::Player*>(mActor)->x_7();
    static_cast<ksys::act::Player*>(mActor)->_1800 = 0;

    f32 speed = 0.0f;
    if (auto* manager = sub_710072BA90(mActor)) {
        const s32 count = manager->getField48();
        f32 value;
        f32 limit;
        const f32* const* dec;
        switch (manager->getField50()) {
        case 0:
            value = *mBaseInitSpeedNSword_s + f32(count) * *mAddSpeedNSword_s;
            limit = *mMaxSpeedNSword_s;
            dec = &mDecSpeedNSword_s;
            break;
        case 1:
            value = *mBaseInitSpeedLSword_s + f32(count) * *mAddSpeedLSword_s;
            limit = *mMaxSpeedLSword_s;
            dec = &mDecSpeedLSword_s;
            break;
        case 2:
            value = *mBaseInitSpeedSpear_s + f32(count) * *mAddSpeedSpear_s;
            limit = *mMaxSpeedSpear_s;
            dec = &mDecSpeedSpear_s;
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
    player = static_cast<ksys::act::Player*>(mActor);
    player->_20bc.value = speed;
    player->_20bc.prev_value = speed;
    player = static_cast<ksys::act::Player*>(mActor);
    const u32 reversed = player->x_5().value ^ 0x80000000u;
    static_cast<ksys::act::Player*>(mActor)->_1c68.value = ksys::util::sUnk_7101EC6BA0 & reversed;
    static_cast<ksys::act::Player*>(mActor)->switchToAnimSequenceMaybe("GuardFailHit", true, -1.0f);
}

void PlayerGuardSlip::leave_() {}

void PlayerGuardSlip::loadParams_() {
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

void PlayerGuardSlip::calc_() {
    PlayerAction::calc_();
}

bool PlayerGuardSlip::isChangeable() const {
    return _1c;
}

}  // namespace uking::action
