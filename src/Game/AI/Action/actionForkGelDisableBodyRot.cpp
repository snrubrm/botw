#include "Game/AI/Action/actionForkGelDisableBodyRot.h"
#include "Game/Actor/actGelEnemy.h"

namespace uking::action {

ForkGelDisableBodyRot::ForkGelDisableBodyRot(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ForkGelDisableBodyRot::~ForkGelDisableBodyRot() = default;

bool ForkGelDisableBodyRot::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ForkGelDisableBodyRot::enter_(ksys::act::ai::InlineParamPack* params) {
    mFlags.set(Flag::Changeable);
    if (auto* gel = sead::DynamicCast<uking::act::GelEnemy>(mActor))
        gel->_1678 |= 1;
}

void ForkGelDisableBodyRot::leave_() {
    if (auto* gel = sead::DynamicCast<uking::act::GelEnemy>(mActor))
        gel->_1678 &= ~1;
}

void ForkGelDisableBodyRot::loadParams_() {}

void ForkGelDisableBodyRot::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
