#include "Game/AI/Action/actionPlayerLandDamage.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

PlayerLandDamage::PlayerLandDamage(const InitArg& arg) : PlayerAction(arg) {}

void PlayerLandDamage::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerLandDamage::leave_() {}

void PlayerLandDamage::loadParams_() {
    getStaticParam(&mWaitTimeMin_s, "WaitTimeMin");
    getStaticParam(&mWaitTimeMax_s, "WaitTimeMax");
    getStaticParam(&mDeadHeight_s, "DeadHeight");
    getStaticParam(&mDamageMin_s, "DamageMin");
}

void PlayerLandDamage::calc_() {
    if (mActor->getASList()->x_1(0, 0) == "LandDamageStand") {
        m32();
    } else if (mActor->getASList()->x_4(0, 0)) {
        auto* player = static_cast<ksys::act::Player*>(mActor);
        if (player->_1844.value <= sead::Mathf::epsilon())
            player->switchToAnimSequenceMaybe("LandDamageStand", true, -1.0f);
        else
            player->_1844.update();
    }
}

bool PlayerLandDamage::isChangeable() const {
    return true;
}

}  // namespace uking::action
