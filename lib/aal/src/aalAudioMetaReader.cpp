#include "aal/aalAudioMetaReader.h"
#include <cstddef>
#include <cstring>
#include <prim/seadEndian.h>

namespace aal {

// 0x7100b9690c
f32 AudioMetaReader::getAmplitudePeakValue() const {
    if (!mData)
        return 0.0f;
    if (mData->version != 0x400)
        return 1.0f;
    return getAssetBlock_()->amplitude_peak;
}

// NON_MATCHING: only the operand order of the final address addition differs
// 0x7100b96940
const char* AudioMetaReader::getStringTable() const {
    if (!mData)
        return nullptr;
    if (mData->version >= 0x300)
        return getName_(mData->string_table_offset_v3);
    if (mData->version == 0x100)
        return getName_(mData->string_table_offset_v1);
    return nullptr;
}

// NON_MATCHING: native version branches and field conversions are unrolled separately.
AudioMetaReader::AudioMetaReader(const void* data, const char*) : mData(nullptr) {
    if (!data)
        return;
    Data header;
    std::memcpy(header.signature, data, sizeof(header.signature));
    const u32 signature = u32(header.signature[0]) | (u32(header.signature[1]) << 8) |
                          (u32(header.signature[2]) << 16) | (u32(header.signature[3]) << 24);
    if (signature != 0x41544d41)
        return;
    // The native API normalizes the supplied binary in place despite its const view.
    auto* bytes = const_cast<u8*>(static_cast<const u8*>(data));
    std::memcpy(&header.byte_order, bytes + 4, sizeof(u16) * 2);
    const bool swap = sead::Endian::markToEndian(header.byte_order) != sead::Endian::getHostEndian();
    if (swap) {
        header.byte_order = sead::Endian::swapU16(header.byte_order);
        header.version = sead::Endian::swapU16(header.version);
        std::memcpy(bytes + 4, &header.byte_order, sizeof(u16) * 2);
    }
    const u16 version = header.version;
    if (version != 0x100 && version != 0x300 && version != 0x400)
        return;
    // Retain the existing typed resource view; parsing below uses record copies.
    mData = static_cast<const Data*>(data);
    if (!swap)
        return;
    const size_t header_tail_size = version >= 0x300 ? sizeof(u32) * 5 : sizeof(u32) * 4;
    std::memcpy(&header._8, bytes + 8, header_tail_size);
    header._8 = sead::Endian::swapU32(header._8);
    header.asset_block_offset = sead::Endian::swapU32(header.asset_block_offset);
    header.marker_block_offset = sead::Endian::swapU32(header.marker_block_offset);
    if (version == 0x100) {
        header.string_table_offset_v1 = sead::Endian::swapU32(header.string_table_offset_v1);
    } else {
        header.track_block_offset = sead::Endian::swapU32(header.track_block_offset);
        header.string_table_offset_v3 = sead::Endian::swapU32(header.string_table_offset_v3);
    }
    std::memcpy(bytes + 8, &header._8, header_tail_size);
    AssetBlock asset;
    const size_t asset_size = version == 0x400 ? sizeof(asset) : offsetof(AssetBlock, amplitude_peak);
    std::memcpy(&asset, bytes + header.asset_block_offset, asset_size);
    asset._4 = sead::Endian::swapU32(asset._4);
    asset._14 = sead::Endian::swapU32(asset._14);
    asset.sample_rate = sead::Endian::swapU32(asset.sample_rate);
    asset.loop_start = sead::Endian::swapU32(asset.loop_start);
    asset.loop_end = sead::Endian::swapU32(asset.loop_end);
    std::memcpy(bytes + header.asset_block_offset + offsetof(AssetBlock, _4), &asset._4, sizeof(u32));
    std::memcpy(bytes + header.asset_block_offset + offsetof(AssetBlock, _14), &asset._14, sizeof(u32) * 4);
    if (version == 0x400) {
        u32 peak;
        std::memcpy(&peak, &asset.amplitude_peak, sizeof(peak));
        peak = sead::Endian::swapU32(peak);
        std::memcpy(bytes + header.asset_block_offset + offsetof(AssetBlock, amplitude_peak),
                    &peak, sizeof(peak));
    }
    for (auto& track : asset.tracks) {
        track._0 = sead::Endian::swapU32(track._0);
        track._4 = sead::Endian::swapU32(track._4);
    }
    std::memcpy(bytes + header.asset_block_offset + offsetof(AssetBlock, tracks), asset.tracks,
                sizeof(asset.tracks));
    MarkerBlock markers;
    std::memcpy(&markers, bytes + header.marker_block_offset, offsetof(MarkerBlock, markers));
    if (version >= 0x300) {
        markers._4 = sead::Endian::swapU32(markers._4);
        std::memcpy(bytes + header.marker_block_offset + offsetof(MarkerBlock, _4),
                    &markers._4, sizeof(u32));
    }
    markers.marker_num = sead::Endian::swapU32(markers.marker_num);
    std::memcpy(bytes + header.marker_block_offset + offsetof(MarkerBlock, marker_num),
                &markers.marker_num, sizeof(u32));
    for (u32 i = 0; i < markers.marker_num; ++i) {
        const size_t offset = header.marker_block_offset + offsetof(MarkerBlock, markers) +
                              size_t(i) * sizeof(Marker);
        Marker marker;
        std::memcpy(&marker, bytes + offset, sizeof(marker));
        marker._0 = sead::Endian::swapU32(marker._0);
        marker.name_offset = sead::Endian::swapU32(marker.name_offset);
        marker.start_position = sead::Endian::swapU32(marker.start_position);
        marker._c = sead::Endian::swapU32(marker._c);
        std::memcpy(bytes + offset, &marker, sizeof(marker));
    }
    if (version >= 0x300) {
        TrackBlock tracks;
        std::memcpy(&tracks, bytes + header.track_block_offset, offsetof(TrackBlock, tracks));
        tracks._4 = sead::Endian::swapU32(tracks._4);
        tracks.track_num = sead::Endian::swapU32(tracks.track_num);
        std::memcpy(bytes + header.track_block_offset + offsetof(TrackBlock, _4), &tracks._4,
                    sizeof(u32) * 2);
        for (u32 i = 0; i < tracks.track_num; ++i) {
            const size_t offset = header.track_block_offset + offsetof(TrackBlock, tracks) +
                                  size_t(i) * sizeof(StreamTrack);
            StreamTrack track;
            std::memcpy(&track, bytes + offset, sizeof(track));
            track._0 = sead::Endian::swapU32(track._0);
            track._4 = sead::Endian::swapU32(track._4);
            std::memcpy(bytes + offset, &track, sizeof(track));
        }
    }
}

}  // namespace aal
