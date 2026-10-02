#pragma once

#include "Game/AI/AI/aiCliffCheckSelect.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class CliffCheckTargetDirSelect : public CliffCheckSelect {
    SEAD_RTTI_OVERRIDE(CliffCheckTargetDirSelect, CliffCheckSelect)
public:
    explicit CliffCheckTargetDirSelect(const InitArg& arg);
    ~CliffCheckTargetDirSelect() override;

    void calc_() override;
    void loadParams_() override;

    void m34(sead::Vector3f* out) override;

protected:
    // dynamic_param at offset 0x50
    sead::Vector3f* mTargetPos_d{};
};

}  // namespace uking::ai
