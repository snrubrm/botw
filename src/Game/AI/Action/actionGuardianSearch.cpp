#include "Game/AI/Action/actionGuardianSearch.h"

namespace uking::action {

GuardianSearch::GuardianSearch(const InitArg& arg) : GuardianMoveTo(arg) {}

GuardianSearch::~GuardianSearch() = default;

bool GuardianSearch::init_(sead::Heap* heap) {
    return GuardianMoveTo::init_(heap);
}

// NON_MATCHING: the original keeps `state == _14d8` and the `*mLost_s` test as two separate compares (cmp + ccmp);
// ours folds the second into the first.
void GuardianSearch::enter_(ksys::act::ai::InlineParamPack* params) {
    GuardianMoveTo::enter_(params);
    playAS("Wait", true, 0, 0, -1.0f);
    _28 = *mWaitFrame_s;
    mFlags.set(Flag::Changeable);
    if (auto* guardian = sub_7100192824()) {
        const s32 state = *mLost_s ? 6 : 1;
        guardian->sub_7100035A90(guardian->_14d8 == state && *mLost_s ? 7 : state);
    }
}

void GuardianSearch::leave_() {
    GuardianMoveTo::leave_();
}

void GuardianSearch::loadParams_() {
    GuardianMoveTo::loadParams_();
    getStaticParam(&mWaitFrame_s, "WaitFrame");
    getStaticParam(&mLost_s, "Lost");
}

void GuardianSearch::calc_() {
    GuardianMoveTo::calc_();
    ksys::Timer::update(&_28, -1.0f);
    if (_28 <= 0.0f)
        setFinished();
}

}  // namespace uking::action
