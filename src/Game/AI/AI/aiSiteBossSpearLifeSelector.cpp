#include "Game/AI/AI/aiSiteBossSpearLifeSelector.h"

namespace uking::ai {

SiteBossSpearLifeSelector::SiteBossSpearLifeSelector(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

SiteBossSpearLifeSelector::~SiteBossSpearLifeSelector() = default;

bool SiteBossSpearLifeSelector::init_(sead::Heap* heap) {
    _48 = 0;
    return true;
}

void SiteBossSpearLifeSelector::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void SiteBossSpearLifeSelector::leave_() {
    ksys::act::ai::Ai::leave_();
}

void SiteBossSpearLifeSelector::loadParams_() {
    getStaticParam(&mPatternChangeLife2_s, "PatternChangeLife2");
    getStaticParam(&mPatternChangeLife3_s, "PatternChangeLife3");
}

bool SiteBossSpearLifeSelector::isFailed() const {
    return getCurrentChild() && getCurrentChild()->isFailed();
}

bool SiteBossSpearLifeSelector::isFinished() const {
    return getCurrentChild() && getCurrentChild()->isFinished();
}

void SiteBossSpearLifeSelector::calc_() {
    if (getCurrentChild()) {
        if (getCurrentChild()->isFinished())
            setFinished();
        else if (getCurrentChild()->isFailed())
            setFailed();
    }
}

}  // namespace uking::ai
