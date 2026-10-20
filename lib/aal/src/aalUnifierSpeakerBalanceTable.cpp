#include "aal/aalSpeakerBalanceUnifierMgr.h"
#include <basis/seadNew.h>
#include <cmath>
#include <math/seadMathCalcCommon.h>
#include "aal/aalInterior.h"
#include "aal/aalInteriorSet.h"
#include "aal/aalOutputDevice.h"
#include "aal/aalSettings.h"
#include "aal/aalSystemAccessor.h"

#include "aal/aalSystem.h"

namespace aal {

// 0x7100b946d4
UnifierSpeakerBalanceTable::UnifierSpeakerBalanceTable() : mData(nullptr) {}

// 0x7100b95630
f32 UnifierSpeakerBalanceTable::getTotalVolumeMax(DeviceType device, s32 interior) const {
    return mTotalVolumeMax[device][interior];
}

// 0x7100b95524
void UnifierSpeakerBalanceTable::getSpeakerBalanceU8Range(SpeakerChannelVolume* volume, s32 angle, DeviceType device,
                                                          s32 interior) const {
    const UnifierSpeakerBalanceData::ChannelBalance& balance = mData[device][interior][0][angle].mBalance;
    for (s32 i = 0; i < 5; ++i)
        volume->volume[i] = balance[i];
}

// 0x7100b95598
void UnifierSpeakerBalanceTable::getSpeakerBalanceU8RangeWithSpread(SpeakerChannelVolume* volume, s32 angle,
                                                                    DeviceType device, s32 interior, f32 spread) const {
    const s32 spread_index = static_cast<s32>(spread * 47.0f);
    const UnifierSpeakerBalanceData::ChannelBalance& balance =
        mData[device][interior][spread_index][angle].mBalance;
    for (s32 i = 0; i < 5; ++i)
        volume->volume[i] = balance[i];
}

// 0x7100b946dc
UnifierSpeakerBalanceTable::~UnifierSpeakerBalanceTable() {
    if (mData) {
        if (mData[0]) {
            delete[] mData[0];
            mData[0] = nullptr;
        }
        delete[] mData;
        mData = nullptr;
    }
    if (mTotalVolumeMax[0]) {
        delete[] mTotalVolumeMax[0];
        mTotalVolumeMax[0] = nullptr;
    }
}

// 0x7100b94738
void UnifierSpeakerBalanceTable::initialize(sead::Heap* heap) {
    mData = new (heap, 8) InteriorData*[DeviceType::size()];
    s32 num = 1;
    if (OutputDevice* device = SystemAccessor::getSettings()->getOutputDevice(DeviceType::TV))
        num = device->getNumOfInteriorMax();
    mData[0] = new (heap, 8) InteriorData[num];
    mTotalVolumeMax[0] = new (heap, 8) f32[num];
    mInteriorNum = num;
    makeTable();
}

// NON_MATCHING: native loop layout, temporary storage and register allocation differ.
void UnifierSpeakerBalanceTable::makeTable() {
    Settings* settings = System::sInstance->mSettings;
    InteriorSet* set = settings->getOutputDevice(DeviceType::TV)->getCurrentInteriorSet();
    if (!set) {
        for (s32 interior = 0; interior < mInteriorNum; ++interior) {
            for (s32 angle = 0; angle < 64; ++angle) {
                for (s32 spread = 0; spread < 48; ++spread)
                    mData[0][interior][spread][angle].mBalance = {{180, 180, 0, 0, 0}};
            }
        }
        mCurrentInteriorNum[0] = 0;
        return;
    }
    const SpeakerBalanceMode mode = settings->getCurrentSpeakerBalanceMode(DeviceType::TV);
    const s32 interior_num = set->getNumOfInterior();
    mCurrentInteriorNum[0] = sead::MathCalcCommon<s32>::min(interior_num, mInteriorNum);
    for (s32 i = 0; i < mCurrentInteriorNum[0]; ++i) {
        Interior* interior = set->getInterior(i);
        if (!interior) {
            for (s32 angle = 0; angle < 64; ++angle) {
                for (s32 spread = 0; spread < 48; ++spread)
                    mData[0][i][spread][angle].mBalance = {{180, 180, 0, 0, 0}};
            }
            continue;
        }
        const f32 base_spread = interior->getUnk24();
        const f32 spread_range = 1.0f - base_spread;
        f32 maximum_volume = 0.0f;
        for (s32 angle = 0; angle < 64; ++angle) {
            u32 angle_idx = (u32(angle) << 26) | 0x02000000;
            if (interior->hasRear()) {
                angle_idx -= interior->getFrontSpeakerAngleIdx();
                if (base_spread == 0.0f)
                    calcSpeakerBalance_(&mData[0][i][0][angle], *interior, angle_idx, mode);
                else
                    calcSpeakerBalanceSpread_(&mData[0][i][0][angle], *interior, angle_idx,
                                               base_spread, mode);
                for (s32 spread = 1; spread < 48; ++spread) {
                    const f32 amount = base_spread + spread_range * (f32(spread) / 47.0f);
                    calcSpeakerBalanceSpread_(&mData[0][i][spread][angle], *interior,
                                               angle_idx, amount, mode);
                }
            } else {
                angle_idx -= sead::Mathf::cQuarterRoundIdx;
                if (base_spread == 0.0f)
                    calcSpeakerBalanceStereo_(&mData[0][i][0][angle], angle_idx, mode);
                else
                    calcSpeakerBalanceSpreadStereo_(&mData[0][i][0][angle], angle_idx,
                                                     base_spread, mode);
                for (s32 spread = 1; spread < 48; ++spread) {
                    const f32 amount = base_spread + spread_range * (f32(spread) / 47.0f);
                    calcSpeakerBalanceSpreadStereo_(&mData[0][i][spread][angle], angle_idx,
                                                     amount, mode);
                }
            }
            const auto& balance = mData[0][i][47][angle].mBalance;
            const f32 total = f32(balance[0]) / 255.0f + f32(balance[1]) / 255.0f +
                              f32(balance[2]) / 255.0f + f32(balance[3]) / 255.0f +
                              f32(balance[4]) / 255.0f;
            maximum_volume = sead::Mathf::max(total, maximum_volume);
        }
        mTotalVolumeMax[0][i] = maximum_volume;
    }
}

// NON_MATCHING: native temporary storage, conversion and register allocation differ.
void UnifierSpeakerBalanceTable::calcSpeakerBalance_(
    UnifierSpeakerBalanceData* out, const Interior& interior, u32 angle_idx,
    SpeakerBalanceMode balance_mode) {
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
    const f32 rear_gain = interior.getRearSpeakerGain();
    gains[1] = rear_gain * gains[1];
    gains[2] = rear_gain * gains[2];
    out->mBalance[4] = u8(sead::Mathf::clamp(gains[4] * 255.0f, 0.0f, 255.0f));
    out->mBalance[1] = u8(sead::Mathf::clamp(gains[0] * 255.0f, 0.0f, 255.0f));
    out->mBalance[3] = u8(sead::Mathf::clamp(gains[1] * 255.0f, 0.0f, 255.0f));
    out->mBalance[2] = u8(sead::Mathf::clamp(gains[2] * 255.0f, 0.0f, 255.0f));
    out->mBalance[0] = u8(sead::Mathf::clamp(gains[3] * 255.0f, 0.0f, 255.0f));
}

// NON_MATCHING: native temporary storage, conversion and register allocation differ.
void UnifierSpeakerBalanceTable::calcSpeakerBalanceStereo_(
    UnifierSpeakerBalanceData* out, u32 angle_idx, SpeakerBalanceMode balance_mode) {
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
    out->mBalance[1] = u8(sead::Mathf::clamp(gains[0] * 255.0f, 0.0f, 255.0f));
    out->mBalance[0] = u8(sead::Mathf::clamp(gains[3] * 255.0f, 0.0f, 255.0f));
    out->mBalance[4] = 0;
    out->mBalance[2] = 0;
    out->mBalance[3] = 0;
}

// NON_MATCHING: native temporary storage, conversion and register allocation differ.
void UnifierSpeakerBalanceTable::calcSpeakerBalanceSpread_(
    UnifierSpeakerBalanceData* out, const Interior& interior, u32 angle_idx,
    f32 spread, SpeakerBalanceMode balance_mode) {
    u32 width = u32(spread * sead::Mathf::cHalfRoundIdx);
    if (!width)
        width = 1;
    const u32 lower = angle_idx - width;
    const u32 upper = angle_idx + width - 1;
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
                    portions, f32(width) + f32(width), balance_mode);
    }
    if (balance_mode == SpeakerBalanceMode(1)) {
        for (s32 i = 0; i < speaker_num; ++i)
            gains[i] = std::sqrt(gains[i]);
    }
    const f32 rear_gain = interior.getRearSpeakerGain();
    gains[1] = rear_gain * gains[1];
    gains[2] = rear_gain * gains[2];
    out->mBalance[4] = u8(sead::Mathf::clamp(gains[4] * 255.0f, 0.0f, 255.0f));
    out->mBalance[1] = u8(sead::Mathf::clamp(gains[0] * 255.0f, 0.0f, 255.0f));
    out->mBalance[3] = u8(sead::Mathf::clamp(gains[1] * 255.0f, 0.0f, 255.0f));
    out->mBalance[2] = u8(sead::Mathf::clamp(gains[2] * 255.0f, 0.0f, 255.0f));
    out->mBalance[0] = u8(sead::Mathf::clamp(gains[3] * 255.0f, 0.0f, 255.0f));
}

// NON_MATCHING: native temporary storage, conversion and register allocation differ.
void UnifierSpeakerBalanceTable::calcSpeakerBalanceSpreadStereo_(
    UnifierSpeakerBalanceData* out, u32 angle_idx, f32 spread,
    SpeakerBalanceMode balance_mode) {
    u32 width = u32(spread * sead::Mathf::cHalfRoundIdx);
    if (!width)
        width = 1;
    const u32 lower = angle_idx - width;
    const u32 upper = angle_idx + width - 1;
    AngleSection portions[2]{{~u32(0), 0}, {~u32(0), 0}};
    if (upper < lower) {
        portions[0] = {0, upper};
        portions[1] = {lower, ~u32(0)};
    } else {
        portions[0] = {lower, upper};
    }
    f32 gains[5]{};
    AngleSection section{0, sead::Mathf::cHalfRoundIdx - 1};
    calcSpread_(&gains[0], &gains[3], section, portions, f32(width) + f32(width), balance_mode);
    section = {sead::Mathf::cHalfRoundIdx, ~u32(0)};
    calcSpread_(&gains[3], &gains[0], section, portions, f32(width) + f32(width), balance_mode);
    // The original stereo path normalizes entries 0 and 1, then outputs entries 0 and 3.
    if (balance_mode == SpeakerBalanceMode(1)) {
        for (s32 i = 0; i < 2; ++i)
            gains[i] = std::sqrt(gains[i]);
    }
    out->mBalance[1] = u8(sead::Mathf::clamp(gains[0] * 255.0f, 0.0f, 255.0f));
    out->mBalance[0] = u8(sead::Mathf::clamp(gains[3] * 255.0f, 0.0f, 255.0f));
    out->mBalance[4] = 0;
    out->mBalance[2] = 0;
    out->mBalance[3] = 0;
}

// NON_MATCHING: native unrolled intersections and register allocation differ.
void UnifierSpeakerBalanceTable::calcSpread_(f32* first, f32* second,
                                            const AngleSection& section,
                                            const AngleSection* portions, f32 range,
                                            SpeakerBalanceMode balance_mode) const {
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
