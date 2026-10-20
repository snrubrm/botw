#include "aal/aalAudioResource.h"
#include <resource/seadArchiveRes.h>
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
}  // namespace

// The native static initializer constructs this Sharc factory.
extern sead::DirectResourceFactory<sead::SharcArchiveRes> sUnk_710266e6b8;

// NON_MATCHING: native initialization stores and register allocation differ.
AudioResource* AudioResource::create(u8* data, u32 size, sead::Heap* heap,
                                     const sead::SafeString& filename) {
    AudioResource* resource = new (heap, 8) AudioResource;
    if (!resource)
        return nullptr;
    resource->mData = data;
    const u32 signature = u32(data[0]) | (u32(data[1]) << 8) |
                          (u32(data[2]) << 16) | (u32(data[3]) << 24);
    if (signature == 0x53524142) {
        const auto* header = reinterpret_cast<const BarsHeader*>(data);
        resource->_10 = data + sizeof(BarsHeader) + header->asset_num * sizeof(u32);
        if (sead::Endian::markToEndian(header->byte_order) != sead::Endian::getHostEndian() ||
            header->version != 0x101)
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

}  // namespace aal
