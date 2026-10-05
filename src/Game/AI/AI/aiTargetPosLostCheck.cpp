#include "Game/AI/AI/aiTargetPosLostCheck.h"
#include <math/seadMathCalcCommon.h>
#include <random/seadGlobalRandom.h>
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/System/Timer.h"

// Declaration only; original source namespace is unknown.
bool sub_7100730BB8(ksys::act::Actor* actor, f32 range, f32 min, f32 max);

namespace uking::ai {

TargetPosLostCheck::TargetPosLostCheck(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

TargetPosLostCheck::~TargetPosLostCheck() = default;

bool TargetPosLostCheck::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void TargetPosLostCheck::enter_(ksys::act::ai::InlineParamPack* params) {
    const int time_a = *mLostTimer_s;
    const int time_b = *mLostTimer_s * 1.1f;
    _64 = sead::Mathi::min(time_a, time_b);
    _68 = sead::Mathi::max(time_a, time_b);
    s32 time = _64;
    if (_68 != _64)
        time = sead::GlobalRandom::instance()->getS32Range(_64, _68);
    _60 = time;

    ksys::act::ai::InlineParamPack params_;
    params_.addVec3(*mTargetPos_d, "TargetPos", -1);
    changeChild("発見行動", &params_);
}

// NON_MATCHING: the compiler recomputes the timer address and allocates saved values differently.
void TargetPosLostCheck::calc_() {
    if (sub_7100730BB8(mActor, *mLostRange_s, *mLostVMin_s, *mLostVMax_s)) {
        ksys::Timer::update(&_60, -1.0f);
    } else {
        s32 time = _64;
        const s32 max = _68;
        if (max != time)
            time = sead::GlobalRandom::instance()->getS32Range(time, max);
        _60 = time;
    }

    auto* child = getCurrentChild();
    if (child->isChangeable() && _60 <= 0.0f)
        setFailed();
    child->setDynamicParam(*mTargetPos_d, "TargetPos");
}

void TargetPosLostCheck::leave_() {
    ksys::act::ai::Ai::leave_();
}

void TargetPosLostCheck::loadParams_() {
    getStaticParam(&mLostTimer_s, "LostTimer");
    getStaticParam(&mLostVMin_s, "LostVMin");
    getStaticParam(&mLostVMax_s, "LostVMax");
    getStaticParam(&mLostRange_s, "LostRange");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

bool TargetPosLostCheck::isFailed() const {
    return ksys::act::ai::Ai::isFailed() || getCurrentChild()->isFailed();
}

}  // namespace uking::ai
