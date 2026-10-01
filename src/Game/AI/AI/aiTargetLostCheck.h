#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class TargetLostCheck : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(TargetLostCheck, ksys::act::ai::Ai)
public:
    explicit TargetLostCheck(const InitArg& arg);
    ~TargetLostCheck() override;

    bool isFailed() const override;
    bool isFinished() const override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const int* mLostTimer_s{};
    // static_param at offset 0x40
    const bool* mIsLostByScaffold_s{};
    // static_param at offset 0x48
    const bool* mIsLostByTeached_s{};
    f32 _50 = 0;
    int _54 = 0;
    int _58 = 0;
};
KSYS_CHECK_SIZE_NX150(TargetLostCheck, 0x60);

}  // namespace uking::ai
