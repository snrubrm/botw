#include "Game/AI/Action/actionPlayerKokkoGlide.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"

namespace uking::action {

PlayerKokkoGlide::PlayerKokkoGlide(const InitArg& arg) : PlayerGlide(arg) {}

void PlayerKokkoGlide::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerGlide::enter_(params);
}

void PlayerKokkoGlide::leave_() {
    PlayerGlide::leave_();
}

void PlayerKokkoGlide::loadParams_() {
    PlayerGlide::loadParams_();
    getStaticParam(&mEnergyGlide_s, "EnergyGlide");
    getStaticParam(&mNoEnergyTime_s, "NoEnergyTime");
}

void PlayerKokkoGlide::calc_() {
    PlayerGlide::calc_();
}

bool PlayerKokkoGlide::isChangeable() const {
    return true;
}

bool PlayerKokkoGlide::isFinished() const {
    return static_cast<ksys::act::Player*>(mActor)->isSurfingOnGround() || _98;
}

}  // namespace uking::action
