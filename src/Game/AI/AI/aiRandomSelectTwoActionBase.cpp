#include "Game/AI/AI/aiRandomSelectTwoActionBase.h"
#include <random/seadGlobalRandom.h>

namespace uking::ai {

RandomSelectTwoActionBase::RandomSelectTwoActionBase(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

RandomSelectTwoActionBase::~RandomSelectTwoActionBase() = default;

bool RandomSelectTwoActionBase::isFailed() const {
    return mFlags.isOn(Flag::Failed) || getCurrentChild()->isFailed();
}

bool RandomSelectTwoActionBase::isFinished() const {
    return mFlags.isOn(Flag::Finished) || getCurrentChild()->isFinished();
}

bool RandomSelectTwoActionBase::init_(sead::Heap* heap) {
    _48 = 0;
    return true;
}

void RandomSelectTwoActionBase::enter_(ksys::act::ai::InlineParamPack* params) {
    const s32 rand = sead::GlobalRandom::instance()->getU32(100);
    s32 rate = m34();
    if (_48 > 0)
        rate -= *mCorrectRateToB_s * _48;
    else if (_48 < 0)
        rate -= *mCorrectRateToA_s * _48;

    if (rand < sead::Mathi::clamp(rate, 0, 100))
        m35(params);
    else
        m36(params);
}

void RandomSelectTwoActionBase::calc_() {
    if (getCurrentChild()->isFinished())
        setFinished();
    else if (getCurrentChild()->isFailed())
        setFailed();
}

void RandomSelectTwoActionBase::leave_() {
    ksys::act::ai::Ai::leave_();
}

void RandomSelectTwoActionBase::loadParams_() {
    getStaticParam(&mCorrectRateToA_s, "CorrectRateToA");
    getStaticParam(&mCorrectRateToB_s, "CorrectRateToB");
}

void RandomSelectTwoActionBase::m35(ksys::act::ai::InlineParamPack* params) {
    _48 = _48 < 1 ? 1 : _48 + 1;
    changeChild("行動Ａ", params);
}

void RandomSelectTwoActionBase::m36(ksys::act::ai::InlineParamPack* params) {
    _48 = _48 < 0 ? _48 - 1 : -1;
    changeChild("行動Ｂ", params);
}

}  // namespace uking::ai
