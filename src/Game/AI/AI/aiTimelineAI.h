#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class TimelineAI : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(TimelineAI, ksys::act::ai::Ai)
public:
    explicit TimelineAI(const InitArg& arg);

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

    virtual const sead::SafeString& m34();
    virtual bool m35(const sead::SafeString& name) { return true; }
    virtual void m36(const sead::SafeString& name, ksys::act::ai::InlineParamPack* params);

protected:
    // static_param at offset 0x38
    const int* mIntervalToCheckSchedule_s{};
};

}  // namespace uking::ai
