#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class OnRagdollSelect : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(OnRagdollSelect, ksys::act::ai::Ai)
public:
    explicit OnRagdollSelect(const InitArg& arg);
    ~OnRagdollSelect() override;

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
};

}  // namespace uking::ai
