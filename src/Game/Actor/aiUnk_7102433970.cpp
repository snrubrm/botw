#include "Game/Actor/aiUnk_7102433970.h"
#include <random/seadGlobalRandom.h>
#include <math/seadMathCalcCommon.h>
#include <utility>

Unk_7100743798::Unk_7100743798()
    : _0(-1), _e0(0.0f, 0.0f), _13c(0), _140(false), _141(false) {}

bool Unk_7100743798::sub_7100743814(ksys::act::Actor* actor) {
    _8.sub_7100721830(actor, true);
    _0 = -1;
    _e0.reset(0.0f);
    _13c = 0;
    _140 = false;
    _141 = false;
    for (auto& permutation : mPermutations) {
        permutation.mCount = 5;
        for (s8 i = 0; i < permutation.mCount; ++i)
            permutation.mValues[i] = i;
    }
    mPermutations[4].mCount = 9;
    for (s8 i = 0; i < mPermutations[4].mCount; ++i)
        mPermutations[4].mValues[i] = i;
    mPermutations[6].mCount = 8;
    for (s8 i = 0; i < mPermutations[6].mCount; ++i)
        mPermutations[6].mValues[i] = i;
    return true;
}

// NON_MATCHING: Boolean mode selection and timer store scheduling differ.
void Unk_7100743798::sub_7100743A40() {
    _8.sub_7100721C48();
    if (!(_e0.value <= sead::Mathf::epsilon()))
        _e0.update();
    if (_0 == -1 || !(_e0.value <= sead::Mathf::epsilon()) || !_8._c9)
        return;
    bool skip = _13c >= 4 && (_0 == 6 || _0 == 1);
    if (_140)
        skip |= _0 == 1;
    if (_141 || (_0 != 0 && _0 != 1 && _0 != 3)) {
        if (!skip) {
            sead::FixedSafeString<64> label;
            sub_7100743BD4(_0, &label);
            _8.set(5.0f, label);
            const f32 time = _0 == 6 ? 100.0f : _0 == 1 ? 90.0f : 60.0f;
            _e0.reset(time);
        }
    }
    _0 = -1;
}

// NON_MATCHING: The original has a separate inlined shuffle in each mode case; this common
// permutation path keeps the natural implementation without an unsupported inline-only helper.
void Unk_7100743798::sub_7100743BD4(s32 mode, sead::BufferedSafeString* label) {
    if (!label)
        return;
    const char* format;
    switch (mode) {
    case 0:
        format = "Approach_%02d";
        break;
    case 1:
        format = "Leave_%02d";
        break;
    case 2:
        format = "Worry_%02d";
        break;
    case 3:
        format = "Restart_%02d";
        break;
    case 4:
        format = "Jump_%02d";
        break;
    case 5:
        format = "Success_%02d";
        break;
    case 6:
        format = "Return_%02d";
        break;
    default:
        label->clear();
        return;
    }
    auto& permutation = mPermutations[mode];
    if (permutation.mIndex == 0) {
        for (s8 i = 0; i < permutation.mCount; ++i) {
            const s8 random = sead::GlobalRandom::instance()->getU32(permutation.mCount);
            if (i != random)
                std::swap(permutation.mValues[i], permutation.mValues[random]);
        }
    }
    const s8 value = permutation.mValues[permutation.mIndex];
    permutation.mIndex = (permutation.mIndex + 1) % permutation.mCount;
    label->format(format, value);
}

// 0x7100744200: switches to `mode` (unless one is already set and `force` is false). Mode 1 restarts the timer
// `_e0` at 90 (or keeps its current value if that is larger) with the default rate.
void Unk_7100743798::sub_7100744200(s32 mode, bool force) {
    if (_0 != -1 && !force)
        return;
    f32 value = mode == 1 ? 90.0f : 0.0f;
    _0 = mode;
    if (mode != 1)
        return;
    value = value > _e0.value ? value : _e0.value;
    _e0 = ksys::Timer(value, value);
}
