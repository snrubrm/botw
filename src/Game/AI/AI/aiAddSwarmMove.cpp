#include "Game/AI/AI/aiAddSwarmMove.h"

namespace uking::ai {

AddSwarmMove::AddSwarmMove(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

// The SafeString member makes the original keep the vtable store (see AssassinCallSelect).
AddSwarmMove::~AddSwarmMove() { ; }

bool AddSwarmMove::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void AddSwarmMove::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

bool AddSwarmMove::isFinished() const {
    return ksys::act::ai::Ai::isFinished() || getCurrentChild()->isFinished();
}

void AddSwarmMove::leave_() {
    ksys::act::ai::Ai::leave_();
}

void AddSwarmMove::loadParams_() {
    getStaticParam(&mIgnoreSensorTime_s, "IgnoreSensorTime");
    getStaticParam(&mSubSpeed_s, "SubSpeed");
    getStaticParam(&mSubAccRateMin_s, "SubAccRateMin");
    getStaticParam(&mSubAccRateMax_s, "SubAccRateMax");
    getStaticParam(&mIsEndBySensor_s, "IsEndBySensor");
    getStaticParam(&mAnimName_s, "AnimName");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

bool AddSwarmMove::isFailed() const {
    if (_78 || ActionBase::isFailed())
        return true;
    return getCurrentChild()->isFailed();
}

}  // namespace uking::ai
