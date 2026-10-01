#include "Game/AI/Action/actionSearch.h"
#include "KingSystem/System/Timer.h"

namespace uking::action {

Search::Search(const InitArg& arg) : ActionWithAS(arg) {}

Search::~Search() = default;

void Search::enter_(ksys::act::ai::InlineParamPack* params) {
    ActionWithAS::enter_(params);
}

void Search::loadParams_() {
    ActionWithPosAngReduce::loadParams_();
    getStaticParam(&mNoChangeTime_s, "NoChangeTime");
}

void Search::calc_() {
    ActionWithAS::calc_();
    if (_38 <= 0.0f) {
        mFlags.set(Flag::Changeable);
        return;
    }
    ksys::Timer::update(&_38, -1.0f);
}

}  // namespace uking::action
