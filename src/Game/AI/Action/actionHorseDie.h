#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class HorseDie : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(HorseDie, ksys::act::ai::Action)
public:
    explicit HorseDie(const InitArg& arg);
    ~HorseDie() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;
    bool handleMessage_(const ksys::Message& message) override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const int* mDyingFrames_s{};
    // static_param at offset 0x28
    const bool* mCheckIfStable_s{};
    // static_param at offset 0x30
    sead::SafeString mASName_s{};
    float _40 = 0.0f;
    int _44 = -1;
    float _48 = 0.0f;
    bool _4c = true;
};

}  // namespace uking::action
