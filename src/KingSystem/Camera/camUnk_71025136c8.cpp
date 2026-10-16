#include "KingSystem/Camera/camUnk_71025136c8.h"

SEAD_TASK_SINGLETON_IMPL(Unk_71025136c8)

// NON_MATCHING: our sead StrTreeMap differs from the original's: its clear() does not rebuild the
// free list, freeBuffer() does not walk the nodes, and forEach takes the delegate by its concrete
// type (the original calls IDelegate1::invoke virtually; 0x71011f1da4 / 0x71011f1d08).
Unk_71025137d0::~Unk_71025137d0() {
    mMap.clear();
    mMap.freeBuffer();
    mEntries.freeBuffer();
}

// NON_MATCHING: StrTreeMap::clear (see above).
Unk_71025137a8::~Unk_71025137a8() {
    mMap.clear();
    if (void* work = _60.work())
        ::operator delete[](work);
    _60.reset();
}

// NON_MATCHING: StrTreeMap::clear (see above).
Unk_71025136c8::~Unk_71025136c8() = default;
