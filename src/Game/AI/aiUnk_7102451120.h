#pragma once

#include <basis/seadTypes.h>
#include <math/seadMathCalcCommon.h>
#include "KingSystem/Physics/System/physContactPointInfo.h"
#include "KingSystem/XLink/xlinkActorUtil.h"
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

    // 0x7100721380 (lane1 s47): GolemRoot::enter_ calls it: sets the max mass, makes every body of the actor's "Body" set a
    // gravity-free, impulse-free body without ground collision and installs this callback on the first one.
    void sub_7100721380(f32 max_mass, ksys::act::Actor* actor);

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

// 0x71005dda44 (defined in aiUnk_71005D6D10.cpp; declared here by lane1 s47): enables the "..." attention client of the actor.
void sub_71005DDA44(ksys::act::Actor* actor);

// 0x7100721670 (lane1 s47; the first argument is unused): makes the rigid body `name` of the actor's "Body" set a
// gravity-free, impulse-free, ground-collision-free body that only contacts the player layer.
void sub_7100721670(void* unused, ksys::act::Actor* actor, const sead::SafeString& name);

// Free helpers in the same TU.
// 0x7100720140: sets Enemy::_e90 = 1 if the actor is an Enemy.
void sub_7100720140(ksys::act::Actor* actor);
// 0x7100720a70: forwards the actor to a method (0x710065d5d4) of the object at +0x450 of a singleton
// (GOT 0x7102579100).
void sub_7100720A70(ksys::act::Actor* actor);

// lane4 s49 (declaration-only native helpers of the same TU; source namespaces unknown): 0x710072009c
// (`sub_71005D8DE8(actor, PlayerInfo::instance()->getPlayerLink(), nullptr, nullptr)`), 0x71007200b8 (`Enemy::_e90 = 4`, like
// sub_7100720140 which sets 1), 0x71007201c8 / 0x71007201fc (the "Atk" body `name`: activate / deactivate), 0x710072022c
// / 0x7100720254 (all "Atk" bodies), 0x7100720330 (clears bits 3 / 4 of the attack sensor's _20), 0x71007209e8 /
// 0x7100720a00 / 0x7100720a18 (xlinkSearchAndEmit(actor, "BombEat" / "InsideBomb" / "BombNotEat", 2, arg)).
void sub_710072009C(ksys::act::Actor* actor);
void sub_71007200B8(ksys::act::Actor* actor);
// 0x7100720354 (name-based classification: "All" -> 0, "Tail" -> 1, else 2), 0x7100720454 (enables contacts of the
// "Body" set bodies with NPCs / the player), 0x7100720510 (772 B, declared only).
s32 sub_7100720354(const sead::SafeString& name);
void sub_7100720454(ksys::act::Actor* actor);
void sub_7100720510(ksys::act::Actor* actor, const sead::SafeString& names);
void sub_7100720A00(ksys::act::Actor* actor, Unk_71012419b4* arg);

// Source namespace is inferred from the existing Sandworm helper interface.
void sub_7100720254(ksys::act::Actor* actor);
void sub_71007208EC(ksys::act::Actor* actor);
void sub_710072022C(ksys::act::Actor* actor);
void sub_7100720814(ksys::act::Actor* actor, s32 mode);
