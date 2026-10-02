#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class SubsAngleSelect : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(SubsAngleSelect, ksys::act::ai::Ai)
public:
    explicit SubsAngleSelect(const InitArg& arg);
    ~SubsAngleSelect() override;

    bool isFailed() const override;
    bool isFinished() const override { return getCurrentChild()->isFinished(); }
    bool isChangeable() const override { return getCurrentChild()->isChangeable(); }

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // Inline-only in the original (name is a guess): dot product of the actor's front vector and the
    // direction to the target.
    f32 getFrontDot() const;

    // static_param at offset 0x38
    const float* mSubsAngle_s{};
    // static_param at offset 0x40
    const bool* mCheckOnce_s{};
    // static_param at offset 0x48
    const bool* mYRotOnly_s{};
    // dynamic_param at offset 0x50
    sead::Vector3f* mTargetPos_d{};
};

}  // namespace uking::ai
