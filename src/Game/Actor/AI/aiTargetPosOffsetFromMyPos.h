#pragma once

#include "Game/Actor/AI/aiOffsetTargetPos.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class TargetPosOffsetFromMyPos : public OffsetTargetPos {
    SEAD_RTTI_OVERRIDE(TargetPosOffsetFromMyPos, OffsetTargetPos)
public:
    explicit TargetPosOffsetFromMyPos(const InitArg& arg);
    ~TargetPosOffsetFromMyPos() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

    void m36(sead::Vector3f* pos) override;

protected:
    // dynamic_param at offset 0x68
    sead::Vector3f* mTargetPos_d{};
};

}  // namespace uking::ai
