#include "Game/AI/AI/aiSeqRandomRepeat.h"
#include <random/seadGlobalRandom.h>

namespace uking::ai {

SeqRandomRepeat::SeqRandomRepeat(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

SeqRandomRepeat::~SeqRandomRepeat() = default;

bool SeqRandomRepeat::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void SeqRandomRepeat::enter_(ksys::act::ai::InlineParamPack* params) {
    if (*mMaxActionNum_s < 1) {
        _50 = 0;
    } else {
        const int min = *mMinActionNum_s;
        _50 = sead::GlobalRandom::instance()->getS32Range(min, *mMaxActionNum_s + 1);
    }
    changeChild("行動", params);
}

void SeqRandomRepeat::calc_() {
    auto* child = getCurrentChild();
    if (!child->isFinished() && !child->isFailed())
        return;

    if (--_50 <= 0) {
        if (*mMaxActionNum_s <= 0) {
            _50 = 0;
        } else {
            setFinished();
            return;
        }
    }
    changeChild("行動");
}

void SeqRandomRepeat::leave_() {
    ksys::act::ai::Ai::leave_();
}

void SeqRandomRepeat::loadParams_() {
    getStaticParam(&mMinActionNum_s, "MinActionNum");
    getStaticParam(&mMaxActionNum_s, "MaxActionNum");
    getStaticParam(&mIsEndChangeable_s, "IsEndChangeable");
}

bool SeqRandomRepeat::isFinished() const {
    return ksys::act::ai::Ai::isFinished() ||
           (*mMaxActionNum_s >= 1 && getCurrentChild()->isFinished() && _50 < 2);
}

bool SeqRandomRepeat::isChangeable() const {
    auto* child = getCurrentChild();
    return child->isChangeable() ||
           (*mIsEndChangeable_s && (child->isFinished() || child->isFailed()));
}

}  // namespace uking::ai
