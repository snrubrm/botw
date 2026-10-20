#pragma once

#include <basis/seadTypes.h>
#include <container/seadBuffer.h>
#include <container/seadRingBuffer.h>
#include <math/seadMatrix.h>
#include <prim/seadBitFlag.h>
#include "KingSystem/ActorSystem/actBaseProcLink.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::phys {
class CharacterController;
class Constraint;
class InstanceSet;
class RagdollInstance;
class RigidBody;
class ShapeCast;
class MaterialMask;
class ContactLayer;
}

namespace ksys::act {

class PlayerLink;
class Unk_71024ef620;

// Placeholder name (vtable 0x71024ef4e8, only a trivial virtual dtor; methods in 0x7100eb2394-0x7100eb5900;
// created with `new(0x2b8)` by 0x7100eb16a0 (CSV ActorPhysics::x_8, called with the actor's phys::InstanceSet
// and Model by Player::prepareInit_). Stored in Player::_1870 (the object behind Player's slots
// m41 / m42 / m47 and getAttachedTargetActor). Holds the body's transform at +0xe0 (a second copy at +0x188).
// TODO: incomplete.
class Unk_71024ef4e8 {
public:
    // Seven 0x28-byte records initialized by EB5D34 and selected by EB4814.
    struct AttachConfig {
        const char* name;
        sead::Vector3f inertia;
        f32 _14;
        f32 linear_damping;
        f32 angular_damping;
        f32 _20;
        f32 _24;
    };
    // Placeholder: the object at `_b0` (a BaseProcLink of the attached actor lives at +0x158, a Constraint* at +8).
    struct AttachInfo {
        // 0x7100eb0d30 (out of line; defined in its own file so that the caller does not inline it).
        void sub_7100EB0D30();
        phys::RigidBody* getBody() const { return mBody; }

        u8 _0[8];
        phys::Constraint* mConstraint;
        u8 _10[0x48 - 0x10];
        // Flags: bit 1: _c0 is valid (read inline by Unk_71003ffbf0::sub_71003FFD3C); bit 9 tested by
        // sub_7100926AC4 (camera); bits 1 / 7 by Unk_71024ef4e8::sub_7100EB5784 (a 32-bit load).
        /* 0x48 */ u32 _48;
        u8 _4c[0x50 - 0x4c];
        /* 0x50 */ phys::RigidBody* mBody;
        u8 _58[0xc0 - 0x58];
        /* 0xc0 */ phys::RigidBody* _c0;
        u8 _c8[0x138 - 0xc8];
        // Attachment state, written by 0x7100eac434 and reset by 0x7100eac3e0.
        /* 0x138 */ u32 _138;
        u8 _13c[0x140 - 0x13c];
        /* 0x140 */ sead::Vector3f _140;
        u8 _14c[0x158 - 0x14c];
        BaseProcLink mTargetLink;
        u8 _168[0x180 - 0x168];
        /* 0x180 */ sead::Vector3f _180;  // velocity of the attachment (Player::getStatusEffectSpeed)
    };

    // Placeholder: the object at `_b8` (only the flag byte at +0x74 that sub_7100EB5784 tests is modeled).
    struct Unk3 {
        u8 _0[0x74];
        /* 0x74 */ u8 _74;
        u8 _75[0xd8 - 0x75];
        // Passed as the ground position by Unk_710245a028::m2 when bit 1 of _74 is set.
        /* 0xd8 */ sead::Vector3f _d8;
    };

    // EA7300 constructs this 0x210-byte controller contact solver; EA79DC frees its buffers.
    struct Unk2 {
        struct ContactRecord {
            sead::Vector3f position = sead::Vector3f::zero;
            sead::Vector3f normal = sead::Vector3f::ey;
            u8 _18 = 0;
            u8 _19 = 1;
            u8 _1a = 0;
            u8 _1b = 0;
        };
        static_assert(sizeof(ContactRecord) == 0x1c);
        // EA82DC builds this query state and passes it to the contact / retry helpers.
        struct QueryArgs {
            sead::Vector3f start;
            sead::Vector3f end;
            sead::Vector3f _18;
            sead::Vector3f _24;
            sead::Vector3f _30;
            sead::Vector3f _3c;
            u32 _48;
            bool _4c;
        };
        static_assert(sizeof(QueryArgs) == 0x50);
        // EA86A8 fits the projected contact points selected by an index ring.
        struct Fit {
            sead::Vector2f eigenvalues{0, 0};
            f32 smallest = 0;
            f32 slope = 0;
            f32 intercept = 0;
            s32 kind = 4;
            f32 min_x = 10;
            f32 min_y = 0;
            f32 max_y = 0;
            f32 range_y = 0;
        };
        static_assert(sizeof(Fit) == 0x28);

        explicit Unk2(phys::CharacterController* controller);
        virtual ~Unk2();
        static Unk2* sub_7100EA7300(phys::CharacterController* controller, sead::Heap* heap);
        void sub_7100EA7350(sead::Heap* heap);
        void sub_7100EA79DC();
        void sub_7100EA8994();
        void sub_7100EAA6A0(QueryArgs& args, phys::ShapeCast& cast, s32 index,
                            const sead::Vector3f& direction, bool check_material);
        bool sub_7100EA86A8(Fit* out, const sead::RingBuffer<s32>& indices);
        ContactRecord* sub_7100EAA344(QueryArgs& args, phys::ShapeCast& cast, s32 index,
                                     bool check_material, bool special);
        void sub_7100EAB618(const QueryArgs& args, s32 index, const sead::Vector3f& position,
                            const sead::Vector3f& normal, const phys::MaterialMask& material,
                            phys::ContactLayer layer, bool check_material, bool special);
        // EAB818: writes the target position when available; Player 87F29C consumes all three floats.
        bool sub_7100EAB818(sead::Vector3f* out) const;
        // EAB7C0: writes _1c0 while _1f0 bit 5 is set and _1c0 is not zero (Player 0x7100883bc4 tests its y).
        bool sub_7100EAB7C0(sead::Vector3f* out) const;

        /* 0x008 */ phys::CharacterController* mController;
        /* 0x010 */ f32 _10;
        /* 0x014 */ f32 _14;
        /* 0x018 */ u32 _18;
        /* 0x01c */ s32 _1c;
        /* 0x020 */ s32 _20;
        /* 0x024 */ f32 _24;
        /* 0x028 */ sead::Buffer<ContactRecord> mContactRecords;
        /* 0x038 */ sead::RingBuffer<s32> mContactIndices;
        /* 0x050 */ sead::Buffer<sead::Vector2f> mProjectedPoints;
        u8 _60[0xf8 - 0x60];
        /* 0x0f8 */ Fit _f8;
        /* 0x120 */ Fit _120;
        /* 0x148 */ sead::RingBuffer<s32> _148;
        /* 0x160 */ sead::RingBuffer<s32> _160;
        /* 0x178 */ sead::RingBuffer<s32> _178;
        /* 0x190 */ sead::Vector3f _190;
        u8 _19c[0x1a8 - 0x19c];
        /* 0x1a8 */ sead::Vector3f _1a8;
        u8 _1b4[0x1c0 - 0x1b4];
        /* 0x1c0 */ sead::Vector3f _1c0;
        u8 _1cc[0x1d8 - 0x1cc];
        /* 0x1d8 */ sead::Vector3f _1d8;  // the target position (valid while _1f0 bit 5 is set)
        u8 _1e4[0x1f0 - 0x1e4];
        /* 0x1f0 */ u32 _1f0;  // tested with 0x1002 by Player::sub_710087CF54
        u8 _1f4[0x210 - 0x1f4];
    };
    static_assert(sizeof(Unk2) == 0x210);
    static_assert(offsetof(Unk2, mContactRecords) == 0x28);
    static_assert(offsetof(Unk2, mProjectedPoints) == 0x50);
    static_assert(offsetof(Unk2, _190) == 0x190);

    virtual ~Unk_71024ef4e8() = default;

    // 0x7100eb480c: the centre of mass of `_20` in world space.
    void sub_7100EB480C(sead::Vector3f* out) const;
    // 0x7100eb2448: `if (mAttachInfo) mAttachInfo->sub_7100EB0D30()` (calls Constraint::sub_7100F6A074 on the attach constraint).
    void sub_7100EB2448();
    void sub_7100EB4680();
    // 0x7100eb5784 (placeholder name): flag query over _110, the attach info flags, _b8->_74 and _c0->_60.
    bool sub_7100EB5784() const;
    // 0x7100eb57f0: stores `mtx` into _e0 / _188 (resets the scale at _1b8 to 1) and updates the flags at _110.
    void sub_7100EB57F0(const sead::Matrix34f& mtx);
    // 0x7100eb58a4 (declared only; unnamed in the CSV): unless _110 bit 0 is set and not game over, stores the link,
    // matrix, value and flag (_270 - _2ac), sets _2b0 and submits a worker request (Player::m74).
    void sub_7100EB58A4(f32 value, PlayerLink* link, const sead::Matrix34f& mtx, bool flag);

    // 0x7100eb2394: applies the buoyancy scale, the centre of mass and the masses to the bodies. 0x7100eb4814 / 0x7100eb4928 (declared only; 276 / 1892 bytes).
    void sub_7100EB2394();
    void sub_7100EB4814(int type, int a2, f32 f);
    void sub_7100EB4928(int type, int a2, const sead::Vector3f& a, const sead::Vector3f& b, bool flag,
                        f32 f);

    // 0x7100eb5950: body position plus an offset along its local Y axis.
    void sub_7100EB5950(sead::Vector3f* out, phys::RigidBody* body, f32 height);
    // 0x7100eb59e8: 0 blocked/invalid, 1 clear after the ground-normal retry, 2 farther than 3.
    u32 sub_7100EB59E8(const sead::Vector3f& target, phys::CharacterController* controller,
                     phys::RigidBody* body, f32 height);

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
    // 0x7100eb584c (placeholder name): the attach axis: ey when the attach info flags (low two
    // bits) are 2, otherwise Unk2::_190.
    void getAttachAxisMaybe(sead::Vector3f* out) const;
    // 0x7100eb508c (placeholder name): sets the contact layer of body _80 and of the bodies listed
    // in _90 / _a0 to EntityNoHit when `no_hit` is set, EntityRagdoll otherwise.
    void setSelectedBodiesNoHitMaybe(bool no_hit);

    /* 0x008 */ phys::InstanceSet* _8;
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
    u8 _70[0x80 - 0x70];
    /* 0x080 */ s32 _80;
    u8 _84[0x88 - 0x84];
    /* 0x088 */ s32 _88;
    u8 _8c[4];
    /* 0x090 */ u32* _90;
    /* 0x098 */ s32 _98;
    u8 _9c[4];
    /* 0x0a0 */ u32* _a0;
    u8 _a8[0xb0 - 0xa8];
    /* 0x0b0 */ AttachInfo* mAttachInfo;
    /* 0x0b8 */ Unk3* _b8;
    /* 0x0c0 */ Unk_71024ef620* _c0;
    /* 0x0c8 */ Unk2* _c8;
    u8 _d0[0xe0 - 0xd0];
    /* 0x0e0 */ sead::Matrix34f mMtx;
        /* 0x110 */ sead::BitFlag32 _110;  // flags
    /* 0x114 */ sead::Vector3f _114;
    /* 0x120 */ sead::Vector3f _120;
    /* 0x12c */ f32 _12c;
    /* 0x130 */ u32 _130;
    u8 _134[0x144 - 0x134];
    /* 0x144 */ f32 _144;
    /* 0x148 */ u64 _148;
    /* 0x150 */ u32 _150;
    /* 0x154 */ f32 _154;
    /* 0x158 */ f32 _158;
    /* 0x15c */ f32 _15c;
    u8 _160[0x16c - 0x160];
    /* 0x16c */ u8 _16c;  // Unk_710245a028::m2 counts a ground hit when set (player flag bit 19)
    u8 _16d[0x188 - 0x16d];
    /* 0x188 */ sead::Matrix34f _188;
    /* 0x1b8 */ f32 _1b8;
    /* 0x1bc */ f32 _1bc;
    /* 0x1c0 */ f32 _1c0;
    u8 _1c4[4];
    /* 0x1c8 */ AttachConfig* _1c8;
    u8 _1d0[0x1e8 - 0x1d0];
    /* 0x1e8 */ u32 _1e8;
    /* 0x1ec */ sead::Vector3f _1ec;
    /* 0x1f8 */ u32 _1f8;
    u8 _1fc[0x200 - 0x1fc];
    /* 0x200 */ sead::Vector3f _200;
    u8 _20c[0x2b8 - 0x20c];
};
KSYS_CHECK_SIZE_NX150(Unk_71024ef4e8, 0x2b8);

}  // namespace ksys::act
