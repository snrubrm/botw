#include "Game/AI/Action/actionPlayerSwimWait.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"

namespace uking::action {

PlayerSwimWait::PlayerSwimWait(const InitArg& arg) : PlayerAction(arg) {}

void PlayerSwimWait::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
    static_cast<ksys::act::Player*>(mActor)->_cec.setBit(10);
    static_cast<ksys::act::Player*>(mActor)->_cec.setBit(4);
    static_cast<ksys::act::Player*>(mActor)->_cf0.setBit(9);
    static_cast<ksys::act::Player*>(mActor)->_cf4.setBit(7);
    auto* player = static_cast<ksys::act::Player*>(mActor);
    sead::Vector3f dir;
    player->_1b6c.getBase(dir, 2);
    dir.normalize();
    static_cast<ksys::act::Player*>(mActor)->_1c68 =
        ksys::util::Unk_7101EC6BAC(sead::Mathf::atan2Idx(dir.x, dir.z));
    static_cast<ksys::act::Player*>(mActor)->switchToAnimSequenceMaybe("SwimWait", true, -1.0f);
}

void PlayerSwimWait::leave_() {}

void PlayerSwimWait::loadParams_() {
    getStaticParam(&mEnergyWait_s, "EnergyWait");
    getStaticParam(&mDecSpeedRate_s, "DecSpeedRate");
}

void PlayerSwimWait::calc_() {
    PlayerAction::calc_();
}

bool PlayerSwimWait::isChangeable() const {
    return true;
}

bool PlayerSwimWait::isFinished() const {
    return static_cast<ksys::act::Player*>(mActor)->_209c > 0.05f;
}

}  // namespace uking::action
