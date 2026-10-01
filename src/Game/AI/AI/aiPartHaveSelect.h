#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class PartHaveSelect : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(PartHaveSelect, ksys::act::ai::Ai)
public:
    explicit PartHaveSelect(const InitArg& arg);
    ~PartHaveSelect() override;

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

protected:
    void sub_71004F4758(ksys::act::ai::InlineParamPack* params);

    // static_param at offset 0x38
    const bool* mIsCheckEveryFrame_s{};
    // static_param at offset 0x40
    sead::SafeString mPartsKey_s{};
};

}  // namespace uking::ai
