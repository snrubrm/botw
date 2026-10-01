#pragma once

#include "Game/AI/Action/actionJumpAttack.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class LynelHighJumpAttack : public JumpAttack {
    SEAD_RTTI_OVERRIDE(LynelHighJumpAttack, JumpAttack)
public:
    explicit LynelHighJumpAttack(const InitArg& arg);
    ~LynelHighJumpAttack() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
    void m32(f32 a, f32 b) override;
    f32 m33() override;
    f32 _a8 = 0;
};

}  // namespace uking::action
