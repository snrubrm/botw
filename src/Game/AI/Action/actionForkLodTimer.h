#pragma once

#include "Game/AI/Action/actionFork.h"
#include "KingSystem/ActorSystem/actAiAction.h"
#include "KingSystem/ActorSystem/actUnk_7100d3bc4c.h"

namespace uking::action {

class ForkLodTimer : public Fork {
    SEAD_RTTI_OVERRIDE(ForkLodTimer, Fork)
public:
    explicit ForkLodTimer(const InitArg& arg);
    ~ForkLodTimer() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x30
    const int* mWaitFrame_s{};
    ksys::act::Unk_7100d3bce4 _38{mActor};
};

}  // namespace uking::action
