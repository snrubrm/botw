#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class SetPartBind : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(SetPartBind, ksys::act::ai::Ai)
public:
    explicit SetPartBind(const InitArg& arg);
    ~SetPartBind() override;

    bool isChangeable() const override { return getCurrentChild()->isChangeable(); }

    bool isFailed() const override { return getCurrentChild()->isFailed(); }
    bool isFinished() const override { return getCurrentChild()->isFinished(); }

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

protected:
    void sub_7100567E78();

    // static_param at offset 0x38
    sead::SafeString mBaseNodeName_s{};
    // static_param at offset 0x48
    sead::SafeString mPartialNodeName_s{};
};

}  // namespace uking::ai
