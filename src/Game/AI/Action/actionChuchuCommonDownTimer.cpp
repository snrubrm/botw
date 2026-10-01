#include "Game/AI/Action/actionChuchuCommonDownTimer.h"
#include "KingSystem/System/Timer.h"
#include <math/seadMathCalcCommon.h>

namespace uking::action {

ChuchuCommonDownTimer::ChuchuCommonDownTimer(const InitArg& arg) : Fork(arg) {}

ChuchuCommonDownTimer::~ChuchuCommonDownTimer() = default;

bool ChuchuCommonDownTimer::init_(sead::Heap* heap) {
    return Fork::init_(heap);
}

void ChuchuCommonDownTimer::enter_(ksys::act::ai::InlineParamPack* params) {
    Fork::enter_(params);
    _40 = sead::Mathi::max(*mMinWaitFrame_s, *mChemicalChuchuCommonDownTime_a);
}

void ChuchuCommonDownTimer::leave_() {
    *mChemicalChuchuCommonDownTime_a = _40;
    Fork::leave_();
}

void ChuchuCommonDownTimer::loadParams_() {
    Fork::loadParams_();
    getStaticParam(&mMinWaitFrame_s, "MinWaitFrame");
    getAITreeVariable(&mChemicalChuchuCommonDownTime_a, "ChemicalChuchuCommonDownTime");
}

void ChuchuCommonDownTimer::calc_() {
    Fork::calc_();
    if (_40 > 0.0f) {
        ksys::Timer::update(&_40, -1.0f);
        if (_40 <= 0.0f)
            setEndState();
    }
}

}  // namespace uking::action
