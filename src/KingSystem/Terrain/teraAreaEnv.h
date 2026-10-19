#pragma once

#include <basis/seadTypes.h>
#include <container/seadBuffer.h>
#include "KingSystem/Utils/Types.h"

namespace gsys {
class ModelSceneEnv;
}

namespace ksys::tera {

// One attribute record of an area environment entry. 0x7101074d40 reads the index array at +0x48;
// the attribute sampler 0x71010723c8 reads the two floats and the three words.
struct AreaEnvAttribute {
    u8 _0[0x48];
    /* 0x48 */ s32* mIndices;
    u8 _50[0x70 - 0x50];
    /* 0x70 */ f32* mValues;
    u8 _78[0x98 - 0x78];
    /* 0x98 */ f32 _98;
    u8 _9c[0xb8 - 0x9c];
    /* 0xb8 */ f32 _b8;
    u8 _bc[0xd8 - 0xbc];
    /* 0xd8 */ u32 _d8;
    u8 _dc[0xf8 - 0xdc];
    /* 0xf8 */ u32 _f8;
    u8 _fc[0x118 - 0xfc];
    /* 0x118 */ u32 _118;
};

// One column of the area environment data (AreaEnvGetter::Data::mAttributes): an index array and
// the five per-index arrays read by 0x710106bd54.
struct AreaEnvColumn {
    u8 _0[0x48];
    /* 0x48 */ s32* mIndices;
    u8 _50[0x70 - 0x50];
    /* 0x70 */ f32* mValues;
    u8 _78[0x98 - 0x78];
    /* 0x98 */ f32* mWeights;
    u8 _a0[0xc0 - 0xa0];
    /* 0xc0 */ f32* mScales;
    u8 _c8[0xe8 - 0xc8];
    /* 0xe8 */ u32* mIds;
    u8 _f0[0x110 - 0xf0];
    /* 0x110 */ f32* mLimits;
};

// The three entry types of the AreaEnvGetter tables (the record fields _35 / _36 / _37 index them).
// Only the fields read by 0x71010723c8 / 0x7101074d40 are modelled.
struct AreaEnvEntry0 {
    // 0x710107b624 (placeholder name): the weight scale of attribute type `layer` (0 - 2).
    f32 sub_710107B624(s32 layer);

    u8 _0[0xe8];
    /* 0xe8 */ AreaEnvAttribute* mAttributes0[3];
    /* 0x100 */ AreaEnvAttribute* mAttributes1[3];
    u8 _118[0x1c8 - 0x118];
    /* 0x1c8 */ f32 _1c8;
    u8 _1cc[0x1e8 - 0x1cc];
    /* 0x1e8 */ f32 _1e8;
    u8 _1ec[0x208 - 0x1ec];
    /* 0x208 */ u32 _208;
    u8 _20c[0x228 - 0x20c];
    /* 0x228 */ u32 _228;
    u8 _22c[0x248 - 0x22c];
    /* 0x248 */ u32 _248;
};

struct AreaEnvEntry1 {
    u8 _0[0x250];
    /* 0x250 */ f32 _250;
    u8 _254[0x270 - 0x254];
    /* 0x270 */ f32 _270;
    u8 _274[0x290 - 0x274];
    /* 0x290 */ u32 _290;
    u8 _294[0x2b0 - 0x294];
    /* 0x2b0 */ u32 _2b0;
    u8 _2b4[0x2d0 - 0x2b4];
    /* 0x2d0 */ u32 _2d0;
};

struct AreaEnvEntry2 {
    u8 _0[0x1e8];
    /* 0x1e8 */ f32 _1e8;
    u8 _1ec[0x208 - 0x1ec];
    /* 0x208 */ f32 _208;
    u8 _20c[0x228 - 0x20c];
    /* 0x228 */ u32 _228;
    u8 _22c[0x248 - 0x22c];
    /* 0x248 */ u32 _248;
    u8 _24c[0x268 - 0x24c];
    /* 0x268 */ u32 _268;
};

// The game-side area environment getter (vtable 0x71025041b8). The constructor 0x710107c0f4 takes a
// gsys::ModelSceneEnv, stores it at +0x8 and clears the 0x48 bytes at +0x10. The three lookups below
// read the tables of the object at +0x10 (a 0x2c0 byte record built by 0x710107c124).
class AreaEnvGetter {
public:
    // The 0x2c0 byte object at +0x10 (the constructor 0x710107b63c). The three attribute pointers at
    // +0x278 and the three sead::Buffer tables at +0x290 / +0x2a0 / +0x2b0.
    struct Data {
        u8 _0[0x278];
        /* 0x278 */ AreaEnvColumn* mAttributes[3];
        /* 0x290 */ sead::Buffer<AreaEnvEntry0*> mEntries0;
        /* 0x2a0 */ sead::Buffer<AreaEnvEntry1*> mEntries1;
        /* 0x2b0 */ sead::Buffer<AreaEnvEntry2*> mEntries2;
    };
    KSYS_CHECK_SIZE_NX150(Data, 0x2c0);

    // 0x710107c9c4: the entry of the first table (at most 64 entries).
    AreaEnvEntry0* sub_710107C9C4(s32 index);
    // 0x710107c9f4: the entry of the second table (at most 32 entries).
    AreaEnvEntry1* sub_710107C9F4(s32 index);
    // 0x710107ca24: the entry of the third table (at most 32 entries).
    AreaEnvEntry2* sub_710107CA24(s32 index);

    // The vtable pointer of the original class (0x71025041b8). The class is not polymorphic here,
    // so the slot is kept as plain data to keep the member offsets right.
    u64 _0 = 0;
    /* 0x08 */ const gsys::ModelSceneEnv* mEnv = nullptr;
    /* 0x10 */ Data* mData = nullptr;
    u8 _18[0x58 - 0x18];
};
KSYS_CHECK_SIZE_NX150(AreaEnvGetter, 0x58);

}  // namespace ksys::tera
