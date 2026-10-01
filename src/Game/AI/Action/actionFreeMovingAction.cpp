#include "Game/AI/Action/actionFreeMovingAction.h"

namespace uking::action {

FreeMovingAction::FreeMovingAction(const InitArg& arg) : ksys::act::ai::Action(arg) {}

FreeMovingAction::~FreeMovingAction() = default;

bool FreeMovingAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void FreeMovingAction::enter_(ksys::act::ai::InlineParamPack* params) {
    _1c.sub_710072AFFC(mActor);
}

// NON_MATCHING: regalloc (this+0x1c is built in x8 and moved to x0)
void FreeMovingAction::leave_() {
    _1c.sub_710072B078(mActor);
}

void FreeMovingAction::loadParams_() {}

void FreeMovingAction::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
