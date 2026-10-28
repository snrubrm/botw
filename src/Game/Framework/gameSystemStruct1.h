#pragma once

#include <math/seadMatrix.h>
#include <math/seadVector.h>
#include "KingSystem/Utils/Types.h"

namespace uking::frm {

// Native controller state record: System owns it at +0x18; allocation proves its 0x98 extent.
class SystemStruct1 {
public:
    // Vtable 0x7102473410: two dtor slots, the complete dtor is a bare ret and the deleting one
    // calls operator delete, so the destructor body is empty and inline.
    virtual ~SystemStruct1() = default;
    // 0x7100900d3c / 0x7100900e10 (declared only): System constructs the vector and the per-frame
    // controller step copies the input into it.
    SystemStruct1();
    void calcController();
    static SystemStruct1* getInstance();
    // 0x7100897a94 (16 B): stores the instance pointer.
    static void setInstance(SystemStruct1* instance);

    // Constructor zeroes the complete vector; calcController copies all three input components.
    sead::Vector3f _8;

    u8 _14[0x38 - 0x14];
    // lane3 s84: copied by DungeonRotateGyro::enter_ (the gyro orientation, presumably).
    sead::Matrix33f _38;

private:
    static SystemStruct1* sInstance;

    u8 _5c[0x98 - 0x5c];
};
KSYS_CHECK_SIZE_NX150(SystemStruct1, 0x98);

}  // namespace uking::frm
