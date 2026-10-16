#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"
#include "KingSystem/System/Timer.h"
#include <math/seadMatrix.h>

namespace uking::action {

class SiteBossSwordSlowMove : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(SiteBossSwordSlowMove, ksys::act::ai::Action)
public:
    explicit SiteBossSwordSlowMove(const InitArg& arg);
    ~SiteBossSwordSlowMove() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const float* mAfterImage0AppearFrame_s{};
    // static_param at offset 0x28
    const float* mAfterImage1AppearFrame_s{};
    // static_param at offset 0x30
    const float* mAppearFrame_s{};
    // dynamic_param at offset 0x38
    float* mCurrentFrame_d{};
    // dynamic_param at offset 0x40
    sead::Vector3f* mTargetPos_d{};
    // dynamic_param at offset 0x48
    sead::Vector3f* mMoveDstPos_d{};
    // dynamic_param at offset 0x50
    sead::Vector3f* mAfterImage0Pos_d{};
    // dynamic_param at offset 0x58
    sead::Vector3f* mAfterImage1Pos_d{};
    ksys::Timer _60;
    sead::Matrix33f _6c;
    bool _90 = false;
    u8 _91[0x7];
};
KSYS_CHECK_SIZE_NX150(SiteBossSwordSlowMove, 0x98);

}  // namespace uking::action
