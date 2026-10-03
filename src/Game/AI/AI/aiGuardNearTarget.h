#pragma once

#include "Game/AI/aiUnkDamageCallbacks.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class GuardNearTarget : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(GuardNearTarget, ksys::act::ai::Ai)
public:
    explicit GuardNearTarget(const InitArg& arg);
    ~GuardNearTarget() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;
    bool isChangeable() const override;

    virtual bool m34(float distance);
    virtual bool m35() { return false; }
    virtual bool m36(float distance);
    virtual void m37(bool enable);
    virtual bool m38() { return false; }
    // 0x710044d00c (placeholder name)
    void changeToStartFastGuard();

protected:
    float sub_710044C9E8() const;
    void changeToStartGuard();

    struct Params {
        // static_param at offset 0x38
        const int* mWeaponIdx_s{};
        // static_param at offset 0x40
        const float* mBaseDist_s{};
        // static_param at offset 0x48
        const float* mGuardStartDist_s{};
        // static_param at offset 0x50
        const float* mGuardEndDist_s{};
        // dynamic_param at offset 0x58
        sead::Vector3f* mTargetPos_d{};
    };
    Params mParams;
    Unk_71024519a8 _60;
};

}  // namespace uking::ai
