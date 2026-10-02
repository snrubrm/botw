#include "Game/AI/Action/actionPlayerFall.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"

namespace uking::action {

PlayerFall::PlayerFall(const InitArg& arg) : PlayerAction(arg) {}

void PlayerFall::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerFall::leave_() {
    static_cast<ksys::act::Player*>(mActor)->_c44.reset(0x2000000);
    if (static_cast<ksys::act::Player*>(mActor)->m194()) {
        auto* player = static_cast<ksys::act::Player*>(mActor);
        auto* proc = player->_2c28.getProc(nullptr, nullptr);
        if (auto* actor = sead::DynamicCast<ksys::act::Actor>(proc))
            actor->sleep(ksys::act::BaseProc::SleepWakeReason::_0);
    }
}

void PlayerFall::loadParams_() {
    getStaticParam(&mNoClimbTime_s, "NoClimbTime");
    getStaticParam(&mNoClimbTimeTired_s, "NoClimbTimeTired");
    getStaticParam(&mNoDispDisableAppTime_s, "NoDispDisableAppTime");
}

void PlayerFall::calc_() {
    PlayerAction::calc_();
}

bool PlayerFall::isChangeable() const {
    return true;
}

bool PlayerFall::isFinished() const {
    return static_cast<ksys::act::Player*>(mActor)->isSurfingOnGround() || ActionBase::isFinished();
}

}  // namespace uking::action
