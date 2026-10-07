#include "Game/AI/AI/aiDefWanderAI.h"
#include <math/seadMathCalcCommon.h>
#include <random/seadGlobalRandom.h>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/Physics/System/physNavMeshCharacter.h"

namespace uking::ai {

DefWanderAI::DefWanderAI(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

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

void DefWanderAI::calc_() {
    _6c.update();
    if (isCurrentChild("待機") && _6c.hasEnded(0.0f) &&
        (!*mCheckWaitIsChangable_s || getCurrentChild()->isChangeable())) {
        sub_7100E4CABC();
    }

    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        auto* nav = mActor->m45();
        if (ksys::act::isPreyOrSwarm(mActor) && nav && (nav->_2a4 & 0xffff) == 0x17) {
            if (*mMaxWaitTime_s < 0.0f) {
                _6c = ksys::Timer(-1.0f, -1.0f, 0.0f);
            } else {
                const f32 min = *mMinWaitTime_s;
                const f32 range = sead::Mathf::clampMin(*mMaxWaitTime_s - min, 0.0f);
                const f32 time =
                    min + sead::GlobalRandom::instance()->getF32Range(0.0f, range) + 0.5f;
                _6c = ksys::Timer(time, time);
            }
            changeChild("待機");
        } else if (isCurrentChild("移動") && getCurrentChild()->isFailed()) {
            sub_7100E4CC00();
        } else {
            sub_7100E4CABC();
        }
    }
}

void DefWanderAI::sub_7100E4CABC() {
    const int count = _78++;
    if (*mFinishChangeCount_s >= 0 && count >= *mFinishChangeCount_s)
        return;

    f32 rate = *mChangeWaitRate_s;
    if (isCurrentChild("待機"))
        rate = rate / 5.0f;

    if (sead::GlobalRandom::instance()->getF32() < rate) {
        if (*mMaxWaitTime_s < 0.0f) {
            _6c = ksys::Timer(-1.0f, -1.0f, 0.0f);
        } else {
            const f32 min = *mMinWaitTime_s;
            const f32 range = sead::Mathf::clampMin(*mMaxWaitTime_s - min, 0.0f);
            const f32 time = min + sead::GlobalRandom::instance()->getF32Range(0.0f, range) + 0.5f;
            _6c = ksys::Timer(time, time);
        }
        changeChild("待機");
    } else {
        sub_7100E4CC00();
    }
}

void DefWanderAI::sub_7100E4CC00() {
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(_60, "BasePos", -1);
    pack.addVec3(_60, "TargetPos", -1);
    changeChild("移動", &pack);
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
