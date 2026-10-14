#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ThrownSpear : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(ThrownSpear, ksys::act::ai::Action)
public:
    explicit ThrownSpear(const InitArg& arg);
    ~ThrownSpear() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // 0x7100297fc0 (declared only): the body of calc_ is out of line in the original.
    void sub_7100297FC0();
    void calc_() override;

    // static_param at offset 0x20
    const float* mRotSpeedZ_s{};
};

}  // namespace uking::action
