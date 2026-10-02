#include "Game/AI/Action/actionPlayerSuperBlow.h"
#include <math/seadMathCalcCommon.h>
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"

namespace uking::action {

PlayerSuperBlow::PlayerSuperBlow(const InitArg& arg) : PlayerAction(arg) {}

void PlayerSuperBlow::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerSuperBlow::leave_() {}

void PlayerSuperBlow::loadParams_() {
    getStaticParam(&mInitSpeed_s, "InitSpeed");
    getStaticParam(&mJumpHeight_s, "JumpHeight");
    getStaticParam(&mDecSpeed_s, "DecSpeed");
    getStaticParam(&mNoRagdollTime_s, "NoRagdollTime");
}

void PlayerSuperBlow::calc_() {
    auto* player = static_cast<ksys::act::Player*>(mActor);
    if (player->_1844.value <= sead::Mathf::epsilon())
        setFinished();
    else
        player->_1844.update();
    static_cast<ksys::act::Player*>(mActor)->_20bc.chase(0.0f, *mDecSpeed_s);
    static_cast<ksys::act::Player*>(mActor)->actionCommon();
}

bool PlayerSuperBlow::isChangeable() const {
    return false;
}

}  // namespace uking::action
