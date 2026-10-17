#pragma once

#include <prim/seadPtrUtil.h>
#include "KingSystem/Resource/resEntryFactory.h"
#include "KingSystem/Resource/resResource.h"
#include "resource/seadResource.h"

namespace ksys::res {

class Placement : public Resource {
    SEAD_RTTI_OVERRIDE(Placement, Resource)
public:
    Placement() = default;
    ~Placement() override = default;

    static void registerFactory(sead::Heap* heap);

    void doCreate_(u8* buffer, u32 bufferSize, sead::Heap* heap) override;

    // Binary archive: doCreate_ binds the header at buffer and the entries at buffer + 0x10.
    // Static-map load/parse read the signed count at +8 and data/name offsets in eight-byte entries.
    struct Header {
        u8 _0[8];
        s8 num_entries;
        u8 _9[3];
        s32 name_table_offset;
    };
    struct Entry {
        u32 data_offset;
        u32 name_offset;
    };

    static_assert(sizeof(Header) == 0x10);
    static_assert(sizeof(Entry) == 8);

    // Inline-only in the original; names are guesses. Both static-map load and parse walks
    // read the signed count and resolve names through the header-relative name table.
    s32 getNumEntries() const { return mHeader->num_entries; }
    const char* getEntryName(s32 idx) const {
        const void* names = sead::PtrUtil::addOffset(mHeader, mHeader->name_table_offset);
        return static_cast<const char*>(sead::PtrUtil::addOffset(names, mEntries[idx].name_offset));
    }
    u8* getEntryData(s32 idx) const {
        return static_cast<u8*>(sead::PtrUtil::addOffset(mHeader, mEntries[idx].data_offset));
    }

    Header* mHeader = nullptr;
    Entry* mEntries = nullptr;
};

}  // namespace ksys::res
