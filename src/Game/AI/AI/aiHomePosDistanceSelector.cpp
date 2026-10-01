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

// NON_MATCHING: load order of the actor position vs home position components
void HomePosDistanceSelector::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* actor = mActor;
    sead::Vector3f home_pos;
    actor->getHomePos(&home_pos);
    const f32 dx = home_pos.x - actor->getMtx().m[0][3];
    const f32 dz = home_pos.z - actor->getMtx().m[2][3];
    if (sead::Mathf::sqrt(dx * dx + dz * dz) < *mBoundaryDistance_s)
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
