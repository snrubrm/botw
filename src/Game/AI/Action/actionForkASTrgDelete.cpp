#include "Game/AI/Action/actionForkASTrgDelete.h"

namespace uking::action {

ForkASTrgDelete::ForkASTrgDelete(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ForkASTrgDelete::~ForkASTrgDelete() = default;

bool ForkASTrgDelete::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ForkASTrgDelete::enter_(ksys::act::ai::InlineParamPack* params) {
    mFlags.set(Flag::Changeable);
}

void ForkASTrgDelete::leave_() {
    ksys::act::ai::Action::leave_();
}

void ForkASTrgDelete::loadParams_() {}

void ForkASTrgDelete::calc_() {
    ksys::act::ai::Action::calc_();
}

void ForkASTrgDelete::m32() {}

}  // namespace uking::action
