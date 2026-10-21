#pragma once

#include <container/seadBuffer.h>
#include <heap/seadDisposer.h>
#include <math/seadVector.h>
#include "KingSystem/Utils/Types.h"

namespace uking {

// Stage-local navigation obstacles. Factory 0x7100e8e850 allocates 0x30 bytes;
// its singleton disposer starts at +0, followed by the 0x260-byte obstacle buffer.
class NavMeshSystem {
    SEAD_SINGLETON_DISPOSER(NavMeshSystem)
    NavMeshSystem() = default;
    ~NavMeshSystem();

public:
    void init(sead::Heap* heap);
    // 0x7100e8f1c0 (declaration only; placeholder name): called by Unk_710251cbf0's destructor with the
    // fire position, its obstacle id and 1.5f.
    void sub_7100E8F1C0(const sead::Vector3f* position, s32 id, f32 radius);

private:
    struct Entry;
    sead::Buffer<Entry> mEntries;
};
KSYS_CHECK_SIZE_NX150(NavMeshSystem, 0x30);

}  // namespace uking
