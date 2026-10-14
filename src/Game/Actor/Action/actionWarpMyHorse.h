#pragma once

#include <math/seadMatrix.h>
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class WarpMyHorse : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(WarpMyHorse, ksys::act::ai::Action)
public:
    explicit WarpMyHorse(const InitArg& arg);
    ~WarpMyHorse() override;

    bool init_(sead::Heap* heap) override;
    void loadParams_() override;
    bool oneShot_() override;

protected:
    // dynamic_param at offset 0x20
    float* mPositionX_d{};
    // dynamic_param at offset 0x28
    float* mPositionY_d{};
    // dynamic_param at offset 0x30
    float* mPositionZ_d{};
    // dynamic_param at offset 0x38
    float* mDirection_d{};
    sead::Matrix34f _40;
};
KSYS_CHECK_SIZE_NX150(WarpMyHorse, 0x70);

}  // namespace uking::action
