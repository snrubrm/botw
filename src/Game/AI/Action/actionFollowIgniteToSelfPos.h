#pragma once

#include "Game/AI/Action/actionRotateTurnToTarget.h"
#include "Game/AI/Action/actionUnk_71023c8678.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class FollowIgniteToSelfPos : public RotateTurnToTarget {
    SEAD_RTTI_OVERRIDE(FollowIgniteToSelfPos, RotateTurnToTarget)
public:
    explicit FollowIgniteToSelfPos(const InitArg& arg);
    ~FollowIgniteToSelfPos() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
    bool handleMessage_(const ksys::Message* message) override;

    Unk_71023c8678 _78{this};
};

}  // namespace uking::action
