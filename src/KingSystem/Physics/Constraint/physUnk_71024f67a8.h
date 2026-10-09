#pragma once

#include "KingSystem/Utils/Types.h"

namespace ksys::phys {

// Whole factory 0x7100f71be4 allocates 0x40 and installs the complete
// two-slot lifetime table 0x71024f67a8. The payload has no member destructor.
class Unk_71024f67a8 {
public:
    virtual ~Unk_71024f67a8();
    static void sub_7100F71CB4(Unk_71024f67a8* object);

private:
    u8 _8[0x38];
};
KSYS_CHECK_SIZE_NX150(Unk_71024f67a8, 0x40);

}  // namespace ksys::phys
