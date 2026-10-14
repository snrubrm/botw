#pragma once

namespace ksys::act {
class Actor;
}

// 0x710073d318 (declared only; placeholder name): the actor linked from the horse-ride info (Actor vslot 0x410,
// link at +0x18) as an Actor (DynamicCast); nullptr if there is none. HorseRideChaseBattleAttackMove::m34.
ksys::act::Actor* sub_710073D318(ksys::act::Actor* actor);
