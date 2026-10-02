#include "Game/AI/Action/actionPlayerStoleOpen.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

PlayerStoleOpen::PlayerStoleOpen(const InitArg& arg) : PlayerStoleOpenEx(arg) {}

void PlayerStoleOpen::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerStoleOpenBase::enter_(params);
    _e0 = 0;
    mActor->setScale(sead::Vector3f::zero);
    _38._98 = 0;
}

void PlayerStoleOpen::loadParams_() {
    PlayerStoleOpenBase::loadParams_();
    getStaticParam(&mEnlargeSpd_s, "EnlargeSpd");
}

void PlayerStoleOpen::calc_() {
    PlayerStoleOpenEx::calc_();
}

}  // namespace uking::action
