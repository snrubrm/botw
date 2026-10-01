#pragma once

#include "Game/AI/AI/aiEnemyRecognizeTargetBase.h"
#include "Game/AI/aiUnk_7102357d20.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class EnemyDemoSumonRecgTgt : public EnemyRecognizeTargetBase {
    SEAD_RTTI_OVERRIDE(EnemyDemoSumonRecgTgt, EnemyRecognizeTargetBase)
public:
    explicit EnemyDemoSumonRecgTgt(const InitArg& arg);
    ~EnemyDemoSumonRecgTgt() override;
    bool m34() override;
    bool m35() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x128
    const bool* mOnlyOne_s{};
    // static_param at offset 0x130
    const bool* mIsBroadCastOnlyOne_s{};
    // static_param at offset 0x138
    sead::SafeString mDemoName_s{};
    // static_param at offset 0x148
    sead::SafeString mEntryPoint_s{};
    Unk_71023d31f8 _158{mActor, 0x8000044};
};

}  // namespace uking::ai
