#include "aal/aalBiquadFilterPreset.h"
#include <math/seadMathCalcCommon.h>

namespace aal {

// 0x7100b7c320
void BiquadFilterPreset::BiquadFilterCallback::GetCoefficients(
    nn::atk::BiquadFilterCoefficients* coefficients, int type, f32 value) const {
    getCofficientsImpl_(coefficients, type, value);
}

// 0x7100b7c32c
void BiquadFilterPreset::BiquadFilterCallback::getCofficientsImpl_(
    nn::atk::BiquadFilterCoefficients* coefficients, int, f32 value) const {
    const s32 last = mTableSize - 1;
    s32 index = s32(f32(last) * value);
    index = sead::Mathi::clamp(index, 0, last);
    *coefficients = mTable[index];
}

// 0x7100b7c374
void BiquadFilterPreset::BiquadFilterCallbackWithWeight::getCofficientsImpl_(
    nn::atk::BiquadFilterCoefficients* coefficients, int, f32 value) const {
    const f32 weighted = (2.0f - value) * value;
    const s32 last = mTableSize - 1;
    s32 index = s32(weighted * f32(last));
    index = sead::Mathi::clamp(index, 0, last);
    *coefficients = mTable[index];
}

// 0x7100b7c3c8
BiquadFilterPreset::BiquadFilterPreset()
    : _8(nullptr), _10(nullptr), _18(nullptr), _20(nullptr), _28(nullptr) {}

// 0x7100b7c3e4 (D1) / 0x7100b7c530 (D0)
BiquadFilterPreset::~BiquadFilterPreset() {
    finalize();
}

}  // namespace aal
