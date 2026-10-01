#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

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
    float _50 = 0.0f;
    int _54 = 0;
    int _58 = 0;
    float _5c = 0.0f;
    int _60 = 0;
    int _64 = 0;
    float _68 = 30.0f;
    u16 _6c = 0;
    bool _6e = false;
};

}  // namespace uking::action
