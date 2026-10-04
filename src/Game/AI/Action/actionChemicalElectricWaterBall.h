#pragma once

#include "Game/AI/Action/actionChemicalAttackBall.h"
#include "Game/AI/aiActorLink.h"
#include "Game/AI/aiUnk_710244ECF0.h"
#include "KingSystem/ActorSystem/actAiAction.h"
#include "KingSystem/System/Timer.h"

namespace uking::action {

class ChemicalElectricWaterBall : public ChemicalAttackBall {
    SEAD_RTTI_OVERRIDE(ChemicalElectricWaterBall, ChemicalAttackBall)
public:
    explicit ChemicalElectricWaterBall(const InitArg& arg);
    ~ChemicalElectricWaterBall() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
    bool sub_71000DBC74();
    int m36() override;
    int m37() override;
    int m38() override;

    // static_param at offset 0x90
    const int* mDeleteTime_s{};
    // static_param at offset 0x98
    const float* mTargetScale_s{};
    // static_param at offset 0xa0
    const bool* mScaleKeep_s{};
    // aitree_variable at offset 0xa8
    void* mChemicalBulletBindActor_a{};
    /* 0xb0 */ ksys::Timer _b0{0.0f, 0.0f};
    /* 0xbc */ bool _bc = false;
    /* 0xc0 */ Unk_710244ecf0 _c0;
    /* 0x138 */ Unk_7102370e70 _138;
    /* 0x150 */ bool _150 = false;
    /* 0x151 */ bool _151 = false;
};

}  // namespace uking::action
