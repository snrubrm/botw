#pragma once

#include "Game/AI/Action/actionStopBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class Eat : public StopBase {
    SEAD_RTTI_OVERRIDE(Eat, StopBase)
public:
    explicit Eat(const InitArg& arg);
    ~Eat() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
    virtual void m32();

    // static_param at offset 0x30
    const bool* mIsHeal_s{};
};

}  // namespace uking::action
