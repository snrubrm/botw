#include "Game/AI/AI/aiFishSafeReturn.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

FishSafeReturn::FishSafeReturn(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

FishSafeReturn::~FishSafeReturn() = default;

bool FishSafeReturn::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void FishSafeReturn::enter_(ksys::act::ai::InlineParamPack* params) {
    _60.set(*mTargetPos_d);
    changeToMove();
}

void FishSafeReturn::leave_() {
    ksys::act::ai::Ai::leave_();
}

void FishSafeReturn::loadParams_() {
    getStaticParam(&mInWaterDepth_s, "InWaterDepth");
    getStaticParam(&mDivePercent_s, "DivePercent");
    getStaticParam(&mAllowReturnThreatDist_s, "AllowReturnThreatDist");
    getDynamicParam(&mIsEscape_d, "IsEscape");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

void FishSafeReturn::changeToMove() {
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(_60, "TargetPos", -1);
    pack.addVec3(_60, "MoveAwayFromPos", -1);
    changeChild("移動", &pack);
}

bool FishSafeReturn::isChangeable() const {
    return isCurrentChild("移動") || isCurrentChild("逃走");
}

}  // namespace uking::ai
