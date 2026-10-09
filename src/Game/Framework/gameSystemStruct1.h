#pragma once

#include <math/seadVector.h>
#include "KingSystem/Utils/Types.h"

namespace uking::frm {

// Native controller state record: System owns it at +0x18; allocation proves its 0x98 extent.
class SystemStruct1 {
public:
    virtual ~SystemStruct1();
    static SystemStruct1* getInstance();

    // Constructor zeroes the complete vector; calcController copies all three input components.
    sead::Vector3f _8;

private:
    u8 _14[0x98 - 0x14];
};
KSYS_CHECK_SIZE_NX150(SystemStruct1, 0x98);

}  // namespace uking::frm
