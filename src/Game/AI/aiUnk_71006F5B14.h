#pragma once

#include <basis/seadTypes.h>
#include <prim/seadEnum.h>

namespace ksys::act {
class Actor;
class Chemical;
}

// Chemical helpers in the translation unit at 0x71006f5xxx (they walk the actor's ActorChemicals at
// +0x6a8). Placeholder names; not decompiled yet.

// 0x71006f5b14
void sub_71006F5B14(ksys::act::Actor* actor);
// 0x71006f5c50
void sub_71006F5C50(ksys::act::Actor* actor);

// The element of an actor's chemical (lane1 s21). A SEAD_ENUM in the original: its text list
// "Normal, Fire, Electric, Ice" is parsed by 0x71006f5db0 (text_; the CSV misnames that function
// aal::VirtualSurroundCtrl::SurroundLevel::text_). Placeholder name.
SEAD_ENUM(Unk_71006F5DB0, Normal, Fire, Electric, Ice)

// 0x71006f5694: reads the element from the actor's chemical (declared only).
Unk_71006F5DB0 sub_71006F5694(ksys::act::Actor* actor);
// 0x71006f594c: whether `chemical` is active for `element` (declared only).
bool sub_71006F594C(Unk_71006F5DB0 element, ksys::act::Chemical* chemical);
// 0x71006f59c4 (declared only).
bool sub_71006F59C4(ksys::act::Actor* actor, int a2);
// 0x71006f5d3c (declared only): starts the head-shot limp animation of `element` (actor's ASList).
void sub_71006F5D3C(Unk_71006F5DB0 element, ksys::act::Actor* actor);
// 0x71006f6144 (declared only).
void sub_71006F6144(ksys::act::Actor* actor);
// 0x71006f55d8 (lane2 s21): makes the actor's character controller leave hover mode (sets motion type _1
// unless it already is).
void sub_71006F55D8(ksys::act::Actor* actor);
// 0x71006f566c (lane2 s21): whether the actor's character controller is in hover motion type.
bool sub_71006F566C(ksys::act::Actor* actor);
