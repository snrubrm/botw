#pragma once

#include "KingSystem/Resource/resResource.h"

namespace ksys::res {

// Placeholder name (vtable 0x71025148f8, typeinfo 0x71025b71c8; ctor 0x71011fe300, size >= 0x1a8): the bfres
// resource of the texture handle manager. Only the type is modelled (for DynamicCast).
// TODO: incomplete.
class BfRes : public Resource {
    SEAD_RTTI_OVERRIDE(BfRes, Resource)
public:
    BfRes();
    ~BfRes() override;

    u8 _38[0x50 - 0x38];
    void* _50;
};

}  // namespace ksys::res
