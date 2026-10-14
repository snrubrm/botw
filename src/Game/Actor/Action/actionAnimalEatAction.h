#pragma once

#include <prim/seadEnum.h>
#include "KingSystem/System/Timer.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class AnimalEatAction : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(AnimalEatAction, ksys::act::ai::Action)
public:
    explicit AnimalEatAction(const InitArg& arg);
    ~AnimalEatAction() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    SEAD_ENUM(Bit, _0, _1)

    void calc_() override;
    virtual int m32();

    // static_param at offset 0x20
    const float* mMinFramesPlayWaitAS_s{};
    // dynamic_param at offset 0x28
    ksys::act::BaseProcLink* mTargetActor_d{};
    sead::BitFlag8 _30;
    ksys::Timer _34{0, 0};
};

}  // namespace uking::action
