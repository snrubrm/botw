#include "Game/Actor/Action/actionPlayerStoleOpen.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

PlayerStoleOpen::PlayerStoleOpen(const InitArg& arg) : BindPlayerNodeEx(arg) {}

void PlayerStoleOpen::enter_(ksys::act::ai::InlineParamPack* params) {
    BindPlayerNodeBase::enter_(params);
    _e0 = 0;
    mActor->setScale(sead::Vector3f::zero);
    _38._98 = 0;
}

void PlayerStoleOpen::loadParams_() {
    BindPlayerNodeBase::loadParams_();
    getStaticParam(&mEnlargeSpd_s, "EnlargeSpd");
}

void PlayerStoleOpen::calc_() {
    BindPlayerNodeEx::calc_();
}

}  // namespace uking::action
