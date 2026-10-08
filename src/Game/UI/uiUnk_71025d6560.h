#pragma once

#include <container/seadBuffer.h>
#include <heap/seadDisposer.h>
#include "KingSystem/Utils/Types.h"

namespace uking::ui {

// Placeholder singleton (instance pointer 0x71025d6560; lane2 s47; createInstance 0x7100949718, size 0x38, a table of
// pointers at 0x28 / 0x30 that is cleared and freed by the destructor (vtable 0x7102475238: D1 0x7100949808, D0
// 0x71009498c0), disposer vtable 0x7102475218).
class Unk_71025d6560 {
    SEAD_SINGLETON_DISPOSER(Unk_71025d6560)
    Unk_71025d6560() = default;

public:
    virtual ~Unk_71025d6560();

    // 0x7100949974 (placeholder name): allocates the table (0x91 entries) and clears it
    void sub_7100949974(sead::Heap* heap);
    // 0x7100949a60 (placeholder name): stores `value` at `index` if the table has such an entry
    void sub_7100949A60(s32 index, void* value);

    /* 0x28 */ sead::Buffer<void*> mEntries;
};
KSYS_CHECK_SIZE_NX150(Unk_71025d6560, 0x38);

}  // namespace uking::ui
