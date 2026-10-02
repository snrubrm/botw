#include "Game/AI/Action/actionPlayerBeamMove.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"

namespace uking::action {

PlayerBeamMove::PlayerBeamMove(const InitArg& arg) : WindCutter(arg) {}

PlayerBeamMove::~PlayerBeamMove() = default;

void PlayerBeamMove::enter_(ksys::act::ai::InlineParamPack* params) {
    WindCutter::enter_(params);
}

void PlayerBeamMove::leave_() {
    WindCutter::leave_();
}

void PlayerBeamMove::loadParams_() {
    WindCutter::loadParams_();
}

bool PlayerBeamMove::m33() {
    if (WindCutter::m33())
        return true;
    return hasAttackInfo(mActor);
}

}  // namespace uking::action
