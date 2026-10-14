#pragma once

#include <math/seadMatrix.h>
#include "KingSystem/ActorSystem/actAiAction.h"
#include "KingSystem/System/Timer.h"

namespace ksys::phys {
class RigidBody;
}

namespace uking::action {

class TornadoMove : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(TornadoMove, ksys::act::ai::Action)
public:
    explicit TornadoMove(const InitArg& arg);
    ~TornadoMove() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const float* mMaxAmplitude_s{};
    // static_param at offset 0x28
    const float* mMinAmplitude_s{};
    // static_param at offset 0x30
    const float* mMaxSpeed_s{};
    // static_param at offset 0x38
    const float* mAmplitudeAddRate_s{};
    // static_param at offset 0x40
    const float* mDeleteTimer_s{};
    // static_param at offset 0x48
    const float* mFrequency_s{};
    // static_param at offset 0x50
    const float* mIgnoreHitFrame_s{};
    ksys::Timer _58;
    ksys::Timer _64;
    f32 _70 = 0.0f;
    sead::Matrix33f _74;
    sead::Vector3f _98;
    ksys::Timer _a4;
    ksys::phys::RigidBody* _b0 = nullptr;
};
KSYS_CHECK_SIZE_NX150(TornadoMove, 0xb8);

}  // namespace uking::action
