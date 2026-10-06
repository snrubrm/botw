#include "aal/aalAudioMetaReader.h"

namespace aal {

// 0x7100b9690c
f32 AudioMetaReader::getAmplitudePeakValue() const {
    if (!mData)
        return 0.0f;
    if (mData->version != 0x400)
        return 1.0f;
    auto* peak_block =
        reinterpret_cast<const PeakBlock*>(mData->peak_block_offset + reinterpret_cast<uintptr_t>(mData));
    return peak_block->amplitude_peak;
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

}  // namespace aal
