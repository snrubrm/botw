#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class BowChildDeviceGaleArrow : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(BowChildDeviceGaleArrow, ksys::act::ai::Action)
public:
    explicit BowChildDeviceGaleArrow(const InitArg& arg);
    ~BowChildDeviceGaleArrow() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const float* mMaxMoveSpeed_s{};
    // static_param at offset 0x28
    const float* mRotateSpeedMax_s{};
    // static_param at offset 0x30
    const float* mRotateAccel_s{};
    // static_param at offset 0x38
    const float* mRotateOffset_s{};
    // static_param at offset 0x40
    const sead::Vector3f* mCenterOffset_s{};
    // dynamic_param at offset 0x48
    int* mID_d{};
    // dynamic_param at offset 0x50
    float* mXRotateAngle_d{};
    // dynamic_param at offset 0x58
    ksys::act::BaseProcLink* mParentActor_d{};
    s32 _60 = 0;
    bool _64 = false;
    u8 _65[0x3];
    f32 _68 = 0.0f;
    f32 _6c = 0.0f;
    f32 _70 = 0.0f;
    f32 _74 = 0.0f;
    u64 _78 = 0;
    s32 _80 = 0;
    u8 _84[0x4];
};
KSYS_CHECK_SIZE_NX150(BowChildDeviceGaleArrow, 0x88);

}  // namespace uking::action
