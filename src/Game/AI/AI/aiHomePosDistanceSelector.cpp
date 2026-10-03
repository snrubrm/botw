#include "Game/AI/AI/aiHomePosDistanceSelector.h"
#include <math/seadMathCalcCommon.h>
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

HomePosDistanceSelector::HomePosDistanceSelector(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

HomePosDistanceSelector::~HomePosDistanceSelector() = default;

bool HomePosDistanceSelector::isFailed() const {
    return getCurrentChild()->isFailed();
}

bool HomePosDistanceSelector::isFinished() const {
    return getCurrentChild()->isFinished();
}

bool HomePosDistanceSelector::isChangeable() const {
    return getCurrentChild()->isChangeable();
}

bool HomePosDistanceSelector::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void HomePosDistanceSelector::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* actor = mActor;
    sead::Vector3f home_pos;
    actor->getHomePos(&home_pos);
    const sead::Vector3f diff = home_pos - actor->getMtx().getTranslation();
    if (sead::Mathf::sqrt(diff.x * diff.x + diff.z * diff.z) < *mBoundaryDistance_s)
        changeChild("レンジ内", params);
    else
        changeChild("レンジ外", params);
}

void HomePosDistanceSelector::calc_() {}

void HomePosDistanceSelector::leave_() {
    ksys::act::ai::Ai::leave_();
}

void HomePosDistanceSelector::loadParams_() {
    getStaticParam(&mBoundaryDistance_s, "BoundaryDistance");
}

}  // namespace uking::ai
