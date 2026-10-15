#pragma once

#include <prim/seadEnum.h>
#include "Game/Actor/AI/aiPriestBoss.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class PriestBossSynchroMode : public PriestBoss {
    SEAD_RTTI_OVERRIDE(PriestBossSynchroMode, PriestBoss)
public:
    explicit PriestBossSynchroMode(const InitArg& arg);
    ~PriestBossSynchroMode() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

protected:
    // The children (0x71005309b0 is the text getter)
    SEAD_ENUM(Mode, 円陣弓,円陣突進,一列流星,一列突進,待機,終了)

    // aitree_variable at offset 0x40
    int* mEquipWeaponBufIndex_a{};
    // aitree_variable at offset 0x48
    bool* mReturnFromBananaMode_a{};
    u32 _50 = 0;
};
KSYS_CHECK_SIZE_NX150(PriestBossSynchroMode, 0x58);

}  // namespace uking::ai
