#include "Game/AI/Action/actionCapturedActFreeze.h"

namespace uking::action {

CapturedActFreeze::CapturedActFreeze(const InitArg& arg) : Freeze(arg) {}

// Empty-statement body as in upstream's GameDataFlagSelector::~GameDataFlagSelector() (96101229):
// the original keeps the vtable store that a defaulted destructor drops.
CapturedActFreeze::~CapturedActFreeze() {
    ;
}

bool CapturedActFreeze::init_(sead::Heap* heap) {
    return Freeze::init_(heap);
}

void CapturedActFreeze::enter_(ksys::act::ai::InlineParamPack* params) {
    Freeze::enter_(params);
}

void CapturedActFreeze::leave_() {
    Freeze::leave_();
}

void CapturedActFreeze::loadParams_() {
    Freeze::loadParams_();
    getStaticParam(&mPauseDelayFrames_s, "PauseDelayFrames");
    getStaticParam(&mASKeyName_s, "ASKeyName");
}

void CapturedActFreeze::calc_() {
    Freeze::calc_();
}

}  // namespace uking::action
