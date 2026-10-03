#pragma once

#include <math/seadVector.h>
#include "Game/Actor/actGuardian.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace ksys::act {
class Actor;
}

// Placeholder name = its only virtual (default implementation 0x7100041da4). Second base class of
// GuardianMoveTo (at +0x20, 8 bytes: just the vptr); the Guardian reads it through a pointer that
// GuardianMoveTo::enter_ stores (Guardian component +0x50). No RTTI, no virtual destructor.
// m0(data, actor) fills the movement data of `data` (directions, speed) for `actor`; the default
// walks the actor's rail if it has one (not decompiled yet). Overridden by the subclasses
// (GuardianMoveToPosition::m32 / GuardianMoveToTarget::m32 / GuardianStopWait::m32 and thunks).
class Unk_7100041da4 {
public:
    // Placeholder (only the members used so far; the real size is at least 0xc4).
    struct Data {
        /* 0x00 */ sead::Vector3f _0;   // direction to move in (normalised)
        /* 0x0c */ sead::Vector3f _c;   // same, at the end of m0
        /* 0x18 */ f32 _18;             // distance to go (or the speed limit)
        /* 0x1c */ sead::Vector3f _1c;
        /* 0x28 */ sead::Vector3f _28;
        /* 0x34 */ sead::Vector3f _34;  // = _b8
        /* 0x40 */ sead::Vector3f _40;  // up (0, 1, 0)
        /* 0x4c */ u8 _4c[0xb8 - 0x4c];
        /* 0xb8 */ sead::Vector3f _b8;
    };

    virtual void m0(Data* data, ksys::act::Actor* actor);

protected:
    ~Unk_7100041da4() = default;
};

namespace uking::action {

class GuardianMoveTo : public ksys::act::ai::Action, public Unk_7100041da4 {
    SEAD_RTTI_OVERRIDE(GuardianMoveTo, ksys::act::ai::Action)
public:
    explicit GuardianMoveTo(const InitArg& arg);
    ~GuardianMoveTo() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // 0x71001928b0: the _15b0 structure of the actor as a Guardian or, failing that, of its connected
    // calc parent as a Guardian (nullptr if there is none; same lookup as GuardianAI::sub_710040DC54).
    uking::act::Guardian::Unk1* sub_71001928B0();
    // 0x7100192798 / 0x7100192824 (identical bodies): the actor as a Guardian (DynamicCast).
    uking::act::Guardian* sub_7100192798();
    uking::act::Guardian* sub_7100192824();
    // 0x7100192770: tail call to sub_71001928B0.
    uking::act::Guardian::Unk1* sub_7100192770();
};

}  // namespace uking::action
