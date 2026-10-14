#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class RandomSelectTwoActionBase : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(RandomSelectTwoActionBase, ksys::act::ai::Ai)
public:
    explicit RandomSelectTwoActionBase(const InitArg& arg);
    ~RandomSelectTwoActionBase() override;

    bool isFailed() const override;
    bool isFinished() const override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

    virtual int m34() { return 0; }
    virtual void m35(ksys::act::ai::InlineParamPack* params);
    virtual void m36(ksys::act::ai::InlineParamPack* params);

protected:
    // static_param at offset 0x38
    const int* mCorrectRateToA_s{};
    // static_param at offset 0x40
    const int* mCorrectRateToB_s{};
    int _48 = 0;
};

}  // namespace uking::ai
