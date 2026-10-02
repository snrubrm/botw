#pragma once

#include "Game/AI/AI/aiPriestBossMode.h"
#include "Game/AI/aiUnk_7102357210.h"
#include "Game/AI/aiUnk_7102357d20.h"
#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/System/Timer.h"

namespace uking::ai {

class PriestBossCloneBulletRoot : public PriestBossMode {
    SEAD_RTTI_OVERRIDE(PriestBossCloneBulletRoot, PriestBossMode)
public:
    explicit PriestBossCloneBulletRoot(const InitArg& arg);
    ~PriestBossCloneBulletRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;
    bool handleMessage_(const ksys::Message& message) override;

protected:
    // aitree_variable at offset 0x40
    void* mPriestBossMetaAIUnit_a{};
    ksys::Timer _48{};
    ksys::act::BaseProcLink _58;
    Unk_7102450978 _68;
    Unk_71023b1860 _e0{mActor, 0x80000d5};
    bool _118 = false;
};
KSYS_CHECK_SIZE_NX150(PriestBossCloneBulletRoot, 0x120);

}  // namespace uking::ai
