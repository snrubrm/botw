#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"
#include "KingSystem/System/Timer.h"

namespace uking::action {

class RemainsWaterBulletAction : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(RemainsWaterBulletAction, ksys::act::ai::Action)
public:
    explicit RemainsWaterBulletAction(const InitArg& arg);
    ~RemainsWaterBulletAction() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
    virtual void m32() = 0;
    virtual void m33();
    virtual void m34();

    // 0x7100230304 (placeholder name): how much of the sign animation is left (1 without one).
    f32 sub_7100230304();

    // static_param at offset 0x20
    const int* mSignASFrame_s{};
    // static_param at offset 0x28
    const float* mMaxRotSpd_s{};
    // static_param at offset 0x30
    const float* mMinRotSpd_s{};
    // static_param at offset 0x38
    const float* mEndTimer_s{};
    // static_param at offset 0x40
    const bool* mIgnroeWater_s{};
    // static_param at offset 0x48
    const bool* mIgnoreGravity_s{};
    // static_param at offset 0x50
    const bool* mUseParentRevDirRot_s{};
    // static_param at offset 0x58
    sead::SafeString mSignASName_s{};
    bool _68 = false;
    ksys::Timer _6c;
    bool _78 = false;
    f32 _7c = 1.0f;
};

KSYS_CHECK_SIZE_NX150(RemainsWaterBulletAction, 0x80);

}  // namespace uking::action
