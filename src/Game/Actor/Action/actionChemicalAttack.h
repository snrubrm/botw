#pragma once

#include "Game/Actor/Action/actionEmitAttackBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ChemicalAttack : public EmitAttackBase {
    SEAD_RTTI_OVERRIDE(ChemicalAttack, EmitAttackBase)
public:
    explicit ChemicalAttack(const InitArg& arg);
    ~ChemicalAttack() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
    float m34() override;
    int m35() override;
    int m36() override;

    // static_param at offset 0x80
    const bool* mIsUseMyRange_s{};
    // static_param at offset 0x88
    const int* mAttackType_s{};
};

}  // namespace uking::action
