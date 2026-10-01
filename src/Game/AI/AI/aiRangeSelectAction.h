#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class RangeSelectAction : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(RangeSelectAction, ksys::act::ai::Ai)
public:
    explicit RangeSelectAction(const InitArg& arg);
    ~RangeSelectAction() override;

    bool isFailed() const override {
        return mFlags.isOn(Flag::Failed) || getCurrentChild()->isFailed();
    }
    bool isFinished() const override {
        return mFlags.isOn(Flag::Finished) || getCurrentChild()->isFinished();
    }

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

    virtual void m34() = 0;
    virtual f32 m35();
    f32 sub_7100539F84();

protected:
    // static_param at offset 0x38
    const int* mWeaponIdx_s{};
    // static_param at offset 0x40
    const bool* mIsSelectEveryFrame_s{};
    // static_param at offset 0x48
    const bool* mIsRangeXZ_s{};
    // dynamic_param at offset 0x50
    sead::Vector3f* mTargetPos_d{};
};

}  // namespace uking::ai
