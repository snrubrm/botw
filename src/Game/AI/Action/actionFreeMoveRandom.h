#pragma once

#include "Game/AI/Action/actionFreeMove.h"
#include "KingSystem/ActorSystem/actAiAction.h"
#include "KingSystem/System/Timer.h"

namespace uking::action {

class FreeMoveRandom : public FreeMove {
    SEAD_RTTI_OVERRIDE(FreeMoveRandom, FreeMove)
public:
    explicit FreeMoveRandom(const InitArg& arg);
    ~FreeMoveRandom() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
    bool m32(ksys::phys::CharacterController* controller) override;
    void m33(ksys::phys::CharacterController* controller) override;
    bool m34() override;

    // static_param at offset 0xa8
    const float* mRandVertical_s{};
    // static_param at offset 0xb0
    const float* mRandHorizontal_s{};
    // static_param at offset 0xb8
    const float* mRandSpeedMax_s{};
    // static_param at offset 0xc0
    const float* mRandSpeedMin_s{};
    // static_param at offset 0xc8
    const float* mTargetDistance_s{};
    // static_param at offset 0xd0
    const float* mHeightMax_s{};
    // static_param at offset 0xd8
    const float* mHeightMin_s{};
    // static_param at offset 0xe0
    const float* mMoveAreaRadius_s{};
    sead::Vector3f _e8;
    sead::Vector3f _f4;
    f32 _100 = 0;
    f32 _104 = 0;
    f32 _108 = 0;
    ksys::Timer _10c;
};

}  // namespace uking::action
