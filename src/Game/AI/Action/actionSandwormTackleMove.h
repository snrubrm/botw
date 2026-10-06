#pragma once

#include "Game/AI/Action/actionAtkTackleMove.h"
#include <container/seadPtrArray.h>
#include "KingSystem/ActorSystem/actAiAction.h"
#include <gsys/gsysModelAccessKey.h>

namespace uking::action {

// Placeholder name (target of a tackle: an actor handle at 0x38 and a counter at 0x58; the destructor 0x71073e3bc is
// declared only).
struct Unk_SandwormTackleTarget {
    ~Unk_SandwormTackleTarget();

    u8 _0[0x38];
    ksys::act::BaseProcLink _38;
    u8 _48[0x58 - 0x48];
    s32 _58;
    u8 _5c[4];
};

// Actor plus a two-element list of targets (names are guesses). The member functions are
// declared only (0x71f6dc, 0x71f858, 0x71fefc, 0x71ff70); SandwormJumpTackle has the same object
// at 0xc0.
struct Unk_SandwormTackleMoveList {
    explicit Unk_SandwormTackleMoveList(ksys::act::Actor* actor) : mActor(actor) {}

    bool sub_71F6DC(sead::Heap* heap);
    void sub_71F858();  // deletes all targets (called from the owners' destructors)
    void sub_71FEFC();
    bool sub_71FF70(const ksys::MessageAck* ack);

    ksys::act::Actor* mActor;
    sead::FixedPtrArray<Unk_SandwormTackleTarget, 2> mTargets;
};

class SandwormTackleMove : public AtkTackleMove {
    SEAD_RTTI_OVERRIDE(SandwormTackleMove, AtkTackleMove)
public:
    explicit SandwormTackleMove(const InitArg& arg);
    ~SandwormTackleMove() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;
    bool isFailed() const override;
    bool handleAck_(const ksys::MessageAck* ack) override;

protected:
    void calc_() override;
    void m32(sead::Vector3f* pos) override;
    f32 m34() override;
    f32 m35() override;
    void m37() override;
    void m36() override;
    bool m38() override;

    // static_param at offset 0xc0
    const float* mTargetSandOffset_s{};
    // static_param at offset 0xc8
    const float* mSandOffsetSpeed_s{};
    // static_param at offset 0xd0
    const float* mEatRadius_s{};
    // static_param at offset 0xd8
    sead::SafeString mEatNode_s{};
    // static_param at offset 0xe8
    const sead::Vector3f* mEatOffset_s{};
    f32 _f0 = 1.0f;
    bool _f4 = false;
    bool _f5 = false;
    gsys::BoneAccessKeyEx _f8;
    Unk_SandwormTackleMoveList _130{mActor};
};

KSYS_CHECK_SIZE_NX150(SandwormTackleMove, 0x158);

}  // namespace uking::action
