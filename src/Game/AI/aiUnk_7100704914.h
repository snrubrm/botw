#pragma once

#include <basis/seadTypes.h>
#include <prim/seadSafeString.h>

namespace ksys::act {
class Actor;
namespace ai {
class ActionBase;
}  // namespace ai
}  // namespace ksys::act

// Placeholder name (first method 0x7100704914 = the out-of-line constructor; no name known): the 0x40-byte state of
// GiantOneHandPunchWithLegTurn (embedded at +0x280): three attack sensor names (static params) and the actor.
struct Unk_7100704914 {
    explicit Unk_7100704914(ksys::act::Actor* actor);
    ~Unk_7100704914();

    // 0x7100704944: `_38 = false` (the action's enter_).
    void sub_7100704944();
    // 0x710070494c (declared only): the action's calc_ (1 KB).
    void sub_710070494C();
    // 0x7100704d84 (declared only): the action's loadParams_ (three string params).
    void sub_7100704D84(ksys::act::ai::ActionBase* action);
    // 0x7100704f1c (declared only): the action's m32 (activates an attack sensor).
    void sub_7100704F1C(const sead::SafeString* name);
    // 0x710070507c: the action's m33 (removes the sensors named in `_0` / `_10`).
    void sub_710070507C();

    /* 0x00 */ sead::SafeString _0[2];
    /* 0x20 */ sead::SafeString _20;
    /* 0x30 */ ksys::act::Actor* _30;
    /* 0x38 */ bool _38 = false;
};
static_assert(sizeof(Unk_7100704914) == 0x40);
