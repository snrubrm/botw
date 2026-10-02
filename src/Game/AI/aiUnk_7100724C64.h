#pragma once

#include <basis/seadTypes.h>

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

// Unnamed free helpers for Stalfos part actors (0x7100724c80-0x7100725960, CSV placeholders
// aiStalPartStuff_3..16). They act on the uking::act::Unk_7100d3cd74 parts list (Enemy::_1128) of an
// Enemy that has the StalfosParts tag. `part` indexes the part name table
// {StalHead, StalLeftArm, StalChin, StalRib1, StalRib2, StalRib3, StalRib4} (0x71024511f8).

// The actor as an Enemy if it has the StalfosParts tag, else nullptr.
uking::act::Enemy* sub_7100724D7C(ksys::act::Actor* actor);

bool sub_7100724C80(ksys::act::Actor* actor, sead::Heap* heap, u32 part);
bool sub_7100724E1C(ksys::act::Actor* actor, u32 part);
ksys::act::BaseProcLink& sub_7100724F08(ksys::act::Actor* actor, u32 part);
bool sub_7100724FE8(ksys::act::Actor* actor, ksys::act::BaseProc* proc, u32 part);
bool sub_71007250E4(ksys::act::Actor* actor, u32 part);

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
