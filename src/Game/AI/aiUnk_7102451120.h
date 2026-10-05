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

// Unnamed contact callback (vtable 0x7102451148, same TU; invoke 0x71007212f0) embedded in
// PriestBossGiantEnemyRoot (_258): like Unk_7102451120, but non-dynamic bodies are kept only if they
// are EntityGround. Placeholder name = vtable address.
class Unk_7102451148 : public ksys::phys::ContactPointInfo::ContactCallback {
public:
    bool invoke(ksys::phys::ContactPointInfo::ShouldDisableContact* disable,
                const ksys::phys::ContactPointInfo::Event& event) override;

    f32 _8 = sead::Mathf::infinity();  // max mass
};
KSYS_CHECK_SIZE_NX150(Unk_7102451148, 0x10);

// Paired contact callbacks used by the giant enemy AIs. Placeholder name follows the helper.
struct Unk_71007214A0 {
    Unk_7102451120 _0;
    Unk_7102451148 _10;
};

// Declaration only; the original source namespace is unknown.
void sub_71007214A0(Unk_71007214A0* callbacks, ksys::act::Actor* actor,
                   const sead::SafeString& dynamic_name, const sead::SafeString& body_name,
                   const sead::SafeString& extra_name, f32 max_mass);

// Free helpers in the same TU.
// 0x7100720140: sets Enemy::_e90 = 1 if the actor is an Enemy.
void sub_7100720140(ksys::act::Actor* actor);
// 0x7100720a70: forwards the actor to a method (0x710065d5d4) of the object at +0x450 of a singleton
// (GOT 0x7102579100).
void sub_7100720A70(ksys::act::Actor* actor);

// Source namespace is inferred from the existing Sandworm helper interface.
void sub_7100720254(ksys::act::Actor* actor);
void sub_71007208EC(ksys::act::Actor* actor);
void sub_710072022C(ksys::act::Actor* actor);
void sub_7100720814(ksys::act::Actor* actor, s32 mode);
