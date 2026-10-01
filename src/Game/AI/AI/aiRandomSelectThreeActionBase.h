#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class RandomSelectThreeActionBase : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(RandomSelectThreeActionBase, ksys::act::ai::Ai)
public:
    explicit RandomSelectThreeActionBase(const InitArg& arg);
    ~RandomSelectThreeActionBase() override;

    bool isFailed() const override {
        return mFlags.isOn(Flag::Failed) || getCurrentChild()->isFailed();
    }
    bool isFinished() const override {
        return mFlags.isOn(Flag::Finished) || getCurrentChild()->isFinished();
    }

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

    virtual f32 m34();
    virtual f32 m35();
    virtual f32 m36();

protected:
    // static_param at offset 0x38
    const float* mCorrectRatioA_s{};
    // static_param at offset 0x40
    const float* mCorrectRatioB_s{};
    // static_param at offset 0x48
    const float* mCorrectRatioC_s{};
    int _50;
    int _54;
    int _58;
};

}  // namespace uking::ai
