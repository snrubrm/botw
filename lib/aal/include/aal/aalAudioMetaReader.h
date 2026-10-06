#pragma once

#include <basis/seadTypes.h>

namespace aal {

/// Reads the audio meta binary (the description of the audio assets). TODO: incomplete: the constructor
/// (0x7100b96058) and the asset lookups are not modeled, only the accessors of the header data.
class AssetInfo;

/// Reads the audio meta binary (the description of the audio assets). TODO: incomplete: the constructor
/// (0x7100b96058) and the asset lookups are not modeled, only the accessors of the header data.
class AudioMetaReader {
public:
    explicit AudioMetaReader(const void* data = nullptr, const char* name = nullptr);

    /// The peak amplitude of the audio data (1 for versions that do not store it, 0 if the resource is not valid).
    f32 getAmplitudePeakValue() const;
    /// The string table of the resource, nullptr if there is none.
    const char* getStringTable() const;

private:
    friend class AssetInfo;

    struct Marker {
        u32 _0;
        u32 name_offset;
        s32 start_position;
        u32 _c;
    };
    static_assert(sizeof(Marker) == 0x10, "aal::AudioMetaReader::Marker size mismatch");

    struct StreamTrack {
        u32 _0;
        u32 _4;
    };

    /// The block of the description of an asset.
    struct AssetBlock {
        u8 _0[8];
        u32 stream_name_offset;
        u8 _c[4];
        u8 _10;
        u8 _11[2];
        /// Bit 2: the asset is looped.
        u8 flags;
        u8 _14[8];
        s32 loop_start;
        s32 loop_end;
        u8 _24[4];
        StreamTrack tracks[8];
        f32 amplitude_peak;
    };
    static_assert(sizeof(AssetBlock) == 0x6c, "aal::AudioMetaReader::AssetBlock size mismatch");

    struct MarkerBlock {
        u8 _0[8];
        u32 marker_num;
        Marker markers[1];
    };

    struct Data {
        u8 _0[6];
        /// 0x100 / 0x300 / 0x400.
        u16 version;
        u32 _8;
        u32 asset_block_offset;
        u32 marker_block_offset;
        u32 string_table_offset_v1;
        u32 string_table_offset_v3;
    };

    const char* getName_(u32 offset) const {
        return reinterpret_cast<const char*>(offset + reinterpret_cast<uintptr_t>(mData)) + 8;
    }

    const AssetBlock* getAssetBlock_() const {
        return reinterpret_cast<const AssetBlock*>(mData->asset_block_offset + reinterpret_cast<uintptr_t>(mData));
    }

    const MarkerBlock* getMarkerBlock_() const {
        return reinterpret_cast<const MarkerBlock*>(mData->marker_block_offset + reinterpret_cast<uintptr_t>(mData));
    }

    const Data* mData;
};

}  // namespace aal
