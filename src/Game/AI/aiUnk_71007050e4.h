#pragma once

#include <basis/seadTypes.h>
#include <prim/seadSafeString.h>

namespace ksys::act {
class Actor;
namespace ai {
class ActionBase;
}  // namespace ai
}  // namespace ksys::act

// Placeholder name (first method 0x71007050e4 = the out-of-line constructor; no name known): the 0x10-byte state of
// GiantOneHandAttackWithLegTurn (embedded at +0x280): the weapon index static param and the actor.
struct Unk_71007050e4 {
    explicit Unk_71007050e4(ksys::act::Actor* actor);
    ~Unk_71007050e4();

    // 0x71007050f0 (declared only): `action->getStaticParam(&_0, "<name>")`.
    void sub_71007050F0(ksys::act::ai::ActionBase* action);
    // 0x7100705138 / 0x7100705188 (declared only): the bodies of the action's m32 / m33.
    void sub_7100705138(const sead::SafeString* name);
    void sub_7100705188();

    /* 0x00 */ const s32* _0 = nullptr;
    /* 0x08 */ ksys::act::Actor* _8;
};
static_assert(sizeof(Unk_71007050e4) == 0x10);
