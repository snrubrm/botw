#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/System/Timer.h"

namespace uking::ai {

class TargetAttackAttitudeTgtSelectBase : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(TargetAttackAttitudeTgtSelectBase, ksys::act::ai::Ai)
public:
    explicit TargetAttackAttitudeTgtSelectBase(const InitArg& arg);
    ~TargetAttackAttitudeTgtSelectBase() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

    virtual void m34(ksys::act::ai::InlineParamPack* params);
    virtual void m35(ksys::act::ai::InlineParamPack* params);

protected:
    void sub_71005BB664(bool enable);
    bool sub_71005BB85C();

    ksys::Timer _38{0.0f, 0.0f};
};

}  // namespace uking::ai
