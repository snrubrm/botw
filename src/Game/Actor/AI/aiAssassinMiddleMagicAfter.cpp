#include "Game/Actor/AI/aiAssassinMiddleMagicAfter.h"

namespace uking::ai {

AssassinMiddleMagicAfter::AssassinMiddleMagicAfter(const InitArg& arg)
    : TargetHeightAreaSelect(arg) {}

AssassinMiddleMagicAfter::~AssassinMiddleMagicAfter() = default;

bool AssassinMiddleMagicAfter::init_(sead::Heap* heap) {
    return TargetHeightAreaSelect::init_(heap);
}

void AssassinMiddleMagicAfter::enter_(ksys::act::ai::InlineParamPack* params) {
    if (*mIsInterseptAttack_a)
        changeChild("一度やられた");
    else
        TargetHeightAreaSelect::enter_(params);
    _48 = false;
}

void AssassinMiddleMagicAfter::calc_() {
    TargetHeightAreaSelect::calc_();
    if (isFinished() || isFailed())
        _48 = true;
}

void AssassinMiddleMagicAfter::leave_() {
    if (!_48)
        *mIsInterseptAttack_a = true;
    TargetHeightAreaSelect::leave_();
}

void AssassinMiddleMagicAfter::loadParams_() {
    TargetHeightAreaSelect::loadParams_();
    getAITreeVariable(&mIsInterseptAttack_a, "IsInterseptAttack");
}

}  // namespace uking::ai
