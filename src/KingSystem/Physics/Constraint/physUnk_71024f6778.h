#pragma once

#include <gsys/gsysModelAccessKey.h>
#include "KingSystem/Utils/Types.h"

namespace ksys::phys {

// Whole factory 0x7100f71854 allocates 0x60, installs its own two-slot
// destructor table 0x71024f6778, and constructs BoneAccessKeyEx at 0x18.
// Both destructors destroy exactly that member; other fields stay opaque.
class Unk_71024f6778 {
public:
    virtual ~Unk_71024f6778();

private:
    u8 _8[0x10];
    gsys::BoneAccessKeyEx mKey;
    u8 _50[0x10];
};
KSYS_CHECK_SIZE_NX150(Unk_71024f6778, 0x60);

}  // namespace ksys::phys
