#pragma once

#include <hostio/seadHostIONode.h>
#include <math/seadVector.h>
#include <prim/seadBitFlag.h>
#include "KingSystem/System/VFRValue.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::phys {
class RayCastForRequest;
}

namespace ksys::act {

// 2026-10-07: ActorX6A0's member at 0x10; ctor 0x7101265a6c, vtable 0x7102517c50.
class Unk_7101265a6c : public sead::hostio::Node {
public:
    Unk_7101265a6c();
    virtual ~Unk_7101265a6c();

    s32 _8 = 0;
    f32 _c = 30.0f;
    f32 _10 = 0.0f;
    f32 _14 = 0.0f;
    sead::Vector3f _18 = sead::Vector3f::ex;
    bool _24 = false;
};
KSYS_CHECK_SIZE_NX150(Unk_7101265a6c, 0x28);

// CSV ActorX6A0: Actor's component at 0x6a0, allocated with 0x80 bytes at 0x71011d09dc.
// 2026-10-07: constructor 0x71010f209c establishes the flags at 0x8 / 0xa.
class ActorX6A0 : public sead::hostio::Node {
public:
    ActorX6A0();
    virtual ~ActorX6A0();
    void sub_71010F21C4();
    void sub_71010F21E0();
    void* sub_71010F2848();

    sead::BitFlag16 _8;
    sead::BitFlag8 _a;
    Unk_7101265a6c _10;
    phys::RayCastForRequest* _38 = nullptr;
    s32 _40;
    sead::Vector3f _44;
    VFRValue _50;
    sead::Vector3f _5c;
    s32 _68 = 0;
    f32 _6c;
    f32 _70;
    f32 _74;
    u8 _78 = 0;
    u8 _79;
    bool _7a;
    bool _7b;
};
KSYS_CHECK_SIZE_NX150(ActorX6A0, 0x80);

}  // namespace ksys::act
