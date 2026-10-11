#include "aal/aalMarkerController.h"
#include "aal/aalSoundSource.h"
#include "aal/aalMarkerInfo.h"
#include <math/seadMathCalcCommon.h>

namespace aal {

// 0x7100b9f3f0
MarkerController::MarkerController()
    : mSoundSource(nullptr), _8(nullptr), mCallback(nullptr), mCallbackParam(0), mCallbackUserData(nullptr), _28(-1), _2c(0) {}

// 0x7100b9f408
void MarkerController::setup(SoundSource* sound_source) {
    reset();
    mSoundSource = sound_source;
}

// 0x7100b9f424
void MarkerController::reset() {
    mSoundSource = nullptr;
    _8 = nullptr;
    mCallback = nullptr;
    mCallbackParam = 0;
    mCallbackUserData = nullptr;
    _28 = -1;
    _2c = 0;
}

// NON_MATCHING: the maximum selection uses a different comparison predicate.
void MarkerController::calcMarker(s32 sample_position, s32 loop_count) {
    if (!mCallback)
        return;
    if (_28 < 0)
        _28 = 0;
    if (sample_position != 0 || loop_count != 0) {
        const AssetInfo* asset = mSoundSource->getAssetInfo();
        if (!asset)
            return;
        AssetInfo::LoopInfo loop_info;
        if (!asset->getLoopInfo(&loop_info))
            return;
        MarkerInfo markers;
        asset->getMarkerInfo(&markers);
        s32 previous_position;
        s32 position;
        if (_28 == 0 && loop_count == 0) {
            if (_2c > 0) {
                checkMarkerInfo_(markers, 0, _2c, loop_info, true);
                if (_8)
                    checkMarkerInfo_(*_8, 0, _2c, loop_info, true);
                _28 = _2c;
            }
            position = asset->addOffsetToPosition(sample_position, -mCallbackParam, loop_count);
            previous_position = _28;
            position = sead::Mathi::max(position, previous_position);
        } else {
            position = asset->addOffsetToPosition(sample_position, -mCallbackParam, loop_count);
            previous_position = asset->addOffsetToPosition(_28, -mCallbackParam, loop_count);
        }
        checkMarkerInfo_(markers, previous_position, position, loop_info, false);
        if (_8)
            checkMarkerInfo_(*_8, previous_position, position, loop_info, false);
    }
    _28 = sample_position;
}

// NON_MATCHING: crossing branches and callback-record stack placement differ.
void MarkerController::checkMarkerInfo_(const MarkerInfo& markers, s32 previous_position,
                                        s32 position, const AssetInfo::LoopInfo& loop_info,
                                        bool initial) {
    for (u32 i = 0; i < markers.mMarkerNum; ++i) {
        const auto* marker = static_cast<const MarkerInfo::Marker*>(markers.getMetaData(i));
        if (!marker)
            continue;
        const s32 start = marker->start_position;
        bool crossed_start;
        if (previous_position > position && loop_info.is_looped) {
            crossed_start = (previous_position <= start && start <= loop_info.loop_end) ||
                            (loop_info.loop_start <= start && start < position);
        } else {
            crossed_start = previous_position <= start && start < position;
        }
        s32 type = 0;
        if (marker->_c == 0) {
            if (crossed_start)
                type = 1;
        } else {
            if (crossed_start)
                type = 2;
            const s32 end = start + marker->_c;
            if (end > _2c) {
                bool crossed_end;
                if (previous_position > position && loop_info.is_looped) {
                    crossed_end = (previous_position <= end && end <= loop_info.loop_end) ||
                                  (loop_info.loop_start <= end && end < position);
                } else {
                    crossed_end = previous_position <= end && end < position;
                }
                if (crossed_end)
                    type = 3;
            }
        }
        if (type == 0)
            continue;
        MarkerCallbackInfo info;
        info.sound_source = mSoundSource;
        info.type = type;
        info.id = marker->_0;
        info.name = markers.getName(i);
        info.sample_position = markers.getStartPos(i);
        if (type == 3)
            info.sample_position += marker->_c;
        info.duration = marker->_c;
        info.offset = position - start;
        info.initial = initial;
        mCallback(info, mCallbackUserData);
    }
}

// 0x7100b9f8ac
void MarkerController::setMarkerCallback(MarkerCallback callback, s32 param, void* user_data) {
    mCallback = callback;
    mCallbackParam = param;
    mCallbackUserData = user_data;
    if (mSoundSource)
        mSoundSource->mPrepareFlags |= 8;
}

// NON_MATCHING: SafeString construction stores and lookup branches differ.
s32 MarkerController::getMarkerSamplePos(const sead::SafeString& name) const {
    s32 position = -1;
    const MarkerInfo* extra_markers = _8;
    if (extra_markers) {
        for (u32 i = 0; i < extra_markers->mMarkerNum; ++i) {
            if (name == sead::SafeString(extra_markers->getName(i))) {
                position = extra_markers->getStartPos(i);
                break;
            }
        }
    }
    if (position >= 0)
        return position;
    const AssetInfo* asset = mSoundSource->getAssetInfo();
    MarkerInfo markers;
    if (asset && asset->getMarkerInfo(&markers)) {
        position = -1;
        for (u32 i = 0; i < markers.mMarkerNum; ++i) {
            if (name == sead::SafeString(markers.getName(i))) {
                position = markers.getStartPos(i);
                break;
            }
        }
    }
    return position;
}

}  // namespace aal
