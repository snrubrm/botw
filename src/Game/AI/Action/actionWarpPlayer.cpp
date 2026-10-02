#include "Game/AI/Action/actionWarpPlayer.h"

namespace uking::action {

WarpPlayer::WarpPlayer(const InitArg& arg) : WarpPlayerBase(arg) {}

// Empty-statement body as in upstream's GameDataFlagSelector::~GameDataFlagSelector() (96101229):
// the original keeps the vtable store that a defaulted destructor drops.
WarpPlayer::~WarpPlayer() {
    ;
}

bool WarpPlayer::init_(sead::Heap* heap) {
    return WarpPlayerBase::init_(heap);
}

void WarpPlayer::enter_(ksys::act::ai::InlineParamPack* params) {
    WarpPlayerBase::enter_(params);
}

void WarpPlayer::leave_() {
    WarpPlayerBase::leave_();
}

void WarpPlayer::loadParams_() {
    WarpPlayerBase::loadParams_();
    getDynamicParam(&mWarpDestMapName_d, "WarpDestMapName");
    getDynamicParam(&mWarpDestPosName_d, "WarpDestPosName");
}

void WarpPlayer::calc_() {
    WarpPlayerBase::calc_();
}

bool WarpPlayer::m33() {
    return true;
}

}  // namespace uking::action
