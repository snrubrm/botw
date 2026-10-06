#pragma once

#include <basis/seadTypes.h>
#include <math/seadVector.h>

namespace ksys::act {
class Actor;
namespace ai {
class ActionBase;
}  // namespace ai
}  // namespace ksys::act

#include "Game/AI/aiUnk_71025afb58.h"

// Placeholder name from its RTTI typeInfo static 0x71025c89e8 (parent: Unk_71025afb58; Derive vtable 0x710235ff20,
// isDerived 0x7100066ec8): the "LynelMoveParam" AI tree variable's class. Layout unknown (only its RTTI is used by
// Unk_710070f974::sub_710070F9CC).
class Unk_71025c89e8 : public Unk_71025afb58 {
    SEAD_RTTI_OVERRIDE(Unk_71025c89e8, Unk_71025afb58)
public:
    Unk_71025c89e8() = default;
    ~Unk_71025c89e8() override;  // out of line (lane4 s47): the key function that emits the vtable 0x7102450c18
};

// Placeholder name (0x710070f974, no name known): a 0x18-byte state struct embedded at the end of
// LynelMove (+0x88) and LynelNavMeshMove (+0x80). Its constructor is out of line. Methods
// 0x710070f984 - 0x710070fa84 (and the 1.2 KB one at 0x710070fa84) are declared only except the first two.
struct Unk_710070f974 {
    Unk_710070f974();
    ~Unk_710070f974();

    // 0x710070f984 (declared only): `action->getAITreeVariable(&_10, "LynelMoveParam")`.
    void sub_710070F984(ksys::act::ai::ActionBase* action);
    // 0x710070f9cc: `_0 = 0`, resets the actor's AS list (kind 9), `_8 = DynamicCast<...>(*_10)`.
    void sub_710070F9CC(ksys::act::Actor* actor);
    // 0x710070fa84 (declared only; the third parameter is the XZ distance computed by the callers).
    void sub_710070FA84(ksys::act::Actor* actor, const sead::Vector3f* pos, f32 dist);

    s32 _0 = 0;
    Unk_71025c89e8* _8 = nullptr;
    void* _10 = nullptr;  // AI tree variable "LynelMoveParam" (points to an Unk_71025c89e8*)
};
