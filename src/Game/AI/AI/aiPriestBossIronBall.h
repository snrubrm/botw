#pragma once

#include <container/seadSafeArray.h>
#include "Game/AI/aiUnk_7102357d20.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class PriestBossIronBall : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(PriestBossIronBall, ksys::act::ai::Ai)
public:

    explicit PriestBossIronBall(const InitArg& arg);
    ~PriestBossIronBall() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

    virtual void m34();
    virtual void m35(sead::Vector3f* out, s32 idx);

    bool sub_710051E678();
    void sub_710051E830();
    void sub_710051EBDC();
    void sub_710051EE40();
    void sub_710051F1FC();
    void sub_710051F3FC();
    void sub_710051F79C();

protected:
    // static_param at offset 0x38
    const int* mIronBallWaitThunderTime_s{};
    // static_param at offset 0x40
    const int* mChangeEndAnime_s{};
    // static_param at offset 0x48
    const float* mIronBallOffsetY_s{};
    // static_param at offset 0x50
    const float* mIronBallRadius_s{};
    // static_param at offset 0x58
    const float* mIronBallAngle_s{};
    // static_param at offset 0x60
    const float* mIronBallAngleOffset_s{};
    // static_param at offset 0x68
    const bool* mIsAfterAttack_s{};
    // static_param at offset 0x70
    sead::SafeString mIronSummonLeftBoneName_s{};
    // static_param at offset 0x80
    sead::SafeString mIronSummonRightBoneName_s{};
    // aitree_variable at offset 0x90
    void* mPriestBossMetaAIUnit_a{};
    bool _98 = false;
    bool _99 = false;
    bool _9a = false;
    bool _9b = false;
    sead::SafeArray<Unk_7102368740, 8> _a0;
    sead::SafeArray<Unk_7102409958, 8> _420;
    Unk_7102372510 _620{mActor, 0x8000008};
    s32 _650 = 0;
    s32 _654 = 0;
    Unk_7102409958 _658{mActor, 0x80000da};
    Unk_7102413c08 _698{mActor, 0x80000de};
};
KSYS_CHECK_SIZE_NX150(PriestBossIronBall, 0x6c0);

}  // namespace uking::ai
