#pragma once

#include <basis/seadTypes.h>
#include <math/seadMatrix.h>
#include <math/seadVector.h>
#include <prim/seadSafeString.h>
#include <thread/seadCriticalSection.h>
#include "KingSystem/ActorSystem/actBaseProcLink.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::act {

class Actor;
class ActorConstDataAccess;
class BaseProc;

// Placeholder name (methods 0x7100e4e084-0x7100e50590; its constructor is inlined into
// DynamicActor's). Embedded in DynamicActor at 0x870; returned by Actor vtable slot 100.
// TODO: incomplete.
class Unk_7100e4e084 {
public:
    explicit Unk_7100e4e084(Actor* actor) : mActor(actor) {}

    void sub_7100E4E084();
    void sub_7100E50010(int state, const sead::Vector3f& pos, bool a3);
    void sub_7100E5007C(int state, const sead::Vector3f& pos);
    void sub_7100E500F8(int state, const sead::Vector3f& pos, f32 a3, f32 a4);
    bool sub_7100E5019C(sead::Vector3f* pos, f32* a2, f32* a3);
    void sub_7100E50220();
    void sub_7100E50254();
    void sub_7100E50288();
    bool sub_7100E502B8() const;
    void sub_7100E502EC(BaseProc* proc);
    bool sub_7100E50334(ActorConstDataAccess* accessor);
    // Declared only (Carried::enter_): 0x7100e50450 (sets the carrier on the actor's `+0x6a8` object),
    // 0x7100e4fce8 (rotates `_80` towards the matrix), 0x7100e4edb8.
    void sub_7100E50450(Actor* carrier);
    void sub_7100E4FCE8(f32 a, const sead::Matrix34f* mtx);
    f32 sub_7100E4EDB8();
    // Declared only (CarriedData::x_6 / x_8 / x_12, lane1 s43): 0x7100e504c0 (when `_1d0` has a bit set, stores
    // `&_1c8` into the contact point info's `+0x58` and sets bit 2 of `_1d8`) and its undo 0x7100e5052c.
    void sub_7100E504C0();
    void sub_7100E5052C();

    /* 0x000 */ Actor* mActor;
    /* 0x008 */ sead::CriticalSection _8;
    /* 0x048 */ sead::FixedSafeString<32> _48;
    /* 0x080 */ sead::Matrix34f _80;
    /* 0x0b0 */ u64 _b0;
    /* 0x0b8 */ u32 _b8;
    /* 0x0bc */ u8 _bc = 0;
    /* 0x0c0 */ sead::CriticalSection _c0;
    /* 0x100 */ s32 _100 = -1;
    /* 0x104 */ sead::Vector3f _104 = sead::Vector3f::zero;
    /* 0x110 */ sead::Vector3f _110 = sead::Vector3f::zero;
    /* 0x11c */ f32 _11c = 0;
    /* 0x120 */ f32 _120 = 0;
    /* 0x124 */ f32 _124 = 1.0;
    /* 0x128 */ bool _128 = false;
    /* 0x129 */ bool _129 = false;
    /* 0x130 */ sead::CriticalSection _130;
    /* 0x170 */ BaseProcLink _170;
    /* 0x180 */ sead::CriticalSection _180;
    /* 0x1c0 */ f32 _1c0 = -1.0;
    // object with vtable 0x71024e8790 (invoke 0x7100e50590, clone, isNoDummy) and two bytes at
    // +0x8 / +0x10
    /* 0x1c4 */ u8 _1c4[0x1c8 - 0x1c4];  // padding (the object below is 8-aligned)
    /* 0x1c8 */ u8 _1c8[0x1d0 - 0x1c8];
    /* 0x1d0 */ u8 _1d0;  // flags (CarriedData tests bit 0 and counts the set bits)
    /* 0x1d1 */ u8 _1d1[0x1d8 - 0x1d1];
    /* 0x1d8 */ u8 _1d8;  // flags (bit 2: the contact point info points at `_1c8`)
    /* 0x1d9 */ u8 _1d9[0x1e0 - 0x1d9];
};
KSYS_CHECK_SIZE_NX150(Unk_7100e4e084, 0x1e0);

}  // namespace ksys::act
