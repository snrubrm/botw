#pragma once

#include "Game/AI/AI/aiTargetPosAI.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class TargetTargetPos : public TargetPosAI {
    SEAD_RTTI_OVERRIDE(TargetTargetPos, TargetPosAI)
public:
    explicit TargetTargetPos(const InitArg& arg);
    ~TargetTargetPos() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

    void m35(sead::Vector3f* pos) override;

protected:
    // static_param at offset 0x40
    const float* mAddSpeed_s{};
};

}  // namespace uking::ai
