#pragma once

#include "Game/AI/AI/aiPriestBossMode.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class PriestBossSynchroMode : public PriestBossMode {
    SEAD_RTTI_OVERRIDE(PriestBossSynchroMode, PriestBossMode)
public:
    explicit PriestBossSynchroMode(const InitArg& arg);
    ~PriestBossSynchroMode() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // aitree_variable at offset 0x40
    int* mEquipWeaponBufIndex_a{};
    // aitree_variable at offset 0x48
    bool* mReturnFromBananaMode_a{};
    u32 _50 = 0;
};
KSYS_CHECK_SIZE_NX150(PriestBossSynchroMode, 0x58);

}  // namespace uking::ai
