#include "Game/Actor/Action/actionForkBasicMessageDialogCtrl.h"

namespace uking::action {

ForkBasicMessageDialogCtrl::ForkBasicMessageDialogCtrl(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ForkBasicMessageDialogCtrl::~ForkBasicMessageDialogCtrl() = default;

bool ForkBasicMessageDialogCtrl::init_(sead::Heap* heap) {
    _28.acquire(heap, static_cast<Unk_71025afb58**>(mSimpleDialogUnit_a));
    return true;
}

void ForkBasicMessageDialogCtrl::enter_(ksys::act::ai::InlineParamPack* params) {
    mFlags.set(Flag::Changeable);
}

void ForkBasicMessageDialogCtrl::leave_() {
    ksys::act::ai::Action::leave_();
}

void ForkBasicMessageDialogCtrl::loadParams_() {
    getAITreeVariable(&mSimpleDialogUnit_a, "SimpleDialogUnit");
}

// NON_MATCHING: the original keeps the type check as a diamond that tail-calls with `obj + 8` or nullptr; ours selects the
// argument with one csel (an explicit `static_cast<Data*>(nullptr)->sub_7100721E80()` else-arm reproduces the original)
void ForkBasicMessageDialogCtrl::calc_() {
    _28.getData()->sub_7100721E80();
}

}  // namespace uking::action
