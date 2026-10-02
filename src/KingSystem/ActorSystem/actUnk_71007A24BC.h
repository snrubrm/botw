#pragma once

#include <basis/seadTypes.h>
#include "KingSystem/ActorSystem/actUnk_7102459df8.h"

namespace ksys::act {

class Actor;

// Placeholder names: Actor helper free functions at 0x71007a24bc-0x71007a4a90 (attack info / sensor
// accessors that DynamicCast Actor::getAtk() and Actor::m126()).

// The following return a default value if the actor has no Unk_7102459df8 (Actor::m126()).
Unk_7102459df8::Unk_710079d5a0::Unk1* sub_71007A40D0(Actor* actor, int idx);
bool sub_71007A4178(Actor* actor, bool flag);
s32 sub_71007A425C(Actor* actor);
bool sub_71007A42FC(Actor* actor);
bool sub_71007A4638(Actor* actor, bool flag);
Unk_7102459df8::Unk_7102459e60::Unk1* sub_71007A471C(Actor* actor, int idx);
s32 sub_71007A47C4(Actor* actor);
bool sub_71007A4864(Actor* actor, bool flag);
Unk_7102459df8::Unk_7102459e88::Unk1* sub_71007A4948(Actor* actor, int idx);
s32 sub_71007A49F0(Actor* actor);

// Set or clear bits 0 / 1 of ActorAtk::_78 (no-op if the actor has no ActorAtk).
void sub_71007A44E4(Actor* actor, bool on);
void sub_71007A458C(Actor* actor, bool on);

}  // namespace ksys::act
