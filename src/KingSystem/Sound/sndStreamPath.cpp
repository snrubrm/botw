#include "KingSystem/Sound/sndSound.h"
#include <cstdarg>
#include <aal/aalAssetType.h>
#include <filedevice/seadPath.h>
#include <codec/seadHashCRC32.h>
#include "Game/gameUnkRttiPlaceholders.h"

namespace ksys::snd {

Unk_710105fe78::Unk_710105fe78() = default;

// NON_MATCHING: by-value va_list passing retains a descriptor copy and larger save area.
void Unk_710105fe78::Callback::sub_710105FE08(const char* format, ...) {
    va_list args;
    va_start(args, format);
    mString.formatV(format, args);
    va_end(args);
}

// NON_MATCHING: string and virtual-reader argument scheduling differs.
bool Unk_710105fe78::sub_7101060D14(aal::AssetInfo* info,
                                   const sead::SafeString& path,
                                   const sead::SafeString& asset) {
    if (asset.isEmpty())
        return false;
    sead::FixedSafeString<128> basename;
    sead::Path::getFileName(&basename, path);
    sead::FixedSafeString<128> archive_name;
    archive_name.format("%s%s", basename.cstr(), ".bars");
    auto* resource = sub_7101060C04(archive_name);
    // Existing checked override has an unused flag; retain its true current declaration.
    if (!resource || !resource->readAssetInfo(info, asset, false))
        return false;
    // Actual relative-index enum protocol, not a raw byte substitute.
    if (aal::AssetType(info->_10) == aal::AssetType::Stream) {
        mCallback.sub_710105FE08("Stream_%s", basename.cstr());
        info->_18 = &mCallback;
    }
    return true;
}

// NON_MATCHING: cache-bound and entry-pointer loads are scheduled differently.
ResourceBars* Unk_710105fe78::sub_7101060C04(const sead::SafeString& name) {
    const u32 hash = sead::HashCRC32::calcStringHash(name.cstr());
    const auto* entries = _8->getBufferPtr();
    s32 low = 0;
    s32 high = _10;
    while (true) {
        const s32 middle = (low + high) / 2;
        const auto& entry = entries[middle];
        if (entry.mHash == hash)
            return sead::DynamicCast<ResourceBars>(entry.mHandle->getResource());
        if (entry.mHash < hash) {
            if (low == middle)
                return nullptr;
            low = middle;
        } else {
            if (high == middle)
                return nullptr;
            high = middle;
        }
    }
}

}  // namespace ksys::snd
