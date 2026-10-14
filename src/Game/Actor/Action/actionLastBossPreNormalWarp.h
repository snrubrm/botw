#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"
#include "KingSystem/System/Timer.h"

namespace uking::action {

class LastBossPreNormalWarp : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(LastBossPreNormalWarp, ksys::act::ai::Action)
public:
    explicit LastBossPreNormalWarp(const InitArg& arg);
    ~LastBossPreNormalWarp() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
    virtual void m32();
    virtual void m33();
    virtual void m34(f32 a1, ksys::act::Actor* actor, bool a3);

    // static_param at offset 0x20
    const float* mPreWarpWaitTime_s{};
    // static_param at offset 0x28
    const float* mPosReduce_s{};
    // static_param at offset 0x30
    const bool* mIsDeleteEffect_s{};
    // static_param at offset 0x38
    sead::SafeString mASName_s{};
    // dynamic_param at offset 0x48
    bool* mIsPartsWarpEffectSync_d{};
    ksys::Timer _50;
    float _5c = 0.0f;
    float _60 = 0.0f;
    float _64 = 0.0f;
    float _68 = 30.0f;
    bool _6c = false;
    bool _6d = false;
    bool _6e = false;
};

}  // namespace uking::action
