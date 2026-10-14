#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"
#include <math/seadVector.h>

namespace uking::action {

class ASPlayRotateTurnToTarget : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(ASPlayRotateTurnToTarget, ksys::act::ai::Action)
public:
    explicit ASPlayRotateTurnToTarget(const InitArg& arg);
    ~ASPlayRotateTurnToTarget() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
    virtual void m32();
    virtual void m33(ksys::act::Actor* actor, float x);
    virtual void m34();

    // static_param at offset 0x20
    const float* mAngSpd_s{};
    // static_param at offset 0x28
    const bool* mIsJumpType_s{};
    // static_param at offset 0x30
    const bool* mIsChangeable_s{};
    // static_param at offset 0x38
    sead::SafeString mASName_s{};
    // dynamic_param at offset 0x48
    sead::Vector3f* mTargetPos_d{};
    sead::Vector3f _50 = sead::Vector3f::ey;
    sead::Vector3f _5c{0, 0, 0};
    f32 _68 = 0;
    f32 _6c = 0;
    bool _70 = false;
};

KSYS_CHECK_SIZE_NX150(ASPlayRotateTurnToTarget, 0x78);

}  // namespace uking::action
