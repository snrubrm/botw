#pragma once

#include <xlink2/xlink2HandleELink.h>
#include "KingSystem/ActorSystem/actAiAction.h"
#include "KingSystem/Event/evtResidentEvent.h"

namespace uking::action {

class RemainElectricCannonCharge : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(RemainElectricCannonCharge, ksys::act::ai::Action)
public:
    explicit RemainElectricCannonCharge(const InitArg& arg);
    ~RemainElectricCannonCharge() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const float* mChargeTime_s{};
    f32 _28 = 0;
    xlink2::HandleELink _30;
    bool _40 = false;
    ksys::evt::ResidentEvent _48;
};
KSYS_CHECK_SIZE_NX150(RemainElectricCannonCharge, 0x218);


}  // namespace uking::action
