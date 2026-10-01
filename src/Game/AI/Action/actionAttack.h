#pragma once

#include "Game/AI/Action/actionAttackBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class Attack : public AttackBase {
    SEAD_RTTI_OVERRIDE(Attack, AttackBase)
public:
    explicit Attack(const InitArg& arg);
    ~Attack() override = default;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
    Unk_71023c8418* m32() override { return &_40; }
    virtual void m33();
    virtual bool m34() { return isFinishedAS(0, 0); }
    virtual u32 m35();

    // static_param at offset 0x30
    sead::SafeString mASName_s{};
    Unk_71023c8418 _40{this};
};
KSYS_CHECK_SIZE_NX150(Attack, 0xd0);

}  // namespace uking::action
