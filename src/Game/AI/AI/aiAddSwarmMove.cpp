#include "Game/AI/AI/aiAddSwarmMove.h"
#include "Game/Actor/actSwarm.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
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

// NON_MATCHING: the compiler combines the fixed random-timer bounds into a wider store.
void AddSwarmMove::enter_(ksys::act::ai::InlineParamPack* params) {
    _78 = false;
    auto* swarm = sead::DynamicCast<act::Swarm>(mActor);
    if (!swarm || *mSubAccRateMin_s > *mSubAccRateMax_s) {
        setFailed();
        return;
    }

    _88 = sead::Vector3f::zero;
    _94.value = 5.0f;
    _94.min = 5;
    _94.max = 5;
    for (s32 i = 0; i < swarm->_14c8.size(); ++i) {
        if (auto* unit = swarm->_14c8[i]) {
            const f32 min = *mSubAccRateMin_s;
            const f32 max = *mSubAccRateMax_s;
            unit->_5c = sead::GlobalRandom::instance()->getF32Range(min, max);
        }
    }
    _7c = ksys::Timer(0.0f, 0.0f, 1.0f);
    swarm->sub_71002D47D4(mAnimName_s);

    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(*mTargetPos_d, "TargetPos", -1);
    changeChild("移動", &pack);
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
