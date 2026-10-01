#pragma once

#include "KingSystem/System/Timer.h"
#include "Game/AI/Action/actionChemicalAttackBall.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ChemicalPhysBall : public ChemicalAttackBall {
    SEAD_RTTI_OVERRIDE(ChemicalPhysBall, ChemicalAttackBall)
public:
    explicit ChemicalPhysBall(const InitArg& arg);
    ~ChemicalPhysBall() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
    void m32() override;

    // static_param at offset 0x90
    const int* mDeleteTime_s{};
    sead::Vector3f _98 = sead::Vector3f::zero;
    f32 _a4 = 0;
    ksys::Timer _a8{0, 0};
    bool _b4 = false;
};

}  // namespace uking::action
