#pragma once

#include "Game/AI/Action/actionPriestBossClonesSpawnForDemo.h"
#include "Game/AI/aiUnk_7102357d20.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class PriestBossClonesSpawn : public PriestBossClonesSpawnForDemo {
    SEAD_RTTI_OVERRIDE(PriestBossClonesSpawn, PriestBossClonesSpawnForDemo)
public:
    explicit PriestBossClonesSpawn(const InitArg& arg);
    ~PriestBossClonesSpawn() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x88
    sead::SafeString mASNameForAITree_s{};
    // dynamic_param at offset 0x98
    int* mDelayFrame_d{};
    Unk_71023b1860 _a0{mActor, 0x80000d5};
    bool _d8 = false;
    bool _d9 = false;
};

}  // namespace uking::action
