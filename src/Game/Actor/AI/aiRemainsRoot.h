#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class RemainsRoot : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(RemainsRoot, ksys::act::ai::Ai)
public:
    explicit RemainsRoot(const InitArg& arg);
    ~RemainsRoot() override;

    bool reenter_(ksys::act::ai::ActionBase* other, bool x) override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

    virtual void m34();
    virtual void m35(bool x);
    virtual void m36();

protected:
    // static_param at offset 0x38
    const int* mRemainsTypeID_s{};
    // static_param at offset 0x40
    const bool* mIsAllowRotAxisX_s{};
    bool _48 = false;
    bool _49 = false;
};

}  // namespace uking::ai
