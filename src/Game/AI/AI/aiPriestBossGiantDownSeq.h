#pragma once

#include "Game/AI/AI/aiPriestBossMode.h"
#include "Game/AI/aiUnk_7102357210.h"
#include "Game/AI/aiUnk_7102357d20.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class PriestBossGiantDownSeq : public PriestBossMode {
    SEAD_RTTI_OVERRIDE(PriestBossGiantDownSeq, PriestBossMode)
public:
    explicit PriestBossGiantDownSeq(const InitArg& arg);
    ~PriestBossGiantDownSeq() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;
    bool handleMessage_(const ksys::Message& message) override;
    bool handleAck_(const ksys::MessageAck& ack) override;

protected:
    // static_param at offset 0x40
    const bool* mRecoverIfAlreadyDown_s{};
    // static_param at offset 0x48
    const bool* mIsUseRecover_s{};
    // static_param at offset 0x50
    sead::SafeString mHitGroundASName_s{};
    // aitree_variable at offset 0x60
    float* mKeepDistFromGround_a{};
    // aitree_variable at offset 0x68
    bool* mIsActive_a{};
    // aitree_variable at offset 0x70
    bool* mIsArrivedAtDestination_a{};
    // aitree_variable at offset 0x78
    sead::Vector3f* mDestinationPos_a{};
    Unk_71023dbd40 _80{mActor, 0x80000d7};
    Unk_71024509a8 _b0;
    sead::Vector3f _f8{0, 0, 0};
    bool _104 = false;
    bool _105 = false;
};
KSYS_CHECK_SIZE_NX150(PriestBossGiantDownSeq, 0x108);

}  // namespace uking::ai
