#pragma once

#include "Game/AI/Action/actionForkAttackWithWeaponOrWithout.h"
#include "Game/AI/aiUnk_7100720AB0.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ForkSeqNoWeaponAttack : public ForkAttackWithWeaponOrWithout {
    SEAD_RTTI_OVERRIDE(ForkSeqNoWeaponAttack, ForkAttackWithWeaponOrWithout)
public:
    explicit ForkSeqNoWeaponAttack(const InitArg& arg);
    ~ForkSeqNoWeaponAttack() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x50
    const int* mAttackType_s{};
    // static_param at offset 0x58
    const bool* mIsImpulseLarge_s{};
    // static_param "ExcludeAtkName%d" at offsets 0x60 / 0x70
    sead::SafeString mExcludeAtkName_s[2];
    /* 0x80 */ Unk_7100720ab0 _80{mActor};
};

}  // namespace uking::action
