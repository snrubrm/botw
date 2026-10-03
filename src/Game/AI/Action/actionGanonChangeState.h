#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class GanonChangeState : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(GanonChangeState, ksys::act::ai::Action)
public:
    explicit GanonChangeState(const InitArg& arg);
    ~GanonChangeState() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;
    bool isChangeable() const override;

protected:
    void calc_() override;

    // dynamic_param at offset 0x20
    sead::Vector3f* mTargetPos_d{};
    bool _28 = false;
    u8 _29[0x3];
    f32 _2c = 0.0f;
    sead::Vector3f _30 = sead::Vector3f::zero;
    u8 _3c[0x34];
};
KSYS_CHECK_SIZE_NX150(GanonChangeState, 0x70);

}  // namespace uking::action
