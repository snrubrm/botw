#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

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
    // inline-only in the original; name is a guess. enter_ and calc_ both contain this
    // string + param pack + m36 + changeChild sequence twice.
    void changeChildByName(const sead::SafeString& child) {
        ksys::act::ai::InlineParamPack pack;
        m36(child, &pack);
        changeChild(child.cstr(), &pack);
    }

    // static_param at offset 0x38
    const int* mIntervalToCheckSchedule_s{};
};

}  // namespace uking::ai
