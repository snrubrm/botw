#include "Game/AI/Action/actionPlayerWeaponThrow.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

PlayerWeaponThrow::PlayerWeaponThrow(const InitArg& arg) : PlayerAction(arg) {}

void PlayerWeaponThrow::enter_(ksys::act::ai::InlineParamPack* params) {
    const bool squat = static_cast<ksys::act::Player*>(mActor)->_cec.isOnBit(2);
    PlayerAction::enter_(params);
    static_cast<ksys::act::Player*>(mActor)->_cec.set(0x1);
    static_cast<ksys::act::Player*>(mActor)->_cf0.set(0x40000000);
    if (squat) {
        static_cast<ksys::act::Player*>(mActor)->switchToAnimSequenceMaybe("WeaponThrow", true,
                                                                           -1.0f);
        static_cast<ksys::act::Player*>(mActor)->_cec.set(0x4);
    } else if (static_cast<ksys::act::Player*>(mActor)->isSurfingOnGround()) {
        static_cast<ksys::act::Player*>(mActor)->switchToAnimSequenceMaybe("WeaponThrow", true,
                                                                           -1.0f);
    } else {
        static_cast<ksys::act::Player*>(mActor)->x_23("WeaponThrow", false, -1.0f);
        static_cast<ksys::act::Player*>(mActor)->_cec.set(0x2);
        return;
    }
    auto* player = static_cast<ksys::act::Player*>(mActor);
    player->_20bc = 0;
    player->_20c0 = 0;
}

void PlayerWeaponThrow::leave_() {
    static_cast<ksys::act::Player*>(mActor)->_c44.reset(0x100);
    if (mActor->getASList()->x_1(1, 1) == "WeaponThrow")
        static_cast<ksys::act::Player*>(mActor)->x_18(true);
}

void PlayerWeaponThrow::loadParams_() {
    getStaticParam(&mThrowSpeedY_s, "ThrowSpeedY");
    getStaticParam(&mThrowSpeedF_s, "ThrowSpeedF");
    getStaticParam(&mSquatThrowSpeedF_s, "SquatThrowSpeedF");
}

void PlayerWeaponThrow::calc_() {
    PlayerAction::calc_();
}

bool PlayerWeaponThrow::isChangeable() const {
    return false;
}

}  // namespace uking::action
