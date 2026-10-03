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

    /* 0x000 */ Actor* mActor;
    /* 0x008 */ sead::CriticalSection _8;
    /* 0x048 */ sead::FixedSafeString<32> _48;
    /* 0x080 */ sead::Matrix34f _80;
    /* 0x0b0 */ u8 _b0[0xbc - 0xb0];
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
    /* 0x1c8 */ u8 _1c8[0x1e0 - 0x1c8];
};
KSYS_CHECK_SIZE_NX150(Unk_7100e4e084, 0x1e0);

}  // namespace ksys::act
