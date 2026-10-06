#include "aal/aalAssetInfo.h"
#include <prim/seadSafeString.h>
#include "aal/aalMarkerInfo.h"
#include "aal/aalSystem.h"

namespace aal {

// 0x7100b95968
AssetInfo::AssetInfo() : mAudioData(nullptr), mReader(nullptr, nullptr), _10(0xff), mFlags(0), _18(nullptr) {}

// NON_MATCHING: same operations; the original addresses mFlags with plain offsets, this uses a pre-indexed write-back.
// 0x7100b959a8
void AssetInfo::setup(const void* audio_data, AudioMetaReader* reader) {
    mAudioData = audio_data;
    mReader = *reader;
    if (mReader.mData) {
        _10 = mReader.getAssetBlock_()->_10;
        if (mReader.getAssetBlock_()->flags & 4) {
            mFlags |= 1;
            return;
        }
    } else {
        _10 = 0xff;
    }
    mFlags &= ~1;
}

// 0x7100b95a00
bool AssetInfo::isValid() const {
    return mReader.mData && _10 != 0xff;
}

// 0x7100b95a20
bool AssetInfo::getStreamFilePath(sead::BufferedSafeString* path) const {
    if (!path)
        return false;

    if (!(mFlags & 2)) {
        const char* root = System::sInstance->mStreamFileRoot;
        const char* name = nullptr;
        if (mReader.mData) {
            const u32 name_offset = mReader.getAssetBlock_()->stream_name_offset;
            if (const char* table = mReader.getStringTable())
                name = table + name_offset;
        }
        path->format("%s%s%s", root, name, ".bfstm");
    }
    return true;
}

// NON_MATCHING: same loads and stores; the original loads both words first and stores them as one pair.
// 0x7100b95ab4
bool AssetInfo::getTrackParam(StreamTrack* track, s32 index) const {
    if (!track || static_cast<u32>(index) > 7 || !mReader.mData)
        return false;

    const auto& source = mReader.getAssetBlock_()->tracks[index];
    const u32 first = source._0;
    const u32 second = source._4;
    track->_0 = first;
    track->_4 = second;
    return true;
}

// 0x7100b95aec
bool AssetInfo::getLoopInfo(LoopInfo* info) const {
    if (!info)
        return false;

    info->is_looped = mReader.mData ? (mReader.getAssetBlock_()->flags >> 2) & 1 : 0;
    info->loop_start = mReader.mData ? mReader.getAssetBlock_()->loop_start : 0;
    info->loop_end = mReader.mData ? mReader.getAssetBlock_()->loop_end : 0;
    return true;
}

// 0x7100b95b4c
bool AssetInfo::getMarkerInfo(MarkerInfo* info) const {
    if (!info)
        return false;

    info->mMarkerNum = mReader.mData ? mReader.getMarkerBlock_()->marker_num : 0;
    info->mMarkers = mReader.mData ? mReader.getMarkerBlock_()->markers : nullptr;
    info->mStringTable = mReader.getStringTable();
    return true;
}

// NON_MATCHING: same logic; the original uses branches where this uses conditional selects, and the loop start/end registers are swapped.
// 0x7100b95bb0
s32 AssetInfo::addOffsetToPosition(s32 position, s32 offset, s32 wrap) const {
    s32 result = offset + position;
    if (mReader.mData && (mReader.getAssetBlock_()->flags & 4)) {
        const s32 loop_start = mReader.getAssetBlock_()->loop_start;
        const s32 loop_end = mReader.getAssetBlock_()->loop_end;
        if (offset > 0) {
            const s32 over = result - loop_end;
            if (over < 0)
                return result;
            return over + loop_start;
        }
        if (offset >= 0)
            return result;
        if (wrap > 0) {
            if (result >= loop_start)
                return result;
            return loop_end + result - loop_start;
        }
    }
    return result < 0 ? 0 : result;
}

// 0x7100b95c18
const char* MarkerInfo::getName(s32 index) const {
    if (!mMarkerNum)
        return nullptr;
    return mStringTable + static_cast<const Marker*>(mMarkers)[index].name_offset;
}

// 0x7100b95c3c
s32 MarkerInfo::getStartPos(s32 index) const {
    if (!mMarkerNum)
        return 0;
    return static_cast<const Marker*>(mMarkers)[index].start_position;
}

// 0x7100b95c5c
const void* MarkerInfo::getMetaData(s32 index) const {
    if (!mMarkerNum)
        return nullptr;
    return &static_cast<const Marker*>(mMarkers)[index];
}

}  // namespace aal
