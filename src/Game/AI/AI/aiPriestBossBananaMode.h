#pragma once

#include <math/seadVector.h>
#include <prim/seadBitFlag.h>
#include <prim/seadEnum.h>
#include "Game/AI/AI/aiPriestBossMode.h"
#include "Game/AI/aiUnk_7102357d20.h"
#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/System/Timer.h"
#include "KingSystem/Utils/Thread/MessageTransceiverId.h"

namespace uking::ai {

class PriestBossBananaMode : public PriestBossMode {
    SEAD_RTTI_OVERRIDE(PriestBossBananaMode, PriestBossMode)
public:
    SEAD_ENUM(Flag, _0, _1, _2, _3)

    explicit PriestBossBananaMode(const InitArg& arg);
    ~PriestBossBananaMode() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;
    bool handleAck_(const ksys::MessageAck& ack) override;

protected:
    /* 0x40 */ Unk_7102411f48 _40{mActor, 0x80000d8};
    /* 0x68 */ ksys::MesTransceiverId _68;
    // static_param at offset 0x80
    const int* mHealAmount_s{};
    // static_param at offset 0x88
    const float* mTimeUpFrames_s{};
    // aitree_variable at offset 0x90
    bool* mReturnFromBananaMode_a{};
    /* 0x98 */ ksys::Timer _98{0, 0};
    /* 0xa4 */ sead::Vector3f _a4;
    /* 0xb0 */ sead::BitFlag16 _b0;
};
KSYS_CHECK_SIZE_NX150(PriestBossBananaMode, 0xb8);

}  // namespace uking::ai
