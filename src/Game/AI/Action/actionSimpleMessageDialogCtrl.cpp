#include "Game/AI/Action/actionSimpleMessageDialogCtrl.h"

namespace uking::action {

SimpleMessageDialogCtrl::SimpleMessageDialogCtrl(const InitArg& arg) : ksys::act::ai::Action(arg) {}

SimpleMessageDialogCtrl::~SimpleMessageDialogCtrl() = default;

bool SimpleMessageDialogCtrl::init_(sead::Heap* heap) {
    _28.acquire(heap, static_cast<Unk_71025afb58**>(mSimpleDialogUnit_a));
    return true;
}

void SimpleMessageDialogCtrl::enter_(ksys::act::ai::InlineParamPack* params) {
    mFlags.set(Flag::Changeable);
}

void SimpleMessageDialogCtrl::leave_() {
    ksys::act::ai::Action::leave_();
}

void SimpleMessageDialogCtrl::loadParams_() {
    getAITreeVariable(&mSimpleDialogUnit_a, "SimpleDialogUnit");
}

// NON_MATCHING: the original keeps the type check as a diamond that tail-calls with `obj + 8` or nullptr; ours selects the
// argument with one csel (an explicit `static_cast<Data*>(nullptr)->sub_7100721E80()` else-arm reproduces the original)
void SimpleMessageDialogCtrl::calc_() {
    _28.getData()->sub_7100721E80();
}

}  // namespace uking::action
