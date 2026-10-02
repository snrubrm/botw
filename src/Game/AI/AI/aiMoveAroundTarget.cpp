#include "Game/AI/AI/aiMoveAroundTarget.h"
#include <math/seadMathCalcCommon.h>
#include <random/seadGlobalRandom.h>

namespace uking::ai {

MoveAroundTarget::MoveAroundTarget(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

MoveAroundTarget::~MoveAroundTarget() = default;

bool MoveAroundTarget::isChangeable() const {
    if (!ActionBase::isChangeable())
        return false;
    return ksys::act::ai::Ai::isChangeable();
}

bool MoveAroundTarget::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void MoveAroundTarget::enter_(ksys::act::ai::InlineParamPack* params) {
    _68 = ksys::Timer(-1, -1);
    _80 = ksys::Timer(*mStartRange_s, *mStartRange_s, *mChangeRangeRate_s);
    const s32 base = *mTurnTimeBase_s;
    const s32 end = base + *mTurnTimeRand_s;
    _90 = sead::Mathi::min(base, end);
    _94 = sead::Mathi::max(base, end);
    _8c = _90 == _94 ? _90 : sead::GlobalRandom::instance()->getS32Range(_90, _94);
    sub_71004B004C();
}

void MoveAroundTarget::leave_() {
    ksys::act::ai::Ai::leave_();
}

void MoveAroundTarget::loadParams_() {
    getStaticParam(&mTurnTimeBase_s, "TurnTimeBase");
    getStaticParam(&mTurnTimeRand_s, "TurnTimeRand");
    getStaticParam(&mStartRange_s, "StartRange");
    getStaticParam(&mEndRange_s, "EndRange");
    getStaticParam(&mChangeRangeRate_s, "ChangeRangeRate");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

}  // namespace uking::ai
