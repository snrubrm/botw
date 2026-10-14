#pragma once

#include <basis/seadTypes.h>
#include "Game/gameUnkRttiClasses.h"
#include "KingSystem/Physics/physMaterialMask.h"
#include <math/seadVector.h>
#include <xlink2/xlink2HandleSLink.h>

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
    u32 _70 = 0;
    f32 _74 = 0;
    u16 _78 = 0;
    // 0x710105e114: values below 2 skip the chemical sound spatial flags.
    u16 _7a;
    u8 _7c[0x8b - 0x7c];
    u8 _8b;
    u8 _8c[0x8f - 0x8c];
    // IgnitedThrown::sub_71001B5C4C fades its "Thrown" sound while this is >= 1.
    s8 _8f;
    u8 _90[0xa8 - 0x90];
};
KSYS_CHECK_SIZE_NX150(ActorUnk6b8, 0xa8);

}  // namespace ksys::act
