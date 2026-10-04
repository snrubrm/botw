#pragma once

#include <math/seadVector.h>
#include <prim/seadBitFlag.h>
#include <prim/seadRuntimeTypeInfo.h>
#include "KingSystem/Utils/Types.h"

namespace ksys::phys {
class CharacterController;
class RigidBody;
}  // namespace ksys::phys

namespace ksys::as {
class ASList;
}

namespace ksys::act {

class Actor;

// Placeholder name (vtable 0x71024ef620, a sead RTTI base class; size 0x90; created by 0x7100eba300 with
// the actor's phys::InstanceSet, stored in Unk_71024ef4e8::_c0 by 0x7100eb16a0). The bodies and sound
// banks it looks up are named "Player" / "SurfingBody" / "Surfing": it is the surfing (shield surf / wake
// board) body of the player. The small members 0x7100eba130 - 0x7100ebb7b0 are used by PlayerWakeBoard*,
// PlayerShieldRideMove and GerudoQueenBattle.
// TODO: incomplete (only the functions the actions use are decompiled).
class Unk_71024ef620 {
    SEAD_RTTI_BASE(Unk_71024ef620)
public:
    virtual ~Unk_71024ef620();

    // 0x7100ebb518: stops the surfing (the rope the player holds goes to sleep and the body is removed from
    // the world; the character controller goes back to its default motion type).
    void sub_7100EBB518();
    // 0x7100ebb60c
    void sub_7100EBB60C();
    // 0x7100ebb624: keeps only the vertical component of the body's linear velocity.
    void sub_7100EBB624();

    // 0x7100eba9f0 (declared only): updates the surfing animation from the actor AS list.
    void sub_7100EBA9F0(as::ASList* as_list, bool flag);
    // 0x7100eba4c0 (declared only): starts the surfing body.
    void sub_7100EBA4C0();

    /* 0x08 */ Actor* _8 = nullptr;
    /* 0x10 */ phys::RigidBody* _10;
    /* 0x18 */ phys::CharacterController* _18;
    u8 _20[0x30 - 0x20];
    /* 0x30 */ u64 _30 = 0;
    u64 _38 = 0;
    /* 0x40 */ sead::Vector3f _40;
    /* 0x4c */ sead::Vector3f _4c;
    /* 0x58 */ f32 _58;
    /* 0x5c */ s32 _5c = -1;
    /* 0x60 */ sead::BitFlag16 _60;
    u8 _62[2];
    /* 0x64 */ f32 _64;
    /* 0x68 */ f32 _68;
    u8 _6c[0x90 - 0x6c];
};
KSYS_CHECK_SIZE_NX150(Unk_71024ef620, 0x90);

}  // namespace ksys::act
