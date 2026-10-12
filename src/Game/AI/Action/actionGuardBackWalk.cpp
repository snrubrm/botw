#include "Game/AI/Action/actionGuardBackWalk.h"

namespace uking::action {

GuardBackWalk::GuardBackWalk(const InitArg& arg) : NormalBackWalk(arg) {}

bool GuardBackWalk::init_(sead::Heap* heap) {
    return NormalBackWalk::init_(heap);
}

void GuardBackWalk::enter_(ksys::act::ai::InlineParamPack* params) {
    NormalBackWalk::enter_(params);
    playAS("GuardBackWalk", false, 0, 0, -1.0f);
}

void GuardBackWalk::leave_() {
    NormalBackWalk::leave_();
}

void GuardBackWalk::loadParams_() {
    NormalBackWalk::loadParams_();
}

void GuardBackWalk::calc_() {
    NormalBackWalk::calc_();
}

}  // namespace uking::action
