#pragma once

#include <basis/seadTypes.h>

namespace ksys::act {
class Actor;
class BaseProcLink;
}  // namespace ksys::act

// 0x710073033c (lane1 s21; placeholder name): whether the distance between the actor and the actor
// `link` points to is at most `distance`.
bool sub_710073033C(ksys::act::Actor* actor, ksys::act::BaseProcLink* link, f32 distance);
