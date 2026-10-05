#pragma once

#include <math/seadVector.h>
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class CircleMove : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(CircleMove, ksys::act::ai::Ai)
public:
    explicit CircleMove(const InitArg& arg);
    ~CircleMove() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

    virtual void m34(sead::Vector3f* out) = 0;
    virtual void m35(const sead::Vector3f& target_pos);
    virtual void m36(const sead::Vector3f& target_pos);
    virtual f32 m37() { return *mRadius_s; }
    virtual void m38(sead::Vector3f* out, f32 angle, f32 radius);

protected:
    // Declaration only; native w1 bit 0 gates direction selection.
    void sub_710034E90C(bool keep_direction);

    // static_param at offset 0x38
    const int* mDirection_s{};
    // static_param at offset 0x40
    const float* mRadius_s{};
    // static_param at offset 0x48
    const float* mRadiusMargin_s{};
    // static_param at offset 0x50
    const float* mSpeed_s{};
    f32 _58 = 0.0f;
    f32 _5c = 1.0f;
};

}  // namespace uking::ai
