#pragma once

#include <basis/seadTypes.h>

namespace aal {

/// Reads the audio meta binary (the description of the audio assets). TODO: incomplete: the constructor
/// (0x7100b96058) and the asset lookups are not modeled, only the accessors of the header data.
class AudioMetaReader {
public:
    /// The peak amplitude of the audio data (1 for versions that do not store it, 0 if the resource is not valid).
    f32 getAmplitudePeakValue() const;
    /// The string table of the resource, nullptr if there is none.
    const char* getStringTable() const;

private:
    struct Data {
        u8 _0[6];
        /// 0x100 / 0x300 / 0x400.
        u16 version;
        u32 _8;
        u32 peak_block_offset;
        u32 _10;
        u32 string_table_offset_v1;
        u32 string_table_offset_v3;
    };

    struct PeakBlock {
        u8 _0[0x68];
        f32 amplitude_peak;
    };

    const char* getName_(u32 offset) const {
        return reinterpret_cast<const char*>(offset + reinterpret_cast<uintptr_t>(mData)) + 8;
    }

    const Data* mData;
};

}  // namespace aal
