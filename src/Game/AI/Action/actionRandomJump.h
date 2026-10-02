#pragma once

#include <math/seadMatrix.h>
#include "KingSystem/System/VFRValue.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class RandomJump : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(RandomJump, ksys::act::ai::Action)
public:
    explicit RandomJump(const InitArg& arg);
    ~RandomJump() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;
    bool isFinished() const override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const float* mAngleLimit_s{};
    // static_param at offset 0x28
    const float* mHeightMin_s{};
    // static_param at offset 0x30
    const float* mHeightMaxOffset_s{};
    // static_param at offset 0x38
    const float* mDistanceMin_s{};
    // static_param at offset 0x40
    const float* mDistanceMaxOffset_s{};
    // static_param at offset 0x48
    const bool* mIsReturnByHitWall_s{};
    // static_param at offset 0x50
    sead::SafeString mASName_s{};
    ksys::VFRValue _60;
    u8 _6c[0xc];
    u8 _78 = 0;
    sead::Matrix33f _7c;
    sead::Vector3f _a0;
    bool _ac = false;
};

}  // namespace uking::action
