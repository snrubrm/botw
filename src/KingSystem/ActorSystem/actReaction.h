#pragma once

#include <basis/seadTypes.h>
#include <cstddef>
#include <math/seadMatrix.h>
#include <math/seadVector.h>
#include <prim/seadSafeString.h>
#include <xlink2/xlink2HandleSLink.h>

#include "KingSystem/Physics/System/physUserTag.h"

namespace xlink2 {
class HandleELink;
}

namespace ksys::phys {
class MaterialMask;
}

namespace ksys::xlink {
class XLink;
}

struct DamageReactionRequest;

namespace ksys::act {
class Actor;
class BaseProcLink;
class Unk_71024f02a8;

// Placeholder name: an actor given either directly or through a proc link (the reaction code keeps one at
// +0xa8 of its request objects; 0x7100ec545c / 0x7101284954 read it). Accessors 0x7100ebf9e4..0x7100ebfad4.
struct Unk_7100ebf9e4 {
    xlink::XLink* getXLink() const;
    // Chemical::_c0 of the actor's chemical (0 if none).
    s32 getChemicalState() const;
    const sead::SafeString& getName() const;

    Actor* mActor;
    BaseProcLink* mLink;
};

// Partial declaration. Reaction::createInstance (0x7100ec0138) stores the
// singleton at 0x71026064c0; its 0x180-byte allocation and members remain unrecovered.
// Placeholder: the receiver at Reaction::_a0. 0x7101286868 emits the slanted water reaction
// (ReactionWaterOut / ReactionWaterOut_Slant assets) for a footstep; called by 0x7100ec241c.
class Unk_7101286868 {
public:
    void sub_7101286868(f32 speed, Actor* actor, const sead::Vector3f* pos,
                        const sead::Vector3f* dir, u64 size, u64 material, u64 flag);
    void sub_7101286BF8(xlink2::HandleELink* handle, ::DamageReactionRequest* request);
    u8 _0[0x38];
    // Fallback actor used when the request actor has no emitted effect.
    /* 0x38 */ Actor* _38;
};

class Reaction {
public:
    // Placeholder: the object at _a8 (class unknown). 0x7100ec66fc sets its _110 to 2; the actor
    // argument is unused. Called by OctarockOptionRoot::calc_ when the player touches the rock.
    struct Unk1 {
        void sub_7100EC66FC(Actor* actor);
        // Constant getters (0.7f / 7 / 5); placeholder names.
        f32 sub_7100EC877C() const;
        s32 sub_7100EC87A4() const;
        s8 sub_7100EC89BC() const;
        // 0x7100ec6dd0: queues `actor` for the reaction of the current core (0x710128810c); false when full.
        bool sub_7100EC6DD0(Actor* actor);
        // 0x7100ec6070: emits the GrassTrack effect and the xlink properties for `request`.
        void sub_7100EC6070(f32 value, ::DamageReactionRequest* request, bool flag);
        // 0x7100ec61f8: fills the receiver from `request` (position, link, xlink properties).
        void sub_7100EC61F8(::DamageReactionRequest* request);
        // 0x7100ec8f78: emits the water reaction asset for a footstep on `actor` (sets xlink
        // properties 4 / 6 / 0 / 9 or 10, 608 B, still U).
        void sub_7100EC8F78(f32 speed, Actor* actor, const sead::Vector3f* pos, u64 size,
                            u64 material, u64 flag);

        // Sound emission and property setup for the request source.
        void sub_7100EC539C(::DamageReactionRequest* request, xlink2::HandleSLink* handle,
                           const char* name);
        void sub_7100EC447C(Actor* actor, ::DamageReactionRequest* request,
                           xlink2::HandleSLink* handle, const char* name);
        void sub_7100EC56D8(xlink::XLink* xlink, ::DamageReactionRequest* request);
        void sub_7100EC5B64(const sead::Vector3f& position);
        bool sub_7100EC5C30(f32 speed, f32 value, Actor* actor, const sead::Vector3f& position);
        bool sub_7100EC5C40(f32 speed, f32 value, Actor* actor, const sead::Vector3f& position,
                           s32 size, u32 flags, const phys::MaterialMask* mask);

        u8 _0[8];
        /* 0x08 */ Actor* _8;
        /* 0x10 */ Actor* _10;
        u8 _18[8];
        /* 0x20 */ xlink2::HandleSLink mGrassCutHandle;
        u8 _30[0xe8 - 0x30];
        /* 0xe8 */ Unk_71024f02a8* mSLinkLimiter;
        u8 _f0[0x101 - 0xf0];
        // Player::m377 writes whether lower armor is Armor_Default_Lower; footstep assets use it.
        /* 0x101 */ bool mIsPlayerBarefoot;
        u8 _102[0x110 - 0x102];
        /* 0x110 */ s32 _110;
        u8 _114[4];
        /* 0x118 */ s32 _118;
        u8 _11c[4];
    };

    static Reaction* instance() { return sInstance; }
    // 0x7100ec10b8 (CSV __auto6): passes `request` on to the reaction targets when the instance's
    // +0xb0 flag is set (bits 2 / 1 of request->_c4 select 0x7101284954 / 0x7100ec313c); true.
    bool sub_7100EC10B8(::DamageReactionRequest* request);
    // 0x7100ec2980 / 0x7100ec299c / 0x7100ec29b8: forwarded to the receiver at _a8 while _b0 is set.
    bool sub_7100EC2980(Actor* actor);
    void sub_7100EC299C(f32 value, ::DamageReactionRequest* request, bool flag);
    void sub_7100EC29B8(::DamageReactionRequest* request);
    static Reaction* sInstance;
    // Surface raycast/XLink update called by GolemRootBase::calc_; declaration only.
    void sub_7100EC29D0(Actor* actor);
    // 0x7100ec2278 (placeholder name): size class 0-4 of the actor from the local AABB of its main body
    // (2 or 3 from the height alone without one). `is_long` (optional) is set when the body is longer than
    // 4.5 and much thinner in the other two directions.
    u32 sub_7100EC2278(Actor* actor, bool* is_long);
    // 0x7100ec2598: the moving water footstep reaction: casts 5 / 10 units along the velocity and
    // forwards the speed along the hit normal with flag 1.
    void sub_7100EC2598(Actor* actor);
    // 0x7100ec27fc: the water footstep reaction: casts down 5 / 10 units on the water layer and
    // forwards the hit position and normal to the two receivers with flag 2.
    void sub_7100EC27FC(Actor* actor);
    // 0x7100ec241c: the footstep reaction of `actor` on contact `info`: stores 15.0 in the footstep
    // timer, picks the material mask from the contact type and forwards the speed to the two receivers.
    void sub_7100EC241C(Actor* actor, phys::UserTag::Unk5* info);

    // EC04D0 stores an Actor cast from the released handle; EC0D20 deletes the same actor.
    // EC04D0 releases the first handle and dynamically casts it to Actor here.
    u8 _0[0x28];
    Actor* _28;
    Actor* _30;
    Actor* _38;
    u8 _40[0xa0 - 0x40];
    /* 0xa0 */ Unk_7101286868* _a0;
    /* 0xa8 */ Unk1* _a8;
    /* 0xb0 */ bool _b0;
};
static_assert(offsetof(Unk_7101286868, _38) == 0x38);
static_assert(offsetof(Reaction::Unk1, _8) == 0x8);
static_assert(offsetof(Reaction::Unk1, _10) == 0x10);
static_assert(offsetof(Reaction::Unk1, mGrassCutHandle) == 0x20);
static_assert(offsetof(Reaction::Unk1, mSLinkLimiter) == 0xe8);
static_assert(offsetof(Reaction::Unk1, mIsPlayerBarefoot) == 0x101);
static_assert(offsetof(Reaction::Unk1, _118) == 0x118);

// 0x7100ebfea8 (CSV unnamed; named by its address): builds the matrix of a footstep reaction
// request from the contact axis / up / position and copies `scale` into the three floats at
// 0x3c / 0x40 / 0x44.
void sub_7100EBFB5C(f32 scale, ::DamageReactionRequest* request, const sead::Vector3f& up,
                    const sead::Vector3f& position);
void sub_7100EBFD08(f32 scale, ::DamageReactionRequest* request, const sead::Vector3f& up,
                    const sead::Vector3f& position);
void sub_7100EBFEA8(f32 scale, ::DamageReactionRequest* request, const sead::Vector3f& axis,
                    const sead::Vector3f& up, const sead::Vector3f& pos);

}  // namespace ksys::act
