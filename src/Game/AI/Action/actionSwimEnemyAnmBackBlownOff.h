#pragma once

#include <math/seadMatrix.h>
#include "Game/AI/Action/actionSwimEnemyAnmBackBlownOffBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class SwimEnemyAnmBackBlownOff : public SwimEnemyAnmBackBlownOffBase {
    SEAD_RTTI_OVERRIDE(SwimEnemyAnmBackBlownOff, SwimEnemyAnmBackBlownOffBase)
public:
    explicit SwimEnemyAnmBackBlownOff(const InitArg& arg);
    ~SwimEnemyAnmBackBlownOff() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x70
    const float* mRotSpeed_s{};
    sead::Matrix33f _78;
    sead::Vector3f _9c;
};
KSYS_CHECK_SIZE_NX150(SwimEnemyAnmBackBlownOff, 0xa8);

}  // namespace uking::action
