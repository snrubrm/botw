#include "Game/AI/AI/aiGolemRWeakPointRoot.h"

namespace uking::ai {

GolemRWeakPointRoot::GolemRWeakPointRoot(const InitArg& arg) : GolemWeakPointRoot(arg) {}

GolemRWeakPointRoot::~GolemRWeakPointRoot() = default;

bool GolemRWeakPointRoot::init_(sead::Heap* heap) {
    return GolemWeakPointRoot::init_(heap);
}

void GolemRWeakPointRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    GolemWeakPointRoot::enter_(params);
}

void GolemRWeakPointRoot::calc_() {
    GolemWeakPointRoot::calc_();
}

bool GolemRWeakPointRoot::handleMessage_(const ksys::Message& message) {
    if (_220.m2(message))
        return true;
    return GolemWeakPointRoot::handleMessage_(message);
}

bool GolemRWeakPointRoot::m36() {
    return true;
}

void GolemRWeakPointRoot::m37() {}

void GolemRWeakPointRoot::m38(s32 idx, const sead::Matrix34f& mtx) {}

void GolemRWeakPointRoot::leave_() {
    GolemWeakPointRoot::leave_();
}

void GolemRWeakPointRoot::loadParams_() {
    GolemWeakPointRoot::loadParams_();
}

}  // namespace uking::ai
