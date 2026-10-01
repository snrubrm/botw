#include "Game/AI/AI/aiAssassinMiddleMagicAfter.h"

namespace uking::ai {

AssassinMiddleMagicAfter::AssassinMiddleMagicAfter(const InitArg& arg)
    : AssassinMagicTgtSelect(arg) {}

AssassinMiddleMagicAfter::~AssassinMiddleMagicAfter() = default;

bool AssassinMiddleMagicAfter::init_(sead::Heap* heap) {
    return AssassinMagicTgtSelect::init_(heap);
}

void AssassinMiddleMagicAfter::enter_(ksys::act::ai::InlineParamPack* params) {
    if (*mIsInterseptAttack_a)
        changeChild("一度やられた");
    else
        AssassinMagicTgtSelect::enter_(params);
    _48 = false;
}

void AssassinMiddleMagicAfter::calc_() {
    AssassinMagicTgtSelect::calc_();
    if (isFinished() || isFailed())
        _48 = true;
}

void AssassinMiddleMagicAfter::leave_() {
    if (!_48)
        *mIsInterseptAttack_a = true;
    AssassinMagicTgtSelect::leave_();
}

void AssassinMiddleMagicAfter::loadParams_() {
    AssassinMagicTgtSelect::loadParams_();
    getAITreeVariable(&mIsInterseptAttack_a, "IsInterseptAttack");
}

}  // namespace uking::ai
