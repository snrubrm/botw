#pragma once

#include "Game/AI/AI/aiTargetPosAI.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class TargetHomePos : public TargetPosAI {
    SEAD_RTTI_OVERRIDE(TargetHomePos, TargetPosAI)
public:
    explicit TargetHomePos(const InitArg& arg);
    ~TargetHomePos() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

    void m35(sead::Vector3f* pos) override;

protected:
};

}  // namespace uking::ai
