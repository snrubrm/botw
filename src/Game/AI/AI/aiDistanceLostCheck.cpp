#include "Game/AI/AI/aiDistanceLostCheck.h"
#include <random/seadGlobalRandom.h>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/System/Timer.h"

namespace uking::ai {

DistanceLostCheck::DistanceLostCheck(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

DistanceLostCheck::~DistanceLostCheck() = default;

bool DistanceLostCheck::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void DistanceLostCheck::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

bool DistanceLostCheck::isFailed() const {
    return ksys::act::ai::Ai::isFailed() || getCurrentChild()->isFailed();
}

bool DistanceLostCheck::isFinished() const {
    return getCurrentChild()->isFinished();
}

bool DistanceLostCheck::isChangeable() const {
    return getCurrentChild()->isChangeable();
}

// NON_MATCHING: the original keeps &_5c in a callee-saved register; regalloc
void DistanceLostCheck::calc_() {
    if (m34())
        ksys::Timer::update(&_5c, -1.0f);
    else
        _5c = _60 == _64 ? _60 : sead::GlobalRandom::instance()->getS32Range(_60, _64);

    auto* child = getCurrentChild();
    if (child->isChangeable() && _5c <= 0.0f)
        setFailed();
    child->setDynamicParam(*mTargetPos_d, "TargetPos");
}

void DistanceLostCheck::leave_() {
    ksys::act::ai::Ai::leave_();
}

void DistanceLostCheck::loadParams_() {
    getStaticParam(&mLostTimer_s, "LostTimer");
    getStaticParam(&mAddAwarenessRangeType_s, "AddAwarenessRangeType");
    getStaticParam(&mLostRange_s, "LostRange");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

// NON_MATCHING: regalloc (the original squares the range into s1)
bool DistanceLostCheck::sub_7100362928() {
    sead::Vector3f pos;
    mActor->getMtx().getTranslation(pos);
    return (pos - *mTargetPos_d).squaredLength() > sead::Mathf::square(*mLostRange_s + _58);
}

}  // namespace uking::ai
