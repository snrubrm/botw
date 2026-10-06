#include "Game/AI/Action/actionAnimalFollow.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "Game/AI/aiUnk_71005D6D10.h"
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

ksys::act::BaseProcLink* AnimalFollow::m33() {
    if (auto* link = sub_71005D9050(mActor))
        return link;
    return &ksys::act::sUnk_71026505e0;
}

}  // namespace uking::action
