#include "Game/AI/Action/actionAnimalMove.h"
#include "Game/AI/aiUnk_71007320F0.h"

namespace uking::action {

AnimalMove::AnimalMove(const InitArg& arg) : AnimalMoveBase(arg) {}

AnimalMove::~AnimalMove() = default;

bool AnimalMove::init_(sead::Heap* heap) {
    return AnimalMoveBase::init_(heap);
}

void AnimalMove::enter_(ksys::act::ai::InlineParamPack* params) {
    AnimalMoveBase::enter_(params);
}

void AnimalMove::leave_() {
    AnimalMoveBase::leave_();
}

void AnimalMove::loadParams_() {
    AnimalMoveBase::loadParams_();
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mFinRadius_s, "FinRadius");
}

void AnimalMove::calc_() {
    AnimalMoveBase::calc_();
}

bool AnimalMove::m33(float x) {
    return *mFinRadius_s + sub_71007320F0(mActor, *mWeaponIdx_s) >= x;
}

}  // namespace uking::action
