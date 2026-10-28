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

    // Constructor: four direction vectors, two identity matrices and the controller-state tail.
    sead::Vector3f _8;
    sead::Vector3f _14;
    sead::Vector3f _20;
    sead::Vector3f _2c;
    sead::Matrix33f _38;
    sead::Matrix33f _5c;
    bool _80;
    u8 _81[3];
    s32 _84;
    f32 _88;
    f32 _8c;
    s32 _90;
    s32 _94;

private:
    static SystemStruct1* sInstance;
};
KSYS_CHECK_SIZE_NX150(SystemStruct1, 0x98);

}  // namespace uking::frm
