#pragma once

#include <basis/seadTypes.h>
#include <prim/seadSafeString.h>

namespace sead {
class Heap;
}

namespace ksys::act {
class Actor;
class BaseProc;
class BaseProcLink;
}  // namespace ksys::act

namespace uking::act {
class Enemy;
}

namespace uking::ai {
class Unk_71024241a8;
}

// Unnamed free helpers for Stalfos part actors (0x7100724c80-0x7100725960, CSV placeholders
// aiStalPartStuff_3..16). They act on the uking::act::Unk_7100d3cd74 parts list (Enemy::_1128) of an
// Enemy that has the StalfosParts tag. `part` indexes the part name table
// {StalHead, StalLeftArm, StalChin, StalRib1, StalRib2, StalRib3, StalRib4} (0x71024511f8).

// The actor as an Enemy if it has the StalfosParts tag, else nullptr.
uking::act::Enemy* sub_7100724D7C(ksys::act::Actor* actor);
// 0x71007275c8 (declared only): takes the Enemy of sub_7100724D7C (ForkStalEnemyHeadShot / ForkStalPartBlownOff calc_).
void sub_71007275C8(uking::act::Enemy* enemy);

bool sub_7100724C80(ksys::act::Actor* actor, sead::Heap* heap, u32 part);
bool sub_7100724E1C(ksys::act::Actor* actor, u32 part);
ksys::act::BaseProcLink& sub_7100724F08(ksys::act::Actor* actor, u32 part);
bool sub_7100724FE8(ksys::act::Actor* actor, ksys::act::BaseProc* proc, u32 part);
bool sub_71007250E4(ksys::act::Actor* actor, u32 part);
// 0x710072735c (declared only; called by ForkStalEnemyGrabOwnPart::calc_).
void sub_710072735C(ksys::act::Actor* actor, bool a1, bool a2);
// 0x7100727aa0 (declared only; called by ForkStalEnemyGrabOwnPart::calc_).
void sub_7100727AA0(ksys::act::Actor* actor, u32 part);

const char* sub_71007251D0();
const char* sub_71007251DC();
bool sub_71007251E8(ksys::act::Actor* actor, sead::Heap* heap);
bool sub_71007252D4(ksys::act::Actor* actor, sead::Heap* heap);
bool sub_71007253C0(ksys::act::Actor* actor);
bool sub_71007254A4(ksys::act::Actor* actor);
ksys::act::BaseProcLink& sub_7100725588(ksys::act::Actor* actor);
ksys::act::BaseProcLink& sub_71007255A0(ksys::act::Actor* actor);
bool sub_71007255B8(ksys::act::Actor* actor, ksys::act::BaseProc* proc);
bool sub_71007256A4(ksys::act::Actor* actor, ksys::act::BaseProc* proc);
bool sub_7100725790(ksys::act::Actor* actor, const ksys::act::BaseProcLink& link);
bool sub_710072587C(ksys::act::Actor* actor);

// Declared only: first ModelUnit material lookup and setMaterialVisible (slots 24 and 54).
// GolemThrowParts 0x710018d8dc and AI 0x71003ff79c pass Actor*, SafeString and bool.
bool sub_7100725960(ksys::act::Actor* actor, const sead::SafeString& material, bool visible);
// The same operation on the formatted "%s_Seal" material name (native 0x7101dc12a6).
bool sub_71007259CC(ksys::act::Actor* actor, const sead::SafeString& material, bool visible);

// Whether the Stalfos part `part` still has its parts actor (true if the actor isn't a Stalfos-parts
// Enemy). CSV aiStalEnemyRootStuff_1.
bool sub_7100726004(ksys::act::Actor* actor, u32 part);
// sub_7100726004(actor, 0) (StalHead).
bool sub_7100726620(ksys::act::Actor* actor);
// The actor's "StalEnemyUnit" AI tree variable object (two identical out-of-line copies:
// 0x7100726628 is called by StalEnemySleep::m36, 0x7100726ff4 by StalEnemyNoHeadWait,
// StalEnemyBlownOff and StalEnemySleep::calc_).
uking::ai::Unk_71024241a8* sub_7100726628(ksys::act::Actor* actor);
uking::ai::Unk_71024241a8* sub_7100726FF4(ksys::act::Actor* actor);

// Whether the Stalfos left arm (part 1) is present: true if the actor isn't a Stalfos-parts Enemy
// or has the TeamMoriblin tag. CSV aiLandHumEnemyUnarmedStuff.
bool sub_7100726E54(ksys::act::Actor* actor);
// sub_7100726004(actor, 1) (StalLeftArm).
bool sub_7100726F20(ksys::act::Actor* actor);
// Whether the Stalfos left arm (part 1) is present for a Stalfos-parts Enemy with the TeamBokoblin
// tag; true otherwise. CSV aiBokoblinRestraintStuff.
bool sub_7100726F28(ksys::act::Actor* actor);
// Bit 1 of the "StalEnemyUnit" object's flags (false without the object).
bool sub_71007271D4(ksys::act::Actor* actor);

// 0x7100728640 (CSV aiStalPartStuff): whether the StalEnemyUnit has flag bit 1 and any of the parts
// StalLeftArm..StalRib4 (table entries 1-6) of the Stalfos actor is present.
bool sub_7100728640(ksys::act::Actor* actor);
