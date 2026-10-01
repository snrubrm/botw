#pragma once

#include "Game/AI/Action/actionAttack.h"
#include "Game/AI/Action/actionUnk_71023c8378.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class AttackPartBind : public Attack {
    SEAD_RTTI_OVERRIDE(AttackPartBind, Attack)
public:
    explicit AttackPartBind(const InitArg& arg);
    ~AttackPartBind() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
    Unk_71023c8378* m32() override { return &_d8; }
    void m33() override;
    bool m34() override { return isFinishedAS(*mASSlot_s, 0); }

    // static_param at offset 0xd0
    const int* mASSlot_s{};
    Unk_71023c8378 _d8{this};
    sead::SafeString _168;
};
KSYS_CHECK_SIZE_NX150(AttackPartBind, 0x178);

}  // namespace uking::action
