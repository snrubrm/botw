#pragma once

#include <prim/seadSafeString.h>

namespace gsys {

// ModelResource::initialize_ (c0ab10) creates 0x18-byte records for several SDK
// animation resource types. The first pointer is generic resource data, not a
// pointer overlay onto a ResSkeletalAnim pointer array.
class G3dResAnimationEx {
public:
    G3dResAnimationEx();
    void updateNameHash(const sead::SafeString& name);

    void* resource;
    u32 nameHash;
    const char* name;
};
static_assert(sizeof(G3dResAnimationEx) == 0x18);

}  // namespace gsys
