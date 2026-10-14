#pragma once

#include "Game/Actor/Action/actionKnockBackHitImpactForce.h"
#include "KingSystem/ActorSystem/actAiAction.h"
#include <math/seadVector.h>

namespace uking::action {

class Guard : public KnockBackHitImpactForce {
    SEAD_RTTI_OVERRIDE(Guard, KnockBackHitImpactForce)
public:
    explicit Guard(const InitArg& arg);

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void loadParams_() override;
    bool isChangeable() const override;

protected:
    void calc_() override;
    virtual void m38();

    // static_param at offset 0x90
    const float* mRotSubsAngRate_s{};
    sead::Vector3f _98;
};

KSYS_CHECK_SIZE_NX150(Guard, 0xa8);

}  // namespace uking::action
