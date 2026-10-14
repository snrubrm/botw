#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class ChildSelector : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(ChildSelector, ksys::act::ai::Ai)
public:
    explicit ChildSelector(const InitArg& arg);
    ~ChildSelector() override;
    bool isFinished() const override;
    bool isFailed() const override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

    virtual bool m34(ksys::act::BaseProc* proc);

protected:
    // static_param at offset 0x38
    const bool* mIsNoChildForceEnd_s{};
    // static_param at offset 0x40
    const bool* mIsCheckEveryFrame_s{};
};

}  // namespace uking::ai
