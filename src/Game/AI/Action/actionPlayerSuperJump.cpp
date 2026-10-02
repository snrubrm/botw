#include "Game/AI/Action/actionPlayerSuperJump.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actChemical.h"

namespace uking::action {

PlayerSuperJump::PlayerSuperJump(const InitArg& arg) : PlayerAction(arg) {}

void PlayerSuperJump::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerSuperJump::leave_() {
    auto* proc = static_cast<ksys::act::Player*>(mActor)->_2c28.getProc(nullptr, nullptr);
    if (auto* actor = sead::DynamicCast<ksys::act::Actor>(proc))
        actor->sleep(ksys::act::BaseProc::SleepWakeReason::_0);
    mActor->getChemicalStuff()->_14c = 1.0f;
}

void PlayerSuperJump::loadParams_() {
    getStaticParam(&mJumpHeight_s, "JumpHeight");
    getStaticParam(&mWindScale_s, "WindScale");
}

void PlayerSuperJump::calc_() {
    PlayerAction::calc_();
}

bool PlayerSuperJump::isChangeable() const {
    return false;
}

}  // namespace uking::action
