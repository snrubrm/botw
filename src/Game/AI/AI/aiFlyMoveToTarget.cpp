#include "Game/AI/AI/aiFlyMoveToTarget.h"

namespace uking::ai {

FlyMoveToTarget::FlyMoveToTarget(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

FlyMoveToTarget::~FlyMoveToTarget() = default;

bool FlyMoveToTarget::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

// NON_MATCHING: the original loads the target position before the clearing stores
void FlyMoveToTarget::enter_(ksys::act::ai::InlineParamPack* params) {
    _b4 = 0;
    _60.clear();
    _a4 = false;
    _a8 = 0;
    _ac = 0;
    _98.set(mTargetPos_d->x, mTargetPos_d->y + *mOffsetHeight_s, mTargetPos_d->z);
    _b0 = 1.0f;
    sub_71003D4414();
}

void FlyMoveToTarget::leave_() {
    ksys::act::ai::Ai::leave_();
}

void FlyMoveToTarget::loadParams_() {
    getStaticParam(&mMoveFailCount_s, "MoveFailCount");
    getStaticParam(&mFarDist_s, "FarDist");
    getStaticParam(&mOutDist_s, "OutDist");
    getStaticParam(&mOffsetHeight_s, "OffsetHeight");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

}  // namespace uking::ai
