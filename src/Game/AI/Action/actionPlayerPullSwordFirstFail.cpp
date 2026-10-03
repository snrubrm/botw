#include "Game/AI/Action/actionPlayerPullSwordFirstFail.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"
#include "KingSystem/ActorSystem/AS/ASList.h"

namespace uking::action {

PlayerPullSwordFirstFail::PlayerPullSwordFirstFail(const InitArg& arg) : PlayerAction(arg) {}

void PlayerPullSwordFirstFail::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
    static_cast<ksys::act::Player*>(mActor)->_cf4.set(0x80);
    auto* player = static_cast<ksys::act::Player*>(mActor);
    player->_20bc.value = 0;
    player->_20bc.prev_value = 0;
    static_cast<ksys::act::Player*>(mActor)->actionCommon();
    auto& timer = static_cast<ksys::act::Player*>(mActor)->_1844;
    timer = ksys::Timer(*mFirstFailureWait_s, *mFirstFailureWait_s);
}

void PlayerPullSwordFirstFail::leave_() {
    mActor->getASList()->sub_710115C11C();
}

void PlayerPullSwordFirstFail::loadParams_() {
    getStaticParam(&mFirstFailureWait_s, "FirstFailureWait");
}

void PlayerPullSwordFirstFail::calc_() {
    if (!(static_cast<ksys::act::Player*>(mActor)->_1844.value <= sead::Mathf::epsilon()))
        static_cast<ksys::act::Player*>(mActor)->_1844.update();

    if (mActor->getASList()->x_1(0, 0) == "Demo300_0-C02-Link-A-0") {
        if (mActor->getASList()->x_4(0, 0))
            setFailed();
    } else if (static_cast<ksys::act::Player*>(mActor)->_1844.value <= sead::Mathf::epsilon()) {
        mActor->getASList()->sub_710115BC28("Demo300_0-C02-Link-A-0", -1.0f);
    }
}

bool PlayerPullSwordFirstFail::isChangeable() const {
    return false;
}

}  // namespace uking::action
