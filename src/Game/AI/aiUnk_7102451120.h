#pragma once

#include <basis/seadTypes.h>
#include <math/seadMathCalcCommon.h>
#include "KingSystem/Physics/System/physContactPointInfo.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::act {
class Actor;
}  // namespace ksys::act

// Unnamed contact callback (vtable 0x7102451120; invoke 0x7100721288, clone / isNoDummy are the
// IDelegate2R defaults) embedded in SandwormRoot (_278). Its TU (0x7100720000-0x7100721400) is
// a helper TU used by the Sandworm AIs. Placeholder name = vtable address.
class Unk_7102451120 : public ksys::phys::ContactPointInfo::ContactCallback {
public:
    // Contacts with dynamic, non-fixed bodies whose mass is at most _8 are kept.
    bool invoke(ksys::phys::ContactPointInfo::ShouldDisableContact* disable,
                const ksys::phys::ContactPointInfo::Event& event) override;

    f32 _8 = sead::Mathf::infinity();  // max mass
};
KSYS_CHECK_SIZE_NX150(Unk_7102451120, 0x10);

// Free helpers in the same TU.
// 0x7100720140: sets Enemy::_e90 = 1 if the actor is an Enemy.
void sub_7100720140(ksys::act::Actor* actor);
// 0x7100720a70: forwards the actor to a method (0x710065d5d4) of the object at +0x450 of a singleton
// (GOT 0x7102579100).
void sub_7100720A70(ksys::act::Actor* actor);
