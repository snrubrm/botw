#include "aal/aalSpeakerBalanceCalculator.h"
#include <cmath>
#include <math/seadMathCalcCommon.h>
#include "aal/aalInterior.h"
#include "aal/aalSpeakerChannelVolume.h"

namespace aal {

// NON_MATCHING: native frame layout, branches and register allocation differ.
void SpeakerBalanceCalculator::calculate(SpeakerChannelVolume* out, f32 volume, u32 angle_idx,
                                         f32 distance_rate, f32 spread, f32 lfe,
                                         const Interior* interior, Mode mode,
                                         SpeakerBalanceMode balance_mode) {
    const f32 main_volume = lfe > 1.0f ? (2.0f - lfe) * volume : volume;
    if (!interior) {
        const f32 stereo_volume = main_volume * 0.7071f;
        switch (mode) {
        case Mode::Add:
            out->volume[0] += stereo_volume;
            out->volume[1] += stereo_volume;
            break;
        case Mode::Max:
            out->volume[0] = sead::Mathf::max(out->volume[0], stereo_volume);
            out->volume[1] = sead::Mathf::max(out->volume[1], stereo_volume);
            break;
        }
        return;
    }
    if (interior->hasLFE()) {
        const f32 lfe_volume = sead::Mathf::clampMax(lfe, 1.0f) * volume;
        switch (mode) {
        case Mode::Add:
            out->volume[5] += lfe_volume;
            break;
        case Mode::Max:
            out->volume[5] = sead::Mathf::max(out->volume[5], lfe_volume);
            break;
        }
    }
    spread = sead::Mathf::clampMax(spread, 1.0f);
    if (spread < 0.0f) {
        const f32 range = spread + 1.0f;
        spread = 0.0f;
        distance_rate = range > 0.0f ? distance_rate / range : 1.0f;
    }
    distance_rate = sead::Mathf::clamp(distance_rate, 0.0f, 1.0f);
    spread = sead::Mathf::max(spread, 1.0f - distance_rate);
    const f32 interior_spread = interior->getUnk24();
    if (interior_spread > 0.0f)
        spread = interior_spread + (1.0f - interior_spread) * spread;
    if (interior->hasRear())
        angle_idx -= interior->getFrontSpeakerAngleIdx();
    else
        angle_idx -= 0x40000000;
    if (spread == 0.0f) {
        if (interior->hasRear())
            calcSpeakerBalanceFromAngleNoSpread_(out, angle_idx, main_volume, *interior,
                                                 mode, balance_mode);
        else
            calcSpeakerBalanceFromAngleNoSpreadStereo_(out, angle_idx, main_volume,
                                                       mode, balance_mode);
    } else {
        if (interior->hasRear())
            calcSpeakerBalanceFromAngleSpread_(out, angle_idx, spread, spread, main_volume,
                                               *interior, mode, balance_mode);
        else
            calcSpeakerBalanceFromAngleSpreadStereo_(out, angle_idx, spread, spread, main_volume,
                                                     mode, balance_mode);
    }
}

// NON_MATCHING: native temporary storage, branch joins and register use differ.
void SpeakerBalanceCalculator::calcSpeakerBalanceFromAngleNoSpread_(
    SpeakerChannelVolume* out, u32 angle_idx, f32 volume, const Interior& interior,
    Mode mode, SpeakerBalanceMode balance_mode) {
    f32 gains[5]{};
    const s32 speaker_num = interior.hasCenter() ? 5 : 4;
    for (s32 i = 0; i < speaker_num; ++i) {
        const u32 lower = interior.getAngleBoundaries()[i];
        const u32 upper = i < (interior.hasCenter() ? 4 : 3) ?
            interior.getAngleBoundaries()[i + 1] - 1 : ~u32(0);
        if (angle_idx < lower || angle_idx > upper)
            continue;
        const f32 ratio = f32(angle_idx - lower) / f32(upper - lower + 1);
        f32 first, second;
        if (balance_mode == SpeakerBalanceMode(1)) {
            first = std::sqrt(1.0f - ratio);
            second = std::sqrt(ratio);
        } else {
            sead::Mathf::sinCosIdx(&second, &first, u32(ratio * sead::Mathf::cQuarterRoundIdx));
        }
        gains[i] = first;
        gains[i < speaker_num - 1 ? i + 1 : 0] = second;
        break;
    }
    const f32 rear_volume = interior.getRearSpeakerGain() * volume;
    switch (mode) {
    case Mode::Add:
        out->volume[4] += gains[4] * volume;
        out->volume[1] += gains[0] * volume;
        out->volume[3] += rear_volume * gains[1];
        out->volume[2] += rear_volume * gains[2];
        out->volume[0] += gains[3] * volume;
        break;
    case Mode::Max:
        out->volume[4] = sead::Mathf::max(out->volume[4], gains[4] * volume);
        out->volume[1] = sead::Mathf::max(out->volume[1], gains[0] * volume);
        out->volume[3] = sead::Mathf::max(out->volume[3], rear_volume * gains[1]);
        out->volume[2] = sead::Mathf::max(out->volume[2], rear_volume * gains[2]);
        out->volume[0] = sead::Mathf::max(out->volume[0], gains[3] * volume);
        break;
    }
}

// NON_MATCHING: native temporary storage and register allocation differ.
void SpeakerBalanceCalculator::calcSpeakerBalanceFromAngleNoSpreadStereo_(
    SpeakerChannelVolume* out, u32 angle_idx, f32 volume, Mode mode,
    SpeakerBalanceMode balance_mode) {
    s32 first_index = 0;
    s32 second_index = 3;
    u32 lower = 0;
    f32 gains[5]{};
    if (angle_idx >= sead::Mathf::cHalfRoundIdx) {
        first_index = 3;
        second_index = 0;
        lower = sead::Mathf::cHalfRoundIdx;
    }
    const f32 ratio = f32(angle_idx - lower) / sead::Mathf::cHalfRoundIdx;
    f32 first, second;
    if (balance_mode == SpeakerBalanceMode(1)) {
        first = std::sqrt(1.0f - ratio);
        second = std::sqrt(ratio);
    } else {
        sead::Mathf::sinCosIdx(&second, &first, u32(ratio * sead::Mathf::cQuarterRoundIdx));
    }
    gains[first_index] = first;
    gains[second_index] = second;
    switch (mode) {
    case Mode::Add:
        out->volume[1] += gains[0] * volume;
        out->volume[0] += gains[3] * volume;
        break;
    case Mode::Max:
        out->volume[1] = sead::Mathf::max(out->volume[1], gains[0] * volume);
        out->volume[0] = sead::Mathf::max(out->volume[0], gains[3] * volume);
        break;
    }
}

// NON_MATCHING: native loop layout, temporary storage and register allocation differ.
void SpeakerBalanceCalculator::calcSpeakerBalanceFromAngleSpread_(
    SpeakerChannelVolume* out, u32 angle_idx, f32 left_spread, f32 right_spread,
    f32 volume, const Interior& interior, Mode mode, SpeakerBalanceMode balance_mode) {
    u32 left = u32(left_spread * sead::Mathf::cHalfRoundIdx);
    u32 right = u32(right_spread * sead::Mathf::cHalfRoundIdx);
    if (!left)
        left = 1;
    if (!right)
        right = 1;
    const u32 lower = angle_idx - left;
    const u32 upper = angle_idx + right - 1;
    AngleSection portions[2]{{~u32(0), 0}, {~u32(0), 0}};
    if (upper < lower) {
        portions[0] = {0, upper};
        portions[1] = {lower, ~u32(0)};
    } else {
        portions[0] = {lower, upper};
    }
    f32 gains[5]{};
    const s32 speaker_num = interior.hasCenter() ? 5 : 4;
    for (s32 i = 0; i < speaker_num; ++i) {
        AngleSection section{interior.getAngleBoundaries()[i], ~u32(0)};
        if (i < (interior.hasCenter() ? 4 : 3))
            section.upper = interior.getAngleBoundaries()[i + 1] - 1;
        calcSpread_(&gains[i], &gains[i < speaker_num - 1 ? i + 1 : 0], section,
                    portions, f32(left) + f32(right), balance_mode);
    }
    if (balance_mode == SpeakerBalanceMode(1)) {
        for (s32 i = 0; i < speaker_num; ++i)
            gains[i] = std::sqrt(gains[i]);
    }
    const f32 rear_volume = interior.getRearSpeakerGain() * volume;
    switch (mode) {
    case Mode::Add:
        out->volume[4] += gains[4] * volume;
        out->volume[1] += gains[0] * volume;
        out->volume[3] += rear_volume * gains[1];
        out->volume[2] += rear_volume * gains[2];
        out->volume[0] += gains[3] * volume;
        break;
    case Mode::Max:
        out->volume[4] = sead::Mathf::max(out->volume[4], gains[4] * volume);
        out->volume[1] = sead::Mathf::max(out->volume[1], gains[0] * volume);
        out->volume[3] = sead::Mathf::max(out->volume[3], rear_volume * gains[1]);
        out->volume[2] = sead::Mathf::max(out->volume[2], rear_volume * gains[2]);
        out->volume[0] = sead::Mathf::max(out->volume[0], gains[3] * volume);
        break;
    }
}

// NON_MATCHING: native temporary storage, branch joins and register allocation differ.
void SpeakerBalanceCalculator::calcSpeakerBalanceFromAngleSpreadStereo_(
    SpeakerChannelVolume* out, u32 angle_idx, f32 left_spread, f32 right_spread,
    f32 volume, Mode mode, SpeakerBalanceMode balance_mode) {
    u32 left = u32(left_spread * sead::Mathf::cHalfRoundIdx);
    u32 right = u32(right_spread * sead::Mathf::cHalfRoundIdx);
    if (!left)
        left = 1;
    if (!right)
        right = 1;
    const u32 lower = angle_idx - left;
    const u32 upper = angle_idx + right - 1;
    AngleSection portions[2]{{~u32(0), 0}, {~u32(0), 0}};
    if (upper < lower) {
        portions[0] = {0, upper};
        portions[1] = {lower, ~u32(0)};
    } else {
        portions[0] = {lower, upper};
    }
    f32 gains[5]{};
    AngleSection section{0, sead::Mathf::cHalfRoundIdx - 1};
    calcSpread_(&gains[0], &gains[3], section, portions, f32(left) + f32(right), balance_mode);
    section = {sead::Mathf::cHalfRoundIdx, ~u32(0)};
    calcSpread_(&gains[3], &gains[0], section, portions, f32(left) + f32(right), balance_mode);
    // The original stereo path normalizes entries 0 and 1, then outputs entries 0 and 3.
    if (balance_mode == SpeakerBalanceMode(1)) {
        for (s32 i = 0; i < 2; ++i)
            gains[i] = std::sqrt(gains[i]);
    }
    switch (mode) {
    case Mode::Add:
        out->volume[1] += gains[0] * volume;
        out->volume[0] += gains[3] * volume;
        break;
    case Mode::Max:
        out->volume[1] = sead::Mathf::max(out->volume[1], gains[0] * volume);
        out->volume[0] = sead::Mathf::max(out->volume[0], gains[3] * volume);
        break;
    }
}

// NON_MATCHING: native unrolled intersections and arithmetic scheduling differ.
void SpeakerBalanceCalculator::calcSpread_(f32* first, f32* second,
                                           const AngleSection& section,
                                           const AngleSection* portions, f32 range,
                                           SpeakerBalanceMode balance_mode) {
    for (s32 i = 0; i < 2; ++i) {
        const auto& portion = portions[i];
        if (portion.lower > portion.upper || section.lower > portion.upper ||
            portion.lower > section.upper)
            continue;
        const u32 lower = sead::MathCalcCommon<u32>::max(section.lower, portion.lower);
        const u32 upper = sead::MathCalcCommon<u32>::min(section.upper, portion.upper);
        const f32 weight = f32(upper - lower + 1) / range;
        const f32 lower_distance = f32(lower - section.lower);
        const f32 upper_distance = f32(upper - section.lower + 1);
        const f32 ratio = (lower_distance + upper_distance) /
            (upper_distance + (lower_distance + (f32(section.upper - upper) +
                                                 f32(section.upper - lower + 1))));
        if (balance_mode == SpeakerBalanceMode(1)) {
            *first += weight * (1.0f - ratio);
            *second += weight * ratio;
        } else {
            f32 sine, cosine;
            sead::Mathf::sinCosIdx(&sine, &cosine, u32(ratio * sead::Mathf::cQuarterRoundIdx));
            *first += weight * cosine;
            *second += weight * sine;
        }
    }
}

}  // namespace aal
