#pragma once

#include <basis/seadTypes.h>
#include <gsys/gsysModelAccessKey.h>
#include <heap/seadHeap.h>
#include <math/seadMatrix.h>
#include <math/seadVector.h>
#include <prim/seadSafeString.h>
#include "Game/AI/aiUnk_71025b0578.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::act {

class Actor;

// Placeholder name (first function of its TU 0x71006ecc78-0x71006ee2fc; no CSV names): the ragdoll
// controller of a DynamicActor. Heap-allocated (0xd8 bytes) by DynamicActor::initField868 into
// DynamicActor::_868 and embedded in Horse at 0xf50 (the same inlined constructor), ~190 AI /
// action functions go through it (AnmToRagdollDie, Ragdoll, GetUpBase, Freeze, DrowningDeath, ...).
// It switches the actor's ragdoll instance on and off (`_c0` state: 0 = idle, 1 = blending in,
// 2 = blending out; `_c4` = blend frames; `_b8` = blend timer; `_c8` / `_cc` = rigid body group
// indices of the ragdoll config; `_d2` bit 0 = contact layer handling done, bit 6 = ...).
// All methods are declared only; names are placeholders (`sub_<ADDR>`), signatures come from the
// callers' argument setup.
class Unk_71006ecc78 {
public:
    // Opaque argument of sub_71006ED100 / sub_71006ED54C (a 0x70-byte request built by
    // DynamicActor::m69 from the actor's damage info: [+0x30] damage type, [+0x38..] ids,
    // [+0x48] / [+0x54] vectors, [+0x60] float, [+0x61] / [+0x62] / [+0x66] / [+0x67] / [+0x6b]
    // flags).
    struct Request {
        u8 _0[0x70];
    };

    explicit Unk_71006ecc78(Actor* actor) : mActor(actor) {}

    // Creates the 0xe8-byte sub-object `_8` on `heap` (and sets the ragdoll's gravity factor 1.25).
    bool sub_71006ECC78(sead::Heap* heap);
    // Removes the ragdoll from the world (immediately if it is in it) and deletes `_8`.
    void sub_71006ECD08();
    // Sets the contact layer (19 / 5) of the bodies of the ragdoll config's body list.
    void sub_71006ECD6C(bool enable);
    void sub_71006ECF0C();
    void sub_71006ED100(const Request* request);
    void sub_71006ED484();
    void sub_71006ED54C(const Request* request);
    bool sub_71006ED9EC();
    bool sub_71006EDA58();
    // Per-frame update (blend timer `_b8`, state `_c0`).
    void sub_71006EDA80();
    void sub_71006EDCB8();
    void sub_71006EDD5C(bool start);
    bool sub_71006EDDD4();
    // The transform of ragdoll bone `bone` (with the ground-height adjustment of the Y axis).
    void sub_71006EDE54(sead::Matrix34f* out, const sead::SafeString& bone);
    bool sub_71006EDF9C();
    void sub_71006EDFBC();
    void sub_71006EE018();
    bool sub_71006EE07C(sead::Matrix34f* out, const gsys::BoneAccessKey& key,
                        const sead::Vector3f& y_axis);
    // Accessors of `_8` (declared only).
    void sub_71006EE128(sead::Vector3f* out) const;
    f32 sub_71006EE148() const;
    bool sub_71006EE15C();
    bool sub_71006EE1A4();
    void sub_71006EE1F8(const sead::SafeString& bone);
    u8 sub_71006EE274() const;
    void sub_71006EE280(const sead::SafeString& name);
    void sub_71006EE2E8(f32 value);
    void sub_71006EE2FC();

    // The 0xe8-byte sub-object created by sub_71006ECC78 (ctor 0xe9d810, init 0xe9d8b0, dtor
    // 0xe9dac8); only the fields its accessors read are declared.
    struct Unk_8 {
        u8 _0[0xc4];
        sead::Vector3f _c4;
        u8 _d0[4];
        f32 _d4;
        u8 _d8[4];
        u8 _dc;
        u8 _dd[0xe8 - 0xdd];
    };
    static_assert(sizeof(Unk_8) == 0xe8);

    /* 0x00 */ Actor* mActor;
    /* 0x08 */ Unk_8* _8 = nullptr;
    /* 0x10 */ Unk_7100716408 _10;
    /* 0xb8 */ f32 _b8 = 0;
    /* 0xbc */ s32 _bc = 4;
    /* 0xc0 */ s32 _c0 = -1;
    /* 0xc4 */ s32 _c4 = 0;
    /* 0xc8 */ s32 _c8 = -1;
    /* 0xcc */ s32 _cc = -1;
    /* 0xd0 */ u8 _d0 = 0;
    /* 0xd1 */ u8 _d1 = 0;
    /* 0xd2 */ u8 _d2 = 0;
};
KSYS_CHECK_SIZE_NX150(Unk_71006ecc78, 0xd8);

}  // namespace ksys::act
