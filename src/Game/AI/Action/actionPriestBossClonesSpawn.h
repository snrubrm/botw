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
    // 0x71002218d8 (declared only): out of line in the original.
    void sub_71002218D8();
    // 0x7100221b68 (declared only; 312 B): walks the AI tree like getDynamicParamImpl and calls the ParamPack setter
    // (here setString(value, key)) on every level that has the parameter.
    bool sub_7100221B68(const sead::SafeString& value, const sead::SafeString& key,
                        bool (ksys::act::ai::ParamPack::*setter)(const sead::SafeString&, const sead::SafeString&) const);
    void calc_() override;
    int m32() override;

    // static_param at offset 0x88
    sead::SafeString mASNameForAITree_s{};
    // dynamic_param at offset 0x98
    int* mDelayFrame_d{};
    Unk_71023b1860 _a0{mActor, 0x80000d5};
    bool _d8 = false;
    bool _d9 = false;
};

}  // namespace uking::action
