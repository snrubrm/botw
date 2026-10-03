#include "Game/AI/Action/actionPlayerLandDamage.h"
#include "Game/AI/aiUnk_7101E7C2B4.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

PlayerLandDamage::PlayerLandDamage(const InitArg& arg) : PlayerAction(arg) {}

void PlayerLandDamage::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
    static_cast<ksys::act::Player*>(mActor)->_cec.setBit(0);
    static_cast<ksys::act::Player*>(mActor)->_cec.setBit(31);
    auto* player = static_cast<ksys::act::Player*>(mActor);
    player->_20bc.value = 0;
    player->_20bc.prev_value = 0;
    static_cast<ksys::act::Player*>(mActor)->actionCommon();
    static_cast<ksys::act::Player*>(mActor)->_c50.setBit(0);
    static_cast<ksys::act::Player*>(mActor)->switchToAnimSequenceMaybe("LandDamage", true, -1.0f);
    player = static_cast<ksys::act::Player*>(mActor);
    const f32 rate = sead::Mathf::clampMax((player->_20d0 - player->_1770.y - uking::sUnk_7101e7c2b4) /
                                          (sUnk_7101e7c2b8 - uking::sUnk_7101e7c2b4),
                                      1.0f);
    const f32 time = *mWaitTimeMin_s + rate * (*mWaitTimeMax_s - *mWaitTimeMin_s);
    player->_1844 = ksys::Timer(time, time);
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
