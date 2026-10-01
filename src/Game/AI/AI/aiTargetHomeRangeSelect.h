#pragma once

#include "Game/AI/AI/aiRangeSelect.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class TargetHomeRangeSelect : public RangeSelect {
    SEAD_RTTI_OVERRIDE(TargetHomeRangeSelect, RangeSelect)
public:
    explicit TargetHomeRangeSelect(const InitArg& arg);
    ~TargetHomeRangeSelect() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

    f32 m38() override;

protected:
};

}  // namespace uking::ai
