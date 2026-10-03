#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ForkFollowGround : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(ForkFollowGround, ksys::act::ai::Action)
public:
    explicit ForkFollowGround(const InitArg& arg);
    ~ForkFollowGround() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    struct Params {
        // static_param at offset 0x20
        const int* mUpdateFrameCountAfterNoMove_s{};
        // static_param at offset 0x28
        const float* mRotSpd_s{};
        // static_param at offset 0x30
        const float* mBaseRotRatio_s{};
        // static_param at offset 0x38
        const float* mUpdateTargetUpDirMinAngle_s{};
        // static_param at offset 0x40
        const float* mUpdateTargetUpDirRatio_s{};
    };
    Params mParams;
    u8 _48[0x18];
    u64 _60 = 0;
    f32 _68 = 0.0f;
    u8 _6c[0x24];
    f32 _90 = 0.0f;
    u8 _94[0x4];
};
KSYS_CHECK_SIZE_NX150(ForkFollowGround, 0x98);

}  // namespace uking::action
