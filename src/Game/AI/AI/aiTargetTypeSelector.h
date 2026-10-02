#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class TargetTypeSelector : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(TargetTypeSelector, ksys::act::ai::Ai)
public:
    explicit TargetTypeSelector(const InitArg& arg);
    ~TargetTypeSelector() override;

    bool isFailed() const override;
    bool isFinished() const override;
    bool isChangeable() const override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // aitree_variable at offset 0x38
    bool* mIsTrgTargetChangeToPlayer_a{};
    u32 _40 = -1;
};
KSYS_CHECK_SIZE_NX150(TargetTypeSelector, 0x48);

}  // namespace uking::ai
