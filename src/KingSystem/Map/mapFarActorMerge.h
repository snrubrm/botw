#pragma once

#include "KingSystem/Resource/resHandle.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::map {

// Complete map-manager construction D44358 allocates 0x78 and calls 124AA74.
// Complete 124AA74/124AAAC and independent 124AAD0 establish the Handle at +8.
// This owner is nonpolymorphic; the remaining state is still opaque.
class FarActorMerge {
public:
    FarActorMerge();
    ~FarActorMerge();
    void cleanup();
    // D466C8 supplies the generated map name and heap to this empty method.
    void sub_710124ABC0(const sead::SafeString& name, sead::Heap* heap);

private:
    u8 _0[8];
    res::Handle mHandle;
    u8 _58[0x78 - 0x58];
};
KSYS_CHECK_SIZE_NX150(FarActorMerge, 0x78);

}  // namespace ksys::map
