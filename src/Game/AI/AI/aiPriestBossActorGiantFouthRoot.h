#pragma once

#include "Game/AI/AI/aiPriestBossActorGiantRoot.h"
#include "Game/AI/aiUnk_7102357d20.h"
#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/System/Timer.h"

namespace uking::ai {

class PriestBossActorGiantFouthRoot : public PriestBossActorGiantRoot {
    SEAD_RTTI_OVERRIDE(PriestBossActorGiantFouthRoot, PriestBossActorGiantRoot)
public:
    explicit PriestBossActorGiantFouthRoot(const InitArg& arg);
    ~PriestBossActorGiantFouthRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

    const char* m36() override;
    Attack m46() override;
    virtual bool m48();

protected:
    // static_param at offset 0xf8
    const float* mStompDistance_s{};
    // static_param at offset 0x100
    const float* mStompInAreaTimer_s{};
    // static_param at offset 0x108
    const bool* mStompAction_s{};
    // static_param at offset 0x110
    const bool* mStompAlwaysChange_s{};
    // aitree_variable at offset 0x118
    void* mPriestBossMetaAIUnit_a{};
    ksys::Timer _120{};
    Unk_71023b1860 _130{mActor, 0x80000d5};
};
KSYS_CHECK_SIZE_NX150(PriestBossActorGiantFouthRoot, 0x168);

}  // namespace uking::ai
