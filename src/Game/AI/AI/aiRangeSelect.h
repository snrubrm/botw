#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class RangeSelect : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(RangeSelect, ksys::act::ai::Ai)
public:
    explicit RangeSelect(const InitArg& arg);
    ~RangeSelect() override;

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

    virtual f32 m34();
    virtual bool m35() { return false; }
    virtual void m36() {}
    virtual void m37() {}
    virtual f32 m38();

protected:
    void sub_71004BC154(ksys::act::ai::InlineParamPack* params);

protected:
    // static_param at offset 0x38
    const int* mWeaponIdx_s{};
    // static_param at offset 0x40
    const float* mFarDist_s{};
    // static_param at offset 0x48
    const bool* mIsSelectEveryFrame_s{};
};

}  // namespace uking::ai
