#pragma once

#include "Game/AI/Action/actionOnetimeStopASPlay.h"
#include "Game/AI/Action/actionUnk_71023c8600.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class IgniteActorReloadBase : public OnetimeStopASPlay {
    SEAD_RTTI_OVERRIDE(IgniteActorReloadBase, OnetimeStopASPlay)
public:
    explicit IgniteActorReloadBase(const InitArg& arg);
    ~IgniteActorReloadBase() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
    bool isFailed() const override;
    bool isFinished() const override;

    Unk_71023c8600 _48{this};
};

}  // namespace uking::action
