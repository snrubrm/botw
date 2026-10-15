#pragma once

#include <container/seadBuffer.h>
#include <prim/seadBitFlag.h>
#include "KingSystem/Resource/resHandle.h"
#include "KingSystem/Resource/resResDerived.h"
#include "KingSystem/Resource/resUnk_71024F9938.h"
#include "KingSystem/Utils/Types.h"

namespace gsys {
class Model;
}

namespace ksys::act {

// Complete map-manager construction D44358 allocates 0x78 and calls 124AA74.
// This owner is nonpolymorphic. It loads one merged far model per entry and draws the loaded ones.
class FarActorMerge {
public:
    // Record in the merge data (+0x58) that an entry points to. Offsets 0 and 4 are string offsets into the data.
    struct EntryInfo {
        s32 name_offset;
        s32 model_name_offset;
        u8 _8[4];
        s32 num_ids;
        f32 translate[3];
    };

    struct Entry {
        // 0: not loaded, 1: model created.
        s32 state;
        res::ResDerived res;
        gsys::Model* model;
        res::Unk_71024f9958 _60;
        EntryInfo* info;
        // Sorted ids (num_ids of them).
        s32* ids;
    };
    KSYS_CHECK_SIZE_NX150(Entry, 0xa8);

    FarActorMerge();
    ~FarActorMerge();
    void cleanup();
    // D466C8 supplies the generated map name and heap to this empty method.
    void sub_710124ABC0(const sead::SafeString& name, sead::Heap* heap);
    void requestDraw();
    // Whether a loaded entry lists `id`.
    bool x(s32 id);

private:
    sead::BitFlag8 mFlags;
    sead::BitFlag32 mLoadedEntries;
    res::Handle mHandle;
    // Merge data.
    u8* _58 = nullptr;
    void* _60 = nullptr;
    sead::Buffer<Entry> mEntries;
};
KSYS_CHECK_SIZE_NX150(FarActorMerge, 0x78);

}  // namespace ksys::act
