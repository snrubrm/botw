#pragma once

#include "Game/AI/Action/actionFork.h"
#include "Game/AI/Action/actionUnk_71023c8600.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ForkForceIgniteCarriedActor : public Fork {
    SEAD_RTTI_OVERRIDE(ForkForceIgniteCarriedActor, Fork)
public:
    explicit ForkForceIgniteCarriedActor(const InitArg& arg);
    ~ForkForceIgniteCarriedActor() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x30
    const bool* mIsCheckAfterChildState_s{};
    Unk_71023c8600 _38{this};
};

}  // namespace uking::action
