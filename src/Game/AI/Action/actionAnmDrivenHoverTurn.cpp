#include "Game/AI/Action/actionAnmDrivenHoverTurn.h"

namespace uking::action {

AnmDrivenHoverTurn::AnmDrivenHoverTurn(const InitArg& arg) : AnmDrivenHoverBase(arg) {}

// Empty-statement body as in upstream's GameDataFlagSelector::~GameDataFlagSelector() (96101229):
// the original keeps the vtable store that a defaulted destructor drops.
AnmDrivenHoverTurn::~AnmDrivenHoverTurn() {
    ;
}

bool AnmDrivenHoverTurn::init_(sead::Heap* heap) {
    return AnmDrivenHoverBase::init_(heap);
}

void AnmDrivenHoverTurn::enter_(ksys::act::ai::InlineParamPack* params) {
    AnmDrivenHoverBase::enter_(params);
}

void AnmDrivenHoverTurn::leave_() {
    AnmDrivenHoverBase::leave_();
}

void AnmDrivenHoverTurn::loadParams_() {
    AnmDrivenHoverBase::loadParams_();
    getStaticParam(&mRotSpeed_s, "RotSpeed");
    getStaticParam(&mBaseRotRatio_s, "BaseRotRatio");
    getStaticParam(&mRotAccRatio_s, "RotAccRatio");
    getStaticParam(&mFinRotate_s, "FinRotate");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

void AnmDrivenHoverTurn::calc_() {
    AnmDrivenHoverBase::calc_();
}

}  // namespace uking::action
