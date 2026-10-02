#include "Game/AI/Action/actionSearch.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/System/Timer.h"

namespace uking::action {

Search::Search(const InitArg& arg) : ActionWithAS(arg) {}

Search::~Search() = default;

void Search::enter_(ksys::act::ai::InlineParamPack* params) {
    playAS("Search", false, 0, 0, -1.0f);
    mActor->getASList()->x_6(9, 0, mActor->getAngVelocity().y);
    ActionWithAS::enter_(params);
    _38 = *mNoChangeTime_s;
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
