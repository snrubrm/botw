#include "Game/AI/Action/actionPlayerGrabThrow.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

PlayerGrabThrow::PlayerGrabThrow(const InitArg& arg) : PlayerAction(arg) {}

void PlayerGrabThrow::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
    static_cast<ksys::act::Player*>(mActor)->_cec.setBit(0);
    static_cast<ksys::act::Player*>(mActor)->_cec.setBit(5);
    static_cast<ksys::act::Player*>(mActor)->_cf0.setBit(30);
    static_cast<ksys::act::Player*>(mActor)->switchToAnimSequenceMaybe("GrabThrow", true, -1.0f);
    auto* player = static_cast<ksys::act::Player*>(mActor);
    player->_1800 = player->_20bc.value * 30.0f;
    if (auto* child = sead::DynamicCast<ksys::act::Actor>(mActor->getConnectedCalcChild()))
        sub_71005DC3F4(child);
}

void PlayerGrabThrow::leave_() {
    PlayerAction::leave_();
}

void PlayerGrabThrow::loadParams_() {
    getStaticParam(&mOverThrowSpeedYB_s, "OverThrowSpeedYB");
    getStaticParam(&mOverThrowSpeedFB_s, "OverThrowSpeedFB");
    getStaticParam(&mOverThrowSpeedYL_s, "OverThrowSpeedYL");
    getStaticParam(&mOverThrowSpeedFL_s, "OverThrowSpeedFL");
    getStaticParam(&mOverThrowInertiaRate_s, "OverThrowInertiaRate");
}

void PlayerGrabThrow::calc_() {
    PlayerAction::calc_();
}

bool PlayerGrabThrow::isChangeable() const {
    return _1c;
}

}  // namespace uking::action
