#pragma once

#include <math/seadMatrix.h>
#include "KingSystem/ActorSystem/actAiAction.h"
#include "KingSystem/ActorSystem/actBaseProcHandle.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"

namespace uking::action {

class TreasureBoxBurnedOut : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(TreasureBoxBurnedOut, ksys::act::ai::Action)
public:
    explicit TreasureBoxBurnedOut(const InitArg& arg);
    ~TreasureBoxBurnedOut() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // 0x710029bfdc (CSV AI_Action_TreasureBoxBurnedOut::spawnDropActor; declared only).
    void spawnDropActor();
    void calc_() override;

    ksys::act::BaseProcHandle _20;
    ksys::act::BaseProcLink _30;
    // aitree_variable at offset 0x40
    bool* mIsOpenTreasureBox_a{};
    // aitree_variable at offset 0x48
    sead::SafeString* mDropActorName_a{};
    // aitree_variable at offset 0x50
    void* mSharpWeaponAddParam_a{};
    sead::Matrix34f _58 = sead::Matrix34f::ident;
};

}  // namespace uking::action
