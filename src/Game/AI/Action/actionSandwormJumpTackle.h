#pragma once

#include <gsys/gsysModelAccessKey.h>
#include "Game/AI/Action/actionJumpTackle.h"
#include "Game/AI/Action/actionSandwormTackleMove.h"
#include "KingSystem/ActorSystem/actAiAction.h"

#include "KingSystem/XLink/xlinkActorUtil.h"

namespace uking::action {

class SandwormJumpTackle : public JumpTackle {
    SEAD_RTTI_OVERRIDE(SandwormJumpTackle, JumpTackle)
public:
    explicit SandwormJumpTackle(const InitArg& arg);
    ~SandwormJumpTackle() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
    void m32() override;
    void m33() override;
    bool m34() const override;
    bool handleAck_(const ksys::MessageAck* ack) override;

    // static_param at offset 0x98
    const float* mPosReduceRate_s{};
    // static_param at offset 0xa0
    const float* mGravityScale_s{};
    // static_param at offset 0xa8
    sead::SafeString mAtkColName_s{};
    // dynamic_param at offset 0xb8
    ksys::act::BaseProcLink* mTargetActor_d{};
    Unk_SandwormTackleMoveList _c0{mActor};
    sead::Vector3f _e8{0, 0, 0};
    bool _f4 = false;
    f32 _f8 = 0.0f;
    bool _fc = false;
    gsys::BoneAccessKeyEx _100;
    Unk_71012419b4 _138;
};

KSYS_CHECK_SIZE_NX150(SandwormJumpTackle, 0x158);

}  // namespace uking::action
