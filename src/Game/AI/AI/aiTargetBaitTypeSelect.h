#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class TargetBaitTypeSelect : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(TargetBaitTypeSelect, ksys::act::ai::Ai)
public:
    explicit TargetBaitTypeSelect(const InitArg& arg);
    ~TargetBaitTypeSelect() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void loadParams_() override;

    bool isFailed() const override { return getCurrentChild()->isFailed(); }
    bool isFinished() const override { return getCurrentChild()->isFinished(); }

protected:
    void sub_71005BC0B4(ksys::act::ai::InlineParamPack* params);

    // FIXME: remove this
    u8 pad_0x38[0x8];
    // aitree_variable at offset 0x40
    void* mTargetBaitActorLink_a{};
};

}  // namespace uking::ai
