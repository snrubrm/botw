#include "Game/AI/Action/actionAnimalFollow.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "Game/Actor/actRideable.h"

namespace uking::action {

AnimalFollow::AnimalFollow(const InitArg& arg) : AnimalFollowBase(arg) {}

AnimalFollow::~AnimalFollow() = default;

bool AnimalFollow::init_(sead::Heap* heap) {
    return AnimalFollowBase::init_(heap);
}

void AnimalFollow::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* rideable = mActor->m132();
    if (!rideable) {
        setFailed();
        return;
    }
    rideable->_18.sub_7100E770C4(false);
    AnimalFollowBase::enter_(params);
}

void AnimalFollow::leave_() {
    AnimalFollowBase::leave_();
}

void AnimalFollow::loadParams_() {
    AnimalFollowBase::loadParams_();
    getStaticParam(&mDistanceKept_s, "DistanceKept");
}

void AnimalFollow::calc_() {
    AnimalFollowBase::calc_();
}

float AnimalFollow::m32() {
    return *mDistanceKept_s;
}

}  // namespace uking::action
