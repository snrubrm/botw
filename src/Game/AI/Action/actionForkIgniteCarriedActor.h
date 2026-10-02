#pragma once

#include "Game/AI/Action/actionFork.h"
#include "Game/AI/Action/actionUnk_71023c8600.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ForkIgniteCarriedActor : public Fork {
    SEAD_RTTI_OVERRIDE(ForkIgniteCarriedActor, Fork)
public:
    explicit ForkIgniteCarriedActor(const InitArg& arg);
    ~ForkIgniteCarriedActor() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    Unk_71023c8600 _30{this};
};

}  // namespace uking::action
