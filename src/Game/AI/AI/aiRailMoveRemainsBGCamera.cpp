#include "Game/AI/AI/aiRailMoveRemainsBGCamera.h"

namespace uking::ai {

RailMoveRemainsBGCamera::RailMoveRemainsBGCamera(const InitArg& arg) : RailMoveRemains(arg) {}

// The original keeps the vtable store that a defaulted destructor drops (same form as upstream's
// GameDataFlagSelector::~GameDataFlagSelector() { ; }, commit 96101229).
RailMoveRemainsBGCamera::~RailMoveRemainsBGCamera() {
    ;
}

bool RailMoveRemainsBGCamera::init_(sead::Heap* heap) {
    return RailMoveRemains::init_(heap);
}

void RailMoveRemainsBGCamera::enter_(ksys::act::ai::InlineParamPack* params) {
    RailMoveRemains::enter_(params);
}

void RailMoveRemainsBGCamera::calc_() {
    RailMoveRemains::calc_();
}

void RailMoveRemainsBGCamera::leave_() {
    RailMoveRemains::leave_();
}

void RailMoveRemainsBGCamera::loadParams_() {
    RailMoveRemains::loadParams_();
    getStaticParam(&mIsAllowRotAxisX_s, "IsAllowRotAxisX");
    getStaticParam(&mDungeonName_s, "DungeonName");
    getStaticParam(&mRailName_s, "RailName");
}

Unk_71024f15c0* RailMoveRemainsBGCamera::m45() {
    return &_a8;
}

}  // namespace uking::ai
