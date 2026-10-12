#include "Game/AI/Action/actionHorseFollow.h"
#include "Game/Actor/actRideable.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

HorseFollow::HorseFollow(const InitArg& arg) : HorseFollowBase(arg) {}

HorseFollow::~HorseFollow() = default;

bool HorseFollow::init_(sead::Heap* heap) {
    return HorseFollowBase::init_(heap);
}

void HorseFollow::enter_(ksys::act::ai::InlineParamPack* params) {
    HorseFollowBase::enter_(params);
    if (auto* rideable = mActor->getHorseOptionsMaybe())
        rideable->RideableBase::_8 &= ~0x200000;
}

void HorseFollow::leave_() {
    HorseFollowBase::leave_();
    if (auto* rideable = mActor->getHorseOptionsMaybe())
        rideable->RideableBase::_8 &= ~0x200000;
}

void HorseFollow::loadParams_() {
    HorseFollowBase::loadParams_();
    getDynamicParam(&mDistanceKept_d, "DistanceKept");
    getDynamicParam(&mTargetActor_d, "TargetActor");
}

void HorseFollow::calc_() {
    HorseFollowBase::calc_();
}

float HorseFollow::m32() {
    return *mDistanceKept_d;
}

void HorseFollow::m34(const s32* value) {
    if (auto* rideable = mActor->getHorseOptionsMaybe()) {
        if (*value == 0)
            rideable->RideableBase::_8.setBitOn(21);
        else
            rideable->RideableBase::_8.setBitOff(21);
    }
}

}  // namespace uking::action
