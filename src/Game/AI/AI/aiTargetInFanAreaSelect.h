#pragma once

#include "Game/AI/AI/aiTargetInAreaSelect.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class TargetInFanAreaSelect : public TargetInAreaSelect {
    SEAD_RTTI_OVERRIDE(TargetInFanAreaSelect, TargetInAreaSelect)
public:
    explicit TargetInFanAreaSelect(const InitArg& arg);
    ~TargetInFanAreaSelect() override;

    bool isFailed() const override;
    bool isFinished() const override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    bool isChangeable() const override;
    void loadParams_() override;

    virtual bool m34();
    virtual void m35(ksys::act::ai::InlineParamPack* params);
    virtual void m36(ksys::act::ai::InlineParamPack* params);
    virtual void m37(sead::Vector3f* out);
    virtual void m38(sead::Vector3f* out);

protected:
    // static_param at offset 0x40
    const float* mNearYMax_s{};
    // static_param at offset 0x48
    const float* mNearYMin_s{};
    // static_param at offset 0x50
    const float* mFarYMax_s{};
    // static_param at offset 0x58
    const float* mFarYMin_s{};
    // static_param at offset 0x60
    const float* mXZRange_s{};
    // static_param at offset 0x68
    const float* mAngle_s{};
    // dynamic_param at offset 0x70
    sead::Vector3f* mTargetPos_d{};
};

}  // namespace uking::ai
