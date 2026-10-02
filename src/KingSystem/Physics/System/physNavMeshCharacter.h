#pragma once

#include <basis/seadTypes.h>
#include <math/seadVector.h>
#include <thread/seadAtomic.h>
#include <thread/seadCriticalSection.h>
#include "KingSystem/Utils/Types.h"

namespace ksys::phys {

// Placeholder name (ctor 0x7100f7e9f0, dtor 0x7100f7eb14; 0x18 bytes): result returned by value
// from NavMeshCharacter::sub_7100F76078.
class Unk_7100f7e9f0 {
public:
    Unk_7100f7e9f0();
    ~Unk_7100f7e9f0();

    bool sub_7100F7EB40() const;

    /* 0x00 */ void* _0;
    /* 0x08 */ s32 _8;
    /* 0x10 */ void* _10;
};
KSYS_CHECK_SIZE_NX150(Unk_7100f7e9f0, 0x18);

// Name from the CSV (phys::NavMeshCharacter::*, ctor 0x7100f752ac). Returned by Actor vtable slot 45
// (InstanceSet::mNavMeshCharacter). Layout from the ctor and from the fields AI code accesses.
// The object also has vtable pointers at 0x38 and 0x48 (multiple inheritance, not modelled yet).
// TODO: incomplete.
class NavMeshCharacter {
public:
    NavMeshCharacter();
    virtual ~NavMeshCharacter();

    void finalize();
    void init();

    void sub_7100F75AB8();
    void sub_7100F75F3C(u8 value);
    void sub_7100F75F8C(const sead::Vector3f& target);
    void sub_7100F7604C(f32 value);
    void sub_7100F7605C(f32 value);
    void sub_7100F7606C(u32 value);
    // 0x7100f76078: `out` is written by the query (lane1: an output parameter); `to` is checked for
    // NaN first (default result).
    Unk_7100f7e9f0 sub_7100F76078(sead::Vector3f* out, const sead::Vector3f& to, f32 a3);
    void sub_7100F76314();
    void sub_7100F76778();
    void sub_7100F76790();
    void sub_7100F7D2C8();
    void sub_7100F7D308(s32 value);
    void sub_7100F7D350();

    /* 0x008 */ u64 _8 = 0;
    /* 0x010 */ void* _10 = nullptr;
    /* 0x018 */ void* _18 = nullptr;
    /* 0x020 */ u8 _20[0x58 - 0x20];
    /* 0x058 */ void* _58 = nullptr;
    /* 0x060 */ void* _60 = nullptr;
    /* 0x068 */ sead::CriticalSection _68;
    /* 0x0a8 */ u8 _a8[0xd0 - 0xa8];
    /* 0x0d0 */ sead::Atomic<s32> _d0 = 0;
    /* 0x0d4 */ sead::Vector3f _d4;
    /* 0x0e0 */ u8 _e0[0x194 - 0xe0];
    /* 0x194 */ sead::Vector3f _194;
    /* 0x1a0 */ sead::Vector3f _1a0;
    /* 0x1ac */ sead::Vector3f _1ac;
    /* 0x1b8 */ sead::Vector3f _1b8;
    /* 0x1c4 */ u32 _1c4;
    /* 0x1c8 */ u32 _1c8 = 0;
    /* 0x1d0 */ u64 _1d0 = 0;
    /* 0x1d8 */ u8 _1d8 = 4;
    /* 0x1d9 */ u8 _1d9 = 4;
    /* 0x1da */ u8 _1da = 0;
    /* 0x1db */ u8 _1db = 0;
    /* 0x1e0 */ sead::CriticalSection _1e0;
    /* 0x220 */ sead::Atomic<u32> _220 = 0;  // flags
    /* 0x224 */ sead::Vector3f _224;
    /* 0x230 */ sead::Vector3f _230;
    /* 0x23c */ sead::Vector3f _23c;
    /* 0x248 */ sead::Vector3f _248;
    /* 0x254 */ u8 _254[0x290 - 0x254];
    /* 0x290 */ u32 _290 = 0;
    /* 0x294 */ u8 _294 = 0;
    /* 0x298 */ u8 _298[0x2a4 - 0x298];
    /* 0x2a4 */ sead::Atomic<u32> _2a4;
    /* 0x2a8 */ f32 _2a8;
    /* 0x2ac */ f32 _2ac;
    /* 0x2b0 */ f32 _2b0;
    /* 0x2b4 */ u8 _2b4[0x2cc - 0x2b4];
    /* 0x2cc */ f32 _2cc;
    /* 0x2d0 */ f32 _2d0;
    /* 0x2d4 */ u8 _2d4[0x2e0 - 0x2d4];
    /* 0x2e0 */ void* _2e0;
};

}  // namespace ksys::phys
