#pragma once

#include <basis/seadTypes.h>
#include "aal/aalAudioMetaReader.h"

namespace sead {
template <typename T>
class SafeStringBase;
using SafeString = SafeStringBase<char>;
template <typename T>
class BufferedSafeStringBase;
}  // namespace sead

namespace aal {

class AssetInfo;
class MarkerInfo;

/// Reads the description of an asset by its name. TODO: the meaning of the flag is not known.
class IAssetInfoReadable {
public:
    virtual bool readAssetInfo(AssetInfo* asset_info, const sead::SafeString& name, bool flag) = 0;
};

/// The description of an audio asset (a view of the audio meta binary).
class AssetInfo {
public:
    struct StreamTrack {
        u32 _0;
        u32 _4;
    };

    struct LoopInfo {
        bool is_looped;
        s32 loop_start;
        s32 loop_end;
    };

    AssetInfo();

    /// 0x7100b959a8
    void setup(const void* audio_data, AudioMetaReader* reader);
    bool isValid() const;
    /// The name of the asset (nullptr if there is no string table).
    const char* getAssetName() const {
        if (!mReader.mData)
            return nullptr;
        const u32 name_offset = mReader.getAssetBlock_()->stream_name_offset;
        const char* table = mReader.getStringTable();
        if (!table)
            return nullptr;
        return table + name_offset;
    }
    bool getStreamFilePath(sead::BufferedSafeStringBase<char>* path) const;
    bool getTrackParam(StreamTrack* track, s32 index) const;
    bool getLoopInfo(LoopInfo* info) const;
    /// The sample rate of the audio data (0 if the asset has no description).
    f32 getSampleRate() const {
        return mReader.mData ? static_cast<f32>(mReader.getAssetBlock_()->sample_rate) : 0.0f;
    }
    bool getMarkerInfo(MarkerInfo* info) const;
    /// Adds the offset to the position and keeps the result inside of the loop of the asset (if it is looped).
    s32 addOffsetToPosition(s32 position, s32 offset, s32 wrap) const;

    const void* mAudioData;
    AudioMetaReader mReader;
    /// 0xff: the asset is not valid.
    u8 _10;
    /// Bit 0: the asset is looped; bit 1: the stream file path is not built from the name of the asset; bit 2: the
    /// prefetched data is ignored (SoundController::setIgnorePrefetch).
    u8 mFlags;
    void* _18;
};
static_assert(sizeof(AssetInfo) == 0x20, "aal::AssetInfo size mismatch");

}  // namespace aal
