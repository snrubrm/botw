#pragma once

#include <basis/seadTypes.h>
#include <prim/seadSafeString.h>
#include "aal/aalMemoryPool.h"

namespace sead {
class ArchiveRes;
class Heap;
}

namespace aal {

class AssetInfo;

// The factory 0x7101406B0C allocates 0xa8 bytes. Its vtable at
// 0x7102533000 has readAssetInfo followed by the two destructor entries.
// This is separate from IAssetInfoReadable's three-argument interface.
class AudioResource {
public:
    static AudioResource* create(u8* data, u32 size, sead::Heap* heap,
                                 const sead::SafeString& filename);

    virtual bool readAssetInfo(AssetInfo* info, const sead::SafeString& name);
    virtual ~AudioResource();

    // 0x7101406F5C borrows this pointer. ResourceBars 0x7101057588
    // supplies its member SafeString, which must outlive the resource.
    void setFilename(const sead::SafeString* filename);

private:
    AudioResource();

    const u8* mData;
    const void* _10;
    const sead::SafeString* mFilename;
    bool mValid;
    // The factory sets this only for its allocated HeapSafeString.
    // The destructor 0x7101406E54 deletes mFilename only when it is set.
    bool mOwnsFilename;
    u8 _22[6];
    AssetInfo* mAssetInfos;
    // The factory constructs this member at +0x30; the destructor
    // passes the same member to requestDetachMemoryPool.
    MemoryPool mMemoryPool;
    bool _98;
    u8 _99[7];
    // The factory casts ResourceMgr's result to ArchiveRes, and
    // readAssetInfo calls its native getFile slot.
    sead::ArchiveRes* mArchive;
};
static_assert(sizeof(AudioResource) == 0xa8);

}  // namespace aal
