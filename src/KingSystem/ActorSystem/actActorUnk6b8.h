#pragma once

#include <basis/seadTypes.h>
#include "Game/gameUnkRttiClasses.h"
#include "KingSystem/Physics/physMaterialMask.h"

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

    // The base ends at +0x12; this member reuses its tail padding.
    u8 _14[0x58 - 0x14];
    phys::MaterialMask _58;
    u8 _70[0x7a - 0x70];
    // 0x710105e114: values below 2 skip the chemical sound spatial flags.
    u16 _7a;
    u8 _7c[0x8b - 0x7c];
    u8 _8b;
    u8 _8c[0xa8 - 0x8c];
};
KSYS_CHECK_SIZE_NX150(ActorUnk6b8, 0xa8);

}  // namespace ksys::act
