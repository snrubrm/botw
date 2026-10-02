#pragma once

#include <math/seadMatrix.h>
#include "Game/AI/Action/actionTakeHitImpactForce.h"
#include "KingSystem/ActorSystem/actAiAction.h"
#include <math/seadVector.h>

namespace uking::action {

class SmallDamageBackwardBase : public TakeHitImpactForce {
    SEAD_RTTI_OVERRIDE(SmallDamageBackwardBase, TakeHitImpactForce)
public:
    explicit SmallDamageBackwardBase(const InitArg& arg);
    ~SmallDamageBackwardBase() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
    void m34() override;
    sead::Vector3f _90;
    sead::Matrix33f _9c;
};

KSYS_CHECK_SIZE_NX150(SmallDamageBackwardBase, 0xc0);

}  // namespace uking::action
