#pragma once

#include <basis/seadTypes.h>
#include <math/seadMatrix.h>
#include <math/seadVector.h>
#include <prim/seadSafeString.h>
#include <thread/seadCriticalSection.h>
#include "KingSystem/ActorSystem/actBaseProcLink.h"
#include "KingSystem/Physics/System/physContactPointInfo.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::act {

class Actor;
class ActorConstDataAccess;
class ActorChemicals;
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
    // 0x7100e4ff1c (placeholder name).
    void sub_7100E4FF1C(sead::Vector3f* out, const sead::Matrix34f& mtx) const;
    // 0x7100e50390 (placeholder name).
    bool sub_7100E50390(Actor* actor);
    // Declared only (Carried::enter_): 0x7100e50450 (sets the carrier on the actor's `+0x6a8` object),
    // 0x7100e4fce8 (rotates `_80` towards the matrix), 0x7100e4edb8.
    void sub_7100E50450(Actor* carrier);
    void sub_7100E4FCE8(f32 a, const sead::Matrix34f* mtx);
    f32 sub_7100E4EDB8();
    // Declared only (CarriedData::x_6 / x_8 / x_12, lane1 s43): 0x7100e504c0 (when `_1c8._8` has a bit set, stores
    // `&_1c8` into the contact point info's `+0x58` and sets bit 2 of `_1c8._10`) and its undo 0x7100e5052c.
    void sub_7100E504C0();
    // 0x7100e4f1d0 (lane4 s49; declared only, 1.4 KB): CarriedData::x_16 passes its `_14` / `_18`.
    bool sub_7100E4F1D0(f32 a, f32 b);
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
    // Contact callback (vtable 0x71024e8790; invoke 0x7100e50590): disables the contacts with bodies that are on the ground
    // (MovingTrolley ground hit, bit 1 of `_8`) or dynamic (motion type 0, bit 0 of `_8`).
    class ContactCallback : public phys::ContactPointInfo::ContactCallback {
    public:
        bool invoke(phys::ContactPointInfo::ShouldDisableContact* disable,
                    const phys::ContactPointInfo::Event& event) override;

        /* 0x08 */ u8 _8;  // flags (CarriedData tests bit 0 and counts the set bits)
        /* 0x09 */ u8 _9[0x10 - 0x9];
        /* 0x10 */ u8 _10;  // flags (bit 2: the contact point info points at `_1c8`; bit 0: the chemical carrier is set)
    };
    /* 0x1c8 */ ContactCallback _1c8;
};
KSYS_CHECK_SIZE_NX150(Unk_7100e4e084, 0x1e0);

}  // namespace ksys::act
