#include "Game/AI/Action/actionDragonFollow.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

DragonFollow::DragonFollow(const InitArg& arg) : FollowChallenge(arg) {}

DragonFollow::~DragonFollow() = default;

bool DragonFollow::init_(sead::Heap* heap) {
    if (!FollowChallenge::init_(heap))
        return false;
    sub_710004E2B4(false);
    sub_71000F4798();
    return true;
}

void DragonFollow::enter_(ksys::act::ai::InlineParamPack* params) {
    FollowChallenge::enter_(params);
}

void DragonFollow::leave_() {
    FollowChallenge::leave_();
    mActor->sub_71011DA834(&mBindInfo);
}

void DragonFollow::loadParams_() {
    FollowChallenge::loadParams_();
    getStaticParam(&mDungeonName_s, "DungeonName");
}

void DragonFollow::calc_() {
    FollowChallenge::calc_();
}

}  // namespace uking::action
