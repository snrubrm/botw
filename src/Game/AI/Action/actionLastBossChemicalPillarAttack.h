#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"
#include "KingSystem/System/Timer.h"

namespace uking::action {

class LastBossChemicalPillarAttack : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(LastBossChemicalPillarAttack, ksys::act::ai::Action)
public:
    explicit LastBossChemicalPillarAttack(const InitArg& arg);
    ~LastBossChemicalPillarAttack() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;
    bool isChangeable() const override;

protected:
    void calc_() override;
    virtual void m32();
    virtual void m33();

    struct Params {
        // static_param at offset 0x20
        const int* mPillarNum_s{};
        // static_param at offset 0x28
        const float* mAttackEndWait_s{};
        // static_param at offset 0x30
        const float* mCreateInterval_s{};
        // static_param at offset 0x38
        const float* mPillarYOffset_s{};
    };
    Params mParams;
    s32 _40 = 0;
    s32 _44 = 16;
    s32 _48 = 0;
    bool _4c = false;
    bool _4d = false;
    bool _4e = false;
    u8 _4f[0x1];
    ksys::Timer _50;
    ksys::Timer _5c;
    u8 _68[0x28];
};
KSYS_CHECK_SIZE_NX150(LastBossChemicalPillarAttack, 0x90);

}  // namespace uking::action
