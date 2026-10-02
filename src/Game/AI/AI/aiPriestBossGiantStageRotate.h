#pragma once

#include "Game/AI/AI/aiPriestBossMode.h"
#include "Game/AI/aiUnk_7102357210.h"
#include "Game/AI/aiUnk_7102357d20.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class PriestBossGiantStageRotate : public PriestBossMode {
    SEAD_RTTI_OVERRIDE(PriestBossGiantStageRotate, PriestBossMode)
public:
    explicit PriestBossGiantStageRotate(const InitArg& arg);
    ~PriestBossGiantStageRotate() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

    void sub_710051C210();
    bool handleMessage_(const ksys::Message& message) override;

protected:
    // static_param at offset 0x40
    const int* mSendCommand_s{};
    // static_param at offset 0x48
    const bool* mSendOnThrowASEvent_s{};
    // static_param at offset 0x50
    const bool* mIsUseStartAction_s{};
    Unk_71023dbd40 _58{mActor, 0x80000d7};
    Unk_71024509a8 _88;
    void* _d0 = nullptr;
    Unk_7102409958 _d8{mActor, 0x80000da};
    Unk_7102413c08 _118{mActor, 0x80000de};
    u8 _140 = 0;
};
KSYS_CHECK_SIZE_NX150(PriestBossGiantStageRotate, 0x148);

}  // namespace uking::ai
