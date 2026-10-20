#include "aal/aalAudioResource.h"
#include <cstddef>
#include <codec/seadHashCRC32.h>
#include "aal/aalAssetType.h"
#include <resource/seadArchiveRes.h>
#include <cstring>
#include <resource/seadResource.h>
#include <resource/seadResourceMgr.h>
#include <resource/seadSharcArchiveRes.h>
#include <prim/seadEndian.h>
#include "aal/aalAssetInfo.h"
#include "aal/aalMemoryPoolManager.h"
#include "aal/aalSystem.h"
#include "aal/aalSystemAccessor.h"

namespace aal {

// 0x7101406E54
AudioResource::~AudioResource() {
    SystemAccessor::getSystem()->mMemoryPoolManager->requestDetachMemoryPool(&mMemoryPool);
    if (mArchive) {
        delete mArchive;
        mArchive = nullptr;
    }
    if (mOwnsFilename && mFilename) {
        delete mFilename;
        mFilename = nullptr;
    }
    if (mAssetInfos) {
        delete mAssetInfos;
        mAssetInfos = nullptr;
    }
}

// 0x7101406F5C
void AudioResource::setFilename(const sead::SafeString* filename) {
    mFilename = filename;
}

namespace {
// BARS starts with this sixteen-byte header and an asset-name hash array.
struct BarsHeader {
    u8 signature[4];
    u32 file_size;
    u16 byte_order;
    u16 version;
    u32 asset_num;
};
static_assert(sizeof(BarsHeader) == 0x10);
struct BarsAssetRecord {
    u32 metadata_offset;
    u32 audio_offset;
};
static_assert(sizeof(BarsAssetRecord) == 8);
}  // namespace

// The native static initializer constructs this Sharc factory.
extern sead::DirectResourceFactory<sead::SharcArchiveRes> sUnk_710266e6b8;

// NON_MATCHING: native initialization, header loads and register allocation differ.
AudioResource* AudioResource::create(u8* data, u32 size, sead::Heap* heap,
                                     const sead::SafeString& filename) {
    AudioResource* resource = new (heap, 8) AudioResource;
    if (!resource)
        return nullptr;
    resource->mData = data;
    const u32 signature = u32(data[0]) | (u32(data[1]) << 8) |
                          (u32(data[2]) << 16) | (u32(data[3]) << 24);
    if (signature == 0x53524142) {
        BarsHeader header;
        std::memcpy(&header, data, sizeof(header));
        resource->_10 = data + sizeof(BarsHeader) + header.asset_num * sizeof(u32);
        if (sead::Endian::markToEndian(header.byte_order) != sead::Endian::getHostEndian() ||
            header.version != 0x101)
            return nullptr;
        resource->_98 = true;
    } else {
        resource->mData = nullptr;
        sead::ResourceMgr::CreateArg arg;
        arg.buffer = data;
        arg.file_size = size;
        arg.buffer_size = size;
        arg.factory = &sUnk_710266e6b8;
        arg.heap = heap;
        resource->mArchive = sead::DynamicCast<sead::SharcArchiveRes>(
            sead::ResourceMgr::instance()->create(arg));
    }
    if (filename == sead::SafeString::cEmptyString) {
        resource->mFilename = &sead::SafeString::cEmptyString;
    } else {
        resource->mFilename = new (heap, 8) sead::HeapSafeString(heap, filename, 8);
        resource->mOwnsFilename = true;
    }
    resource->mValid = true;
    return resource;
}

// NON_MATCHING: natural binary record copies, string temporaries and enum handling differ.
bool AudioResource::readAssetInfo(AssetInfo* info, const sead::SafeString& name) {
    if (!info || name.calcLength() > 64)
        return false;
    if (_98) {
        if (!mData || !mValid)
            return false;
        BarsHeader header;
        std::memcpy(&header, mData, sizeof(header));
        if (!header.asset_num)
            return false;
        const u32 hash = sead::HashCRC32::calcStringHash(name.cstr());
        u32 lower = 0;
        u32 upper = header.asset_num;
        u32 index;
        for (;;) {
            const u32 middle = (lower + upper) >> 1;
            u32 candidate;
            std::memcpy(&candidate, mData + sizeof(BarsHeader) + size_t(middle) * sizeof(u32),
                        sizeof(candidate));
            if (candidate == hash) {
                index = middle;
                break;
            }
            if (candidate < hash) {
                if (lower == middle)
                    return false;
                lower = middle;
            } else {
                if (upper == middle)
                    return false;
                upper = middle;
            }
        }
        if (mAssetInfos) {
            *info = mAssetInfos[index];
            return true;
        }
        BarsAssetRecord entry;
        std::memcpy(&entry, static_cast<const u8*>(_10) + size_t(index) * sizeof(entry),
                    sizeof(entry));
        AudioMetaReader reader(mData + entry.metadata_offset, name.cstr());
        const void* audio = entry.audio_offset == 0xffffffff ? nullptr : mData + entry.audio_offset;
        info->setup(audio, &reader);
        return true;
    }
    sead::FixedSafeString<72> metadata_path(name);
    metadata_path.append(".bameta");
    if (!mArchive)
        return false;
    const void* metadata = mArchive->getFile(metadata_path);
    if (!metadata)
        return false;
    AudioMetaReader reader(metadata, name.cstr());
    if (!reader.mData)
        return false;
    const auto* metadata_bytes = static_cast<const u8*>(metadata);
    AudioMetaReader::Data metadata_header;
    std::memcpy(&metadata_header.asset_block_offset,
                metadata_bytes + offsetof(AudioMetaReader::Data, asset_block_offset),
                sizeof(metadata_header.asset_block_offset));
    AudioMetaReader::AssetBlock asset;
    std::memcpy(&asset, metadata_bytes + metadata_header.asset_block_offset,
                offsetof(AudioMetaReader::AssetBlock, tracks));
    const AssetType type(asset._10);
    if (type != AssetType::Wave && !(asset.flags & 2)) {
        info->setup(nullptr, &reader);
        return true;
    }
    sead::FixedSafeString<72> audio_path;
    switch (type.value()) {
    case AssetType::Wave:
        audio_path = name;
        audio_path.append(".bfwav");
        break;
    case AssetType::Stream:
        audio_path = name;
        audio_path.append(".bfstp");
        break;
    default:
        return false;
    }
    sead::ArchiveRes::FileInfo file_info{};
    const void* audio = mArchive->getFile(audio_path, &file_info);
    if (!audio || !file_info.mLength)
        return false;
    info->setup(audio, &reader);
    return true;
}

}  // namespace aal
