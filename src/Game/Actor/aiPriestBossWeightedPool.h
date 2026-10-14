#pragma once

#include <container/seadObjList.h>
#include <prim/seadRuntimeTypeInfo.h>
#include "KingSystem/Utils/Types.h"

// Actual weighted action record pool: ctor 0x710072b0e4, vtable 0x7102451280.
// The embedded record handlers remain unrecovered. The ObjList node follows
// each 0x2a0-byte record, as shown by init_ and the pool's list traversal.
class Unk_7102451280 {
public:
    struct Record {
        u64 _0[0x290 / sizeof(u64)];
        s32 mIndex;
        u8 _294[0x2a0 - 0x294];
    };
    SEAD_RTTI_BASE(Unk_7102451280)
    Unk_7102451280();
    virtual ~Unk_7102451280();
    void sub_710072B330();

    /* 0x08 */ sead::ObjList<Record> mRecords;
    /* 0x38 */ s32 _38 = 0;
};
KSYS_CHECK_SIZE_NX150(Unk_7102451280, 0x40);
