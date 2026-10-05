#pragma once

#include "Game/AI/AI/aiPriestBossActorRoot.h"
#include <prim/seadBitFlag.h>
#include "Game/AI/aiUnk_7102357d20.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class PriestBossActorNormalRoot : public PriestBossActorRoot {
    SEAD_RTTI_OVERRIDE(PriestBossActorNormalRoot, PriestBossActorRoot)
public:
    explicit PriestBossActorNormalRoot(const InitArg& arg);
    ~PriestBossActorNormalRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

    virtual bool m36();

protected:
    void sub_710050DC18(bool from_sync);

    // aitree_variable at offset 0x40
    int* mEquipWeaponBufIndex_a{};
    Unk_7102411950 _48{mActor, 0x80000db};
    sead::BitFlag8 _80;
};
KSYS_CHECK_SIZE_NX150(PriestBossActorNormalRoot, 0x88);

}  // namespace uking::ai
