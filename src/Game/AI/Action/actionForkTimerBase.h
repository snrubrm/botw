#pragma once

#include "Game/AI/Action/actionFork.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ForkTimerBase : public Fork {
    SEAD_RTTI_OVERRIDE(ForkTimerBase, Fork)
public:
    explicit ForkTimerBase(const InitArg& arg);
    ~ForkTimerBase() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
    virtual int m32();
    virtual float m33();

    float _30 = 0.0f;
};

}  // namespace uking::action
