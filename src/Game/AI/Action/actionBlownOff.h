#pragma once

#include "Game/AI/Action/actionRagdoll.h"
#include "Game/AI/aiUnkDamageCallbacks.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::dmg {
class DamageManager;
}

namespace uking::action {

class BlownOff : public Ragdoll {
    SEAD_RTTI_OVERRIDE(BlownOff, Ragdoll)
public:
    explicit BlownOff(const InitArg& arg);
    ~BlownOff() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;
    bool isChangeable() const override;

protected:
    void calc_() override;
    void m38() override;
    s32 m40() override;
    virtual s32 m41(uking::dmg::DamageManager* manager);

    // static_param at offset 0x118
    const int* mAddTime_s{};
    // static_param at offset 0x120
    const float* mLifeReflexRatio_s{};
    // static_param at offset 0x128
    const float* mImpulseRatio_s{};
    Unk_7102451970 _130;
    int _158 = 0;
    bool _15c = true;
};

}  // namespace uking::action
