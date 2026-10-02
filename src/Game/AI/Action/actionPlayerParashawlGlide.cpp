#include "Game/AI/Action/actionPlayerParashawlGlide.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"

namespace uking::action {

PlayerParashawlGlide::PlayerParashawlGlide(const InitArg& arg) : PlayerGlide(arg) {}

void PlayerParashawlGlide::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerGlide::enter_(params);
}

void PlayerParashawlGlide::leave_() {
    PlayerGlide::leave_();
}

void PlayerParashawlGlide::loadParams_() {
    PlayerGlide::loadParams_();
    getStaticParam(&mEnergyGlide_s, "EnergyGlide");
    getStaticParam(&mNoEnergyTime_s, "NoEnergyTime");
}

void PlayerParashawlGlide::calc_() {
    PlayerGlide::calc_();
}

bool PlayerParashawlGlide::isChangeable() const {
    return _1c;
}

bool PlayerParashawlGlide::isFinished() const {
    return static_cast<ksys::act::Player*>(mActor)->isSurfingOnGround() || _a0;
}

}  // namespace uking::action
