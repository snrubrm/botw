#include "Game/AI/Action/actionAnimalPlayASAndKeepOnGround.h"

namespace uking::action {

AnimalPlayASAndKeepOnGround::AnimalPlayASAndKeepOnGround(const InitArg& arg)
    : PlayASForAnimalUnit(arg) {}

AnimalPlayASAndKeepOnGround::~AnimalPlayASAndKeepOnGround() = default;

bool AnimalPlayASAndKeepOnGround::init_(sead::Heap* heap) {
    return PlayASForAnimalUnit::init_(heap);
}

void AnimalPlayASAndKeepOnGround::enter_(ksys::act::ai::InlineParamPack* params) {
    *mIsChangeableStateFreeFall_a = false;
    PlayASForAnimalUnit::enter_(params);
    _78.reset(15.0f);
}

void AnimalPlayASAndKeepOnGround::leave_() {
    *mIsChangeableStateFreeFall_a = true;
    PlayASForAnimalUnit::leave_();
}

void AnimalPlayASAndKeepOnGround::loadParams_() {
    PlayASForAnimalUnit::loadParams_();
    getStaticParam(&mDownImpulseScale_s, "DownImpulseScale");
    getStaticParam(&mIsUseDownImpulse_s, "IsUseDownImpulse");
    getAITreeVariable(&mIsChangeableStateFreeFall_a, "IsChangeableStateFreeFall");
}

void AnimalPlayASAndKeepOnGround::calc_() {
    PlayASForAnimalUnit::calc_();
}

}  // namespace uking::action
