#pragma once

#include "Game/AI/Action/actionPredictVacuumShoot.h"
#include "KingSystem/ActorSystem/actAiAction.h"
#include "KingSystem/ActorSystem/actCCAccessor.h"

namespace uking::action {

class HoverPredictVacuumShoot : public PredictVacuumShoot {
    SEAD_RTTI_OVERRIDE(HoverPredictVacuumShoot, PredictVacuumShoot)
public:
    explicit HoverPredictVacuumShoot(const InitArg& arg);
    ~HoverPredictVacuumShoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
    void m32() override;

    /* 0x130 */ ksys::act::CCAccessor _130;
};

}  // namespace uking::action
