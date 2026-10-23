#pragma once

#include <basis/seadTypes.h>
#include <prim/seadEnum.h>
#include "Game/gameUnkRttiClasses.h"
#include "KingSystem/Physics/physMaterialMask.h"
#include <math/seadVector.h>
#include <xlink2/xlink2HandleSLink.h>

namespace ksys::phys {
class RigidBody;
}

namespace ksys::act {

// Placeholder name: the object at Actor::_6b8. Sound emission checks its counter at +0x7a;
// FixedMagneStick::calc_ writes its byte at +0x8b.
struct ActorUnk6b8 : Unk_71024efd58 {
    SEAD_RTTI_OVERRIDE(ActorUnk6b8, Unk_71024efd58)
public:
    explicit ActorUnk6b8(const InitArg& arg);
    ~ActorUnk6b8() override;

    void m5() override;
    void m8() override;
    void m9() override;
    void m10() override;
    void sub_7100EBBCB8(bool fixed);
    // 0x7100ebbce4 (placeholder name): sets or clears flag 0x100 (TrolleyOnRail::calc_ sets it).
    void sub_7100EBBCE4(bool on);
    // 0x7100ebbd04 (placeholder name): sets the byte at +0x90 to 10.
    void sub_7100EBBD04();

    // 0x7100ebe92c (declared only; placeholder name): emits the extra slide/land reaction sound
    // (asset "ReactionSlideAdditional") with the extra volume/pitch scales.
    void sub_7100EBE92C(f32 a, f32 b, f32 c, f32 d, Actor* actor, const phys::MaterialMask& mask);
    // 0x7100ebdcb0 (declared in this class's TU): the slide reaction entry; builds a
    // ReactionSetting and passes it to Reaction::Unk1::sub_7100EC72A0.
    void sub_7100EBDCB0(f32 a, f32 b, f32 c, Actor* actor, const phys::MaterialMask* mask1,
                        const phys::MaterialMask* mask2);
    // 0x7100ebd7dc: the land reaction entry. The original passes the contact mask as EBE328's
    // fifth argument (in x3); the call sites do not set the fourth, so it is omitted here.
    void sub_7100EBD7DC(const sead::Vector3f& velocity, const sead::Vector3f& normal,
                        phys::RigidBody* body, phys::RigidBody* other_body,
                        const phys::MaterialMask* mask1, const phys::MaterialMask* mask2);
    // 0x7100ebe328: emits the additional land reaction sound (ReactionLandAdditional).
    void sub_7100EBE328(f32 a, f32 b, Actor* actor, const phys::MaterialMask* mask);

    // Two sound handles that are faded together.
    struct SoundHandles {
        // 0x7100ebed98
        void fade(s32 frame);

        xlink2::HandleSLink _0;
        xlink2::HandleSLink _10;
    };

    // The base ends at +0x12; this member reuses its tail padding.
    u8 _12[0x14 - 0x12];
    u32 _14 = 0;
    u32 _18 = 0;
    SoundHandles _20;
    sead::Vector3f _40 = sead::Vector3f::zero;
    sead::Vector3f _4c = sead::Vector3f::zero;
    phys::MaterialMask _58;
    f32 _70 = 0;
    f32 _74 = 0;
    u16 _78 = 0;
    // 0x710105e114: values below 2 skip the chemical sound spatial flags.
    u16 _7a = 0;
    u32 _7c = 0;
    u32 _80 = 0;
    u32 _84 = 0;
    u16 _88 = 0;  // flags
    u8 _8a = 0;   // flags
    s8 _8b = 0;
    s8 _8c = 0;
    s8 _8d = 0;
    s8 _8e = 0;
    // IgnitedThrown::sub_71001B5C4C fades its "Thrown" sound while this is >= 1.
    s8 _8f = 0;
    s8 _90 = 0;
    u32 _94 = 0;
    u32 _98 = 0;
    u32 _9c = 0;
    f32 _a0 = 0;
    f32 _a4 = 0;
};
KSYS_CHECK_SIZE_NX150(ActorUnk6b8, 0xa8);

// The reaction size class of a sound setting: "Auto" and "None" followed by the size / sound
// material pairs (the text of 0x7100ebf054's 37-entry table at 0x71024...).
SEAD_ENUM(ReactionSize, Auto, None, TinyBody, TinyMetal, TinyStone, TinyWater, TinyWood, SmallBody,
          SmallMetal, SmallStone, SmallWater, SmallWood, HalfBody, HalfMetal, HalfStone, HalfWater,
          HalfWood, NormalBody, NormalMetal, NormalStone, NormalWater, NormalWood, DoubleBody,
          DoubleMetal, DoubleStone, DoubleWater, DoubleWood, GiantBody, GiantMetal, GiantStone,
          GiantWater, GiantWood, HugeBody, HugeMetal, HugeStone, HugeWater, HugeWood)

// The reaction sound setting built on the stack by the slide/land reaction handlers
// (0x7100ebcd48 / 0x7100ebdcb0) and passed to Reaction::Unk1's sound emitters. Size 0x68; the
// material masks and the handle pointer are read by 0x7100ec72a0, the two words at +0 and +4
// select the event-name prefix and the size class in 0x7100ec7468.
struct ReactionSetting {
    ReactionSetting() = default;

    /* 0x00 */ s32 kind = 0;
    /* 0x04 */ ReactionSize size = ReactionSize::Auto;
    /* 0x08 */ f32 speed = 1.0f;
    /* 0x0c */ f32 volume = 1.0f;
    /* 0x10 */ f32 pitch = 1.0f;
    /* 0x14 */ f32 _14 = 50.0f;
    /* 0x18 */ f32 _18 = 1.0f;
    /* 0x1c */ f32 _1c = 0.0f;
    /* 0x20 */ u8 _20 = 0;
    /* 0x24 */ f32 _24 = 0.0f;
    /* 0x28 */ phys::MaterialMask mask1;
    /* 0x40 */ phys::MaterialMask mask2;
    /* 0x58 */ xlink2::HandleSLink* other = nullptr;
    /* 0x60 */ const char* name = nullptr;
};
static_assert(offsetof(ReactionSetting, mask1) == 0x28);
static_assert(offsetof(ReactionSetting, mask2) == 0x40);
static_assert(offsetof(ReactionSetting, other) == 0x58);
static_assert(offsetof(ReactionSetting, name) == 0x60);

}  // namespace ksys::act
