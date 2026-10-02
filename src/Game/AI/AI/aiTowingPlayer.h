#pragma once

#include "Game/AI/AI/aiTowing.h"
#include "Game/AI/aiUnk_7102357d20.h"
#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/System/Timer.h"
#include "KingSystem/Utils/Thread/MessageTransceiverTxOnly.h"

namespace uking::ai {

class TowingPlayer : public Towing {
    SEAD_RTTI_OVERRIDE(TowingPlayer, Towing)
public:
    explicit TowingPlayer(const InitArg& arg);
    ~TowingPlayer() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

    void m38() override;

protected:
    // static_param at offset 0xc8
    const float* mInterruptDef_s{};
    // static_param at offset 0xd0
    const float* mCheckPlayerStateDef_s{};
    /* 0x0d8 */ Unk_710242cb98 _d8{mActor, 0x8000025};
    /* 0x0f0 */ Unk_710242cbc0 _f0{mActor, 0x8000026};
    /* 0x108 */ ksys::MessageTransceiverTxOnly _108{*mActor};
    /* 0x158 */ ksys::Timer _158;  // CheckPlayerStateDef
    /* 0x164 */ ksys::Timer _164;  // InterruptDef
};
KSYS_CHECK_SIZE_NX150(TowingPlayer, 0x170);

}  // namespace uking::ai
