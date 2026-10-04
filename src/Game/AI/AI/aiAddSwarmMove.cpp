#include "Game/AI/AI/aiAddSwarmMove.h"
#include <random/seadGlobalRandom.h>

namespace uking::ai {

AddSwarmMove::AddSwarmMove(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

// The original keeps the vtable store that a defaulted destructor drops (same form as upstream's
// GameDataFlagSelector::~GameDataFlagSelector() { ; }, commit 96101229).
AddSwarmMove::~AddSwarmMove() {
    ;
}

bool AddSwarmMove::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void AddSwarmMove::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

// NON_MATCHING: only the first four instructions: the original loads `mActor` (first argument), then stores the
// zero `flag`, then loads the SubSpeed pointer / value; ours stores `flag` first and loads `mActor` last
void AddSwarmMove::calc_() {
    s32 flag = 0;
    sead::Vector3f next;
    const bool ok = sub_7100729D18(mActor, &next, _88, *mSubSpeed_s, &flag, false);
    if (flag)
        _94.reset();
    else
        _94.update();

    if (_94.value <= 0.0f)
        _88 = sead::Vector3f::zero;
    else
        _88 = next;

    if (*mIsEndBySensor_s && _7c.value >= f32(*mIgnoreSensorTime_s)) {
        if (!ok)
            _78 = true;
    } else {
        _7c.update();
    }
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
