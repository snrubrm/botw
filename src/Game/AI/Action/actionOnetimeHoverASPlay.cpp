#include "Game/AI/Action/actionOnetimeHoverASPlay.h"

namespace uking::action {

OnetimeHoverASPlay::OnetimeHoverASPlay(const InitArg& arg) : HoverBase(arg) {}

// Empty-statement body as in upstream's GameDataFlagSelector::~GameDataFlagSelector() (96101229):
// the original keeps the vtable store that a defaulted destructor drops.
OnetimeHoverASPlay::~OnetimeHoverASPlay() {
    ;
}

bool OnetimeHoverASPlay::init_(sead::Heap* heap) {
    return HoverBase::init_(heap);
}

void OnetimeHoverASPlay::enter_(ksys::act::ai::InlineParamPack* params) {
    HoverBase::enter_(params);
    playAS(mASName_s.cstr(), true, 0, 0, -1.0f);
    mFlags.reset(Flag::Changeable);
}

void OnetimeHoverASPlay::leave_() {
    HoverBase::leave_();
}

void OnetimeHoverASPlay::loadParams_() {
    HoverBase::loadParams_();
    getStaticParam(&mIsIgnoreSameAS_s, "IsIgnoreSameAS");
    getStaticParam(&mASName_s, "ASName");
}

void OnetimeHoverASPlay::calc_() {
    HoverBase::calc_();
    if (isFinishedAS(0, 0))
        setFinished();
}

bool OnetimeHoverASPlay::isFinished() const {
    return isFinishedAS(0, 0);
}

}  // namespace uking::action
