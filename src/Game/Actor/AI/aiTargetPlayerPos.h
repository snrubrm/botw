#pragma once

#include "Game/Actor/AI/aiTargetActorPos.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class TargetPlayerPos : public TargetActorPos {
    SEAD_RTTI_OVERRIDE(TargetPlayerPos, TargetActorPos)
public:
    explicit TargetPlayerPos(const InitArg& arg);
    ~TargetPlayerPos() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

    void m35(sead::Vector3f* pos) override;

protected:
};

}  // namespace uking::ai
