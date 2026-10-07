#pragma once

#include <basis/seadTypes.h>
#include <math/seadBoundBox.h>
#include <math/seadMatrix.h>
#include <math/seadVector.h>
#include <prim/seadSafeString.h>
#include <prim/seadBitFlag.h>
#include "Game/AI/aiUnk_71025b0578.h"
#include "KingSystem/Utils/Types.h"

namespace sead {
class Heap;
}

namespace gsys {
struct BoneAccessKey;
}

namespace ksys::act {

class Actor;
// Placeholder name (the ragdoll controller created by Unk_71006ecc78::sub_71006ECC78; size unknown):
// only the vector at +0xc4 is modelled so far.
class Unk_7100e9d810 {
public:
    /* 0x00 */ u8 _0[0xc4];
    /* 0xc4 */ sead::Vector3f _c4;
};

// Placeholder name (functions at 0x71006ecc78-0x71006ee3e0; ctor inlined into DynamicActor::initField868
// 0x71006dc5d4): the ragdoll handler of a DynamicActor (DynamicActor::_868, size 0xd8). Only the members
// needed so far are named; the functions are the ones called by AI actions.
class Unk_71006ecc78 {
public:
    // Inlined into DynamicActor::initField868 (0x71006dc5d4) and Horse's constructor (embedded at 0xf50).
    explicit Unk_71006ecc78(Actor* actor) : mActor(actor) {}

    // 0x71006ecc78 (declaration only): creates `_8` in `heap` and applies the ragdoll gravity factor.
    bool sub_71006ECC78(sead::Heap* heap);
    // 0x71006ecd08 (declaration only): removes the ragdoll and releases its controller.
    void sub_71006ECD08();
    // 0x71006ecd6c (declaration only): sets the contact layer of the actor's rigid bodies.
    void sub_71006ECD6C(bool a1);

    // 0x71006ed484
    void sub_71006ED484();
    // 0x71006ee07c (declared only; lane5 s5, placeholder name; Tumble::sub_710029D1BC): the transform of the bone `key`
    // (with `offset`) of the ragdoll.
    bool sub_71006EE07C(sead::Matrix34f* out, const gsys::BoneAccessKey& key, const sead::Vector3f& offset);
    // 0x71006eda58: removes the actor's ragdoll from the world (true without a ragdoll).
    bool sub_71006EDA58();
    // 0x71006ed9ec: whether the ragdoll can be switched on (world state 0 and the controller selection
    // `_c8` / `_cc` is not already active).
    bool sub_71006ED9EC() const;
    // 0x71006edcb8 / 0x71006edd5c
    void sub_71006EDCB8();
    void sub_71006EDD5C();
    // 0x71006eddd4: as sub_71006ED9EC but also requires `_8` and a second world state check.
    bool sub_71006EDDD4() const;
    // 0x71006edf9c: whether the actor's ragdoll has contact points.
    bool sub_71006EDF9C() const;
    // 0x71006edfbc / 0x71006ee018: enables / disables the player contact layer of the ragdoll.
    void sub_71006EDFBC();
    void sub_71006EE018();
    // 0x71006ede54 (declared only): the transform of the ragdoll's root bone `name` (or the one its
    // controller follows) in world space.
    void sub_71006EDE54(sead::Matrix34f* out, const sead::SafeString& name);
    // 0x71006ee1f8 (declared only): feeds the position of the ragdoll bone `name` to the vibration check
    // embedded at +0x10.
    void sub_71006EE1F8(const sead::SafeString& name);
    // 0x71006ee128: copies the vector at _8->_c4.
    void sub_71006EE128(sead::Vector3f* out) const;
    // 0x71006ee15c / 0x71006ee1a4
    bool sub_71006EE15C() const;
    bool sub_71006EE1A4() const;
    // 0x71006ee280: `_c8` = the physics controller index of the rigid body set `name` (RagdollSmallDamageIdxChanger).
    void sub_71006EE280(const sead::SafeString& name);
    // 0x71006ee2e8 / 0x71006ee2fc: friction scale of the actor's physics bodies (the latter 1.0).
    void sub_71006EE2E8(f32 scale);
    void sub_71006EE2FC();

    /* 0x00 */ Actor* mActor;
    /* 0x08 */ Unk_7100e9d810* _8 = nullptr;
    // 2026-10-07: 0x71006ee1f8 passes +0x10 to the position vibration checker;
    // its 0xa8-byte data maps every existing +0x88..+0xb8 counter and bound field.
    /* 0x10 */ Unk_7100716408 _10;
    /* 0xb8 */ f32 _b8 = 0.0f;
    /* 0xbc */ s32 _bc = 4;
    /* 0xc0 */ s32 _c0 = -1;
    /* 0xc4 */ s32 _c4 = 0;
    /* 0xc8 */ s32 _c8 = -1;
    /* 0xcc */ s32 _cc = -1;
    /* 0xd0 */ u8 _d0 = 0;
    /* 0xd1 */ bool _d1 = false;
    /* 0xd2 */ sead::BitFlag8 _d2;
};
KSYS_CHECK_SIZE_NX150(Unk_71006ecc78, 0xd8);

}  // namespace ksys::act
