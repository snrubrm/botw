#include "Game/AI/AI/aiRandomSelectThreeActionBase.h"
#include <random/seadGlobalRandom.h>

namespace uking::ai {

RandomSelectThreeActionBase::RandomSelectThreeActionBase(const InitArg& arg)
    : ksys::act::ai::Ai(arg) {}

RandomSelectThreeActionBase::~RandomSelectThreeActionBase() = default;

bool RandomSelectThreeActionBase::init_(sead::Heap* heap) {
    _50 = 0;
    _54 = 0;
    _58 = 0;
    return true;
}

void RandomSelectThreeActionBase::enter_(ksys::act::ai::InlineParamPack* params) {
    const f32 rate_a = m34() + *mCorrectRatioA_s * _50;
    const f32 rate_b = m35() + *mCorrectRatioA_s * _54;
    const f32 rate_c = m36() + *mCorrectRatioA_s * _58;
    const f32 total = rate_a + rate_b + rate_c;
    const f32 value = total * sead::GlobalRandom::instance()->getF32();

    if (value < rate_a) {
        _50 = 0;
        ++_54;
        ++_58;
        changeChild("行動Ａ", params);
    } else {
        ++_50;
        if (value < rate_a + rate_b) {
            _54 = 0;
            ++_58;
            changeChild("行動Ｂ", params);
        } else {
            ++_54;
            _58 = 0;
            changeChild("行動Ｃ", params);
        }
    }
}

void RandomSelectThreeActionBase::calc_() {}

void RandomSelectThreeActionBase::leave_() {
    ksys::act::ai::Ai::leave_();
}

void RandomSelectThreeActionBase::loadParams_() {
    getStaticParam(&mCorrectRatioA_s, "CorrectRatioA");
    getStaticParam(&mCorrectRatioB_s, "CorrectRatioB");
    getStaticParam(&mCorrectRatioC_s, "CorrectRatioC");
}

f32 RandomSelectThreeActionBase::m34() {
    return 1.0f;
}

f32 RandomSelectThreeActionBase::m35() {
    return 1.0f;
}

f32 RandomSelectThreeActionBase::m36() {
    return 1.0f;
}

}  // namespace uking::ai
