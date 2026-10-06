#pragma once

#include "Game/AI/Action/actionWaterUpDownAnmDrivenMove.h"
#include <math/seadMatrix.h>
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class WaterUpDownDrivenPreAttack : public WaterUpDownAnmDrivenMove {
    SEAD_RTTI_OVERRIDE(WaterUpDownDrivenPreAttack, WaterUpDownAnmDrivenMove)
public:
    explicit WaterUpDownDrivenPreAttack(const InitArg& arg);
    ~WaterUpDownDrivenPreAttack() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
    void m32(ksys::phys::CharacterController* controller) override;

    // static_param at offset 0x68
    const float* mTurnSpeed_s{};
    // dynamic_param at offset 0x70
    sead::Vector3f* mTargetPos_d{};
    sead::Matrix33f _78;
};
KSYS_CHECK_SIZE_NX150(WaterUpDownDrivenPreAttack, 0xa0);

}  // namespace uking::action
