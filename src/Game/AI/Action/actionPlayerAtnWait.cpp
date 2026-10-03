#include "Game/AI/Action/actionPlayerAtnWait.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"

namespace uking::action {

PlayerAtnWait::PlayerAtnWait(const InitArg& arg) : PlayerAction(arg) {}

void PlayerAtnWait::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
    static_cast<ksys::act::Player*>(mActor)->_cec.set(0x1);
    static_cast<ksys::act::Player*>(mActor)->_cec.set(0x8000000);
    static_cast<ksys::act::Player*>(mActor)->_cec.set(0x10000000);
    static_cast<ksys::act::Player*>(mActor)->_cf0.set(0x4);
    static_cast<ksys::act::Player*>(mActor)->_cf0.set(0x80);
    static_cast<ksys::act::Player*>(mActor)->_cf4.set(0x10);
    static_cast<ksys::act::Player*>(mActor)->_cf0.set(0x200);
    static_cast<ksys::act::Player*>(mActor)->_cf4.set(0x20);
    static_cast<ksys::act::Player*>(mActor)->_cf4.set(0x400000);
    static_cast<ksys::act::Player*>(mActor)->_cf4.set(0x2000);
    static_cast<ksys::act::Player*>(mActor)->_cf4.set(0x4000);
    static_cast<ksys::act::Player*>(mActor)->_17f2 = false;
    static_cast<ksys::act::Player*>(mActor)->_1810 = sead::Vector3f(0.0f, 1.0f, 0.0f);
}

// NON_MATCHING: the original does not fold &mActor into a pre-indexed load
void PlayerAtnWait::leave_() {
    if (mActor->getASList()->x_1(1, 1) == "WaitAttentionUpper")
        static_cast<ksys::act::Player*>(mActor)->x_18(true);
    static_cast<ksys::act::Player*>(mActor)->x_19(-1.0f);
}

void PlayerAtnWait::loadParams_() {
    getStaticParam(&mAtnTurnDiffAng_s, "AtnTurnDiffAng");
}

void PlayerAtnWait::calc_() {
    PlayerAction::calc_();
}

bool PlayerAtnWait::isChangeable() const {
    return true;
}

}  // namespace uking::action
