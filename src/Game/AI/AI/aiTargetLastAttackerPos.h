#pragma once

#include "Game/AI/AI/aiTargetPosAI.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class TargetLastAttackerPos : public TargetPosAI {
    SEAD_RTTI_OVERRIDE(TargetLastAttackerPos, TargetPosAI)
public:
    explicit TargetLastAttackerPos(const InitArg& arg);
    ~TargetLastAttackerPos() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

    void m35(sead::Vector3f* pos) override;

protected:
};

}  // namespace uking::ai
