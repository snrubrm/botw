#include "Game/AI/Action/actionPlayerLaunch.h"
#include "Game/gameUnk_71008ba8d8.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"

namespace uking::action {

PlayerLaunch::PlayerLaunch(const InitArg& arg) : PlayerAction(arg) {}

void PlayerLaunch::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerLaunch::leave_() {}

void PlayerLaunch::loadParams_() {
    getStaticParam(&mInitSpeed_s, "InitSpeed");
    getStaticParam(&mJumpHeight_s, "JumpHeight");
    getStaticParam(&mAddLinearImpulse_s, "AddLinearImpulse");
    getStaticParam(&mAddRollImpulse_s, "AddRollImpulse");
    getStaticParam(&mNoRagdollTime_s, "NoRagdollTime");
    getStaticParam(&mDamage_s, "Damage");
    getDynamicParam(&mBasePos_d, "BasePos");
}

void PlayerLaunch::calc_() {
    if (!static_cast<ksys::act::Player*>(mActor)->stillAlive())
        callPlayerGameOverDemo(mActor);
    auto* player = static_cast<ksys::act::Player*>(mActor);
    if (player->_1844.value <= sead::Mathf::epsilon()) {
        if (player->getASList()->x(35, nullptr, 0, 0, &ksys::as::ASList::Unk2::sub_71011638DC,
                                   true)) {
            setFinished();
        }
    } else {
        player->_1844.update();
    }
    static_cast<ksys::act::Player*>(mActor)->actionCommon();
}

bool PlayerLaunch::isChangeable() const {
    return false;
}

}  // namespace uking::action
