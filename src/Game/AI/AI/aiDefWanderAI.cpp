#include "Game/AI/AI/aiDefWanderAI.h"
#include <math/seadMathCalcCommon.h>
#include <random/seadGlobalRandom.h>
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

DefWanderAI::DefWanderAI(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

DefWanderAI::~DefWanderAI() = default;

void DefWanderAI::enter_(ksys::act::ai::InlineParamPack* params) {
    mActor->getMtx().getTranslation(_60);
    if (*mMaxWaitTime_s < 0.0f) {
        _6c = ksys::Timer(-1.0f, -1.0f, 0.0f);
    } else {
        const f32 min = *mMinWaitTime_s;
        const f32 range = sead::Mathf::clampMin(*mMaxWaitTime_s - min, 0.0f);
        const f32 time = min + sead::GlobalRandom::instance()->getF32Range(0.0f, range) + 0.5f;
        _6c = ksys::Timer(time, time);
    }
    changeChild("待機");
    _78 = 0;
}

bool DefWanderAI::isFinished() const {
    const int count = *mFinishChangeCount_s;
    if (count < 0)
        return false;
    return _78 > count;
}

bool DefWanderAI::isChangeable() const {
    return getCurrentChild()->isChangeable();
}

void DefWanderAI::loadParams_() {
    getStaticParam(&mFinishChangeCount_s, "FinishChangeCount");
    getStaticParam(&mChangeWaitRate_s, "ChangeWaitRate");
    getStaticParam(&mMaxWaitTime_s, "MaxWaitTime");
    getStaticParam(&mMinWaitTime_s, "MinWaitTime");
    getStaticParam(&mCheckWaitIsChangable_s, "CheckWaitIsChangable");
}

}  // namespace uking::ai
