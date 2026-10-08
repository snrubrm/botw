#pragma once

#include <basis/seadTypes.h>
#include <container/seadBuffer.h>
#include <math/seadMatrix.h>
#include <prim/seadBitFlag.h>
#include "KingSystem/ActorSystem/actBaseProcLink.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::phys {
class CharacterController;
class Constraint;
class RagdollInstance;
class RigidBody;
}

namespace ksys::act {

class Unk_71024ef620;

// Placeholder name (vtable 0x71024ef4e8, only a trivial virtual dtor; methods in 0x7100eb2394-0x7100eb5900;
// created with `new(0x2b8)` by 0x7100eb16a0 (CSV ActorPhysics::x_8, called with the actor's phys::InstanceSet
// and Model by Player::prepareInit_). Stored in Player::_1870 (the object behind Player's slots
// m41 / m42 / m47 and getAttachedTargetActor). Holds the body's transform at +0xe0 (a second copy at +0x188).
// TODO: incomplete.
class Unk_71024ef4e8 {
public:
    // Placeholder: the object at `_b0` (a BaseProcLink of the attached actor lives at +0x158, a Constraint* at +8).
    struct AttachInfo {
        // 0x7100eb0d30 (out of line; defined in its own file so that the caller does not inline it).
        void sub_7100EB0D30();
        phys::RigidBody* getBody() const { return mBody; }

        u8 _0[8];
        phys::Constraint* mConstraint;
        u8 _10[0x48 - 0x10];
        /* 0x48 */ u8 _48;  // bit 1: _c0 is valid (read inline by Unk_71003ffbf0::sub_71003FFD3C)
        /* 0x49 */ u8 _49;  // bit 1 tested by sub_7100926AC4 (camera)
        u8 _4a[0x50 - 0x4a];
        /* 0x50 */ phys::RigidBody* mBody;
        u8 _58[0xc0 - 0x58];
        /* 0xc0 */ phys::RigidBody* _c0;
        u8 _c8[0x140 - 0xc8];
        /* 0x140 */ sead::Vector3f _140;
        u8 _14c[0x158 - 0x14c];
        BaseProcLink mTargetLink;
    };

    // Placeholder (object at `_c8`, size unknown): only the members Player::sub_710087CF54 reads are modelled.
    struct Unk2 {
        u8 _0[0x1a8];
        /* 0x1a8 */ sead::Vector3f _1a8;
        u8 _1b4[0x1f0 - 0x1b4];
        /* 0x1f0 */ u32 _1f0;  // tested with 0x1002 by Player::sub_710087CF54
    };

    virtual ~Unk_71024ef4e8() = default;

    // 0x7100eb480c: the centre of mass of `_20` in world space.
    void sub_7100EB480C(sead::Vector3f* out) const;
    // 0x7100eb2448: `if (mAttachInfo) mAttachInfo->sub_7100EB0D30()` (calls Constraint::sub_7100F6A074 on the attach constraint).
    void sub_7100EB2448();
    // 0x7100eb57f0: stores `mtx` into _e0 / _188 (resets the scale at _1b8 to 1) and updates the flags at _110.
    void sub_7100EB57F0(const sead::Matrix34f& mtx);

    // 0x7100eb2394: applies the buoyancy scale, the centre of mass and the masses to the bodies. 0x7100eb4814 / 0x7100eb4928 (declared only; 276 / 1892 bytes).
    void sub_7100EB2394();
    void sub_7100EB4814(int type, int a2, f32 f);
    void sub_7100EB4928(int type, int a2, const sead::Vector3f& a, const sead::Vector3f& b, bool flag,
                        f32 f);

    // Small flag / state setters called by the Player actions (0x7100eb51b0-0x7100eb56e8). Placeholder
    // names; the comments describe the effect on `_110`.
    void sub_7100EB51B0(const sead::Vector3f& a, const sead::Vector3f& b, int c);  // sets 0x40
    void sub_7100EB51E0();  // removes the ragdoll body / constraint from the world, resets the controller
    void sub_7100EB523C(const sead::Vector3f& a, const sead::Vector3f& b);  // stores `_114` / `_120`
    void sub_7100EB5270(int a);  // sub_7100EB4928(1, ...), sets 0x300
    void sub_7100EB52BC(int a);  // sub_7100EB4928(5, ...), sets 0x300
    void sub_7100EB5308(bool a, int b, f32 f);
    void sub_7100EB538C(int a, f32 f);  // sets 0x1000000
    void sub_7100EB5410();
    void sub_7100EB548C();
    void sub_7100EB54D8();  // sets the contact layer of every ragdoll body to EntityRagdoll
    void sub_7100EB5550();  // sets 0x4
    void sub_7100EB5560();
    void sub_7100EB5634();  // sets 0x8
    void sub_7100EB5644();  // resets 0x8
    void sub_7100EB5654();  // sets 0x20
    void sub_7100EB5664(bool a, const sead::Vector3f* v);
    void sub_7100EB56B4(bool a);
    void sub_7100EB56E8();

    /* 0x008 */ u8 _8[8];
    /* 0x010 */ phys::CharacterController* _10;
    /* 0x018 */ phys::RagdollInstance* _18;
    /* 0x020 */ phys::RigidBody* _20;
    u8 _28[0x38 - 0x28];
    /* 0x038 */ phys::Constraint* _38;
    u8 _40[0x48 - 0x40];
    /* 0x048 */ f32 _48;  // water buoyancy scale (also copied to _144)
    /* 0x04c */ sead::Vector3f _4c;  // centre of mass in local space
    u8 _58[4];
    /* 0x05c */ f32 _5c;  // mass
    /* 0x060 */ sead::Buffer<f32> _60;  // the mass of each ragdoll body
    u8 _70[0xb0 - 0x70];
    /* 0x0b0 */ AttachInfo* mAttachInfo;
    u8 _b8[8];
    /* 0x0c0 */ Unk_71024ef620* _c0;
    /* 0x0c8 */ Unk2* _c8;
    u8 _d0[0xe0 - 0xd0];
    /* 0x0e0 */ sead::Matrix34f mMtx;
        /* 0x110 */ sead::BitFlag32 _110;  // flags
    /* 0x114 */ sead::Vector3f _114;
    /* 0x120 */ sead::Vector3f _120;
    u8 _12c[4];
    /* 0x130 */ u32 _130;
    u8 _134[0x144 - 0x134];
    /* 0x144 */ f32 _144;
    /* 0x148 */ u64 _148;
    /* 0x150 */ u32 _150;
    u8 _154[0x188 - 0x154];
    /* 0x188 */ sead::Matrix34f _188;
    /* 0x1b8 */ f32 _1b8;
    /* 0x1bc */ f32 _1bc;
    /* 0x1c0 */ f32 _1c0;
    u8 _1c4[0x1e8 - 0x1c4];
    /* 0x1e8 */ u32 _1e8;
    /* 0x1ec */ sead::Vector3f _1ec;
    /* 0x1f8 */ u32 _1f8;
    u8 _1fc[0x200 - 0x1fc];
    /* 0x200 */ sead::Vector3f _200;
    u8 _20c[0x2b8 - 0x20c];
};
KSYS_CHECK_SIZE_NX150(Unk_71024ef4e8, 0x2b8);

}  // namespace ksys::act
