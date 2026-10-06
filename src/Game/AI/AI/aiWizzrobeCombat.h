#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/ActorSystem/actBaseProcHandle.h"

namespace uking::ai {

class WizzrobeCombat : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(WizzrobeCombat, ksys::act::ai::Ai)
public:
    explicit WizzrobeCombat(const InitArg& arg);
    ~WizzrobeCombat() override;

    bool isChangeable() const override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const int* mWeatherMagicRate_s{};
    // static_param at offset 0x40
    const int* mSummonRate_s{};
    // static_param at offset 0x48
    const int* mSummonBufferSize_s{};
    // static_param at offset 0x50
    const int* mMaxHeightLevel_s{};
    // static_param at offset 0x58
    const int* mSummonCount_s{};
    // static_param at offset 0x60
    const float* mAttackLength_s{};
    // static_param at offset 0x68
    const float* mHeightOffset_s{};
    // static_param at offset 0x70
    sead::SafeString mSummonBufferKey_s{};
    // static_param at offset 0x80
    const sead::Vector3f* mTargetOffset_s{};
    // aitree_variable at offset 0x88
    int* mSummonCount_a{};
    // aitree_variable at offset 0x90
    bool* mIsWizzrobeInBattleAreaFlag_a{};
    ksys::act::BaseProcHandle _98;
    // The rest (0xa8 - 0x5a0: FixedSafeString<64> + SafeString arrays) is not recovered yet.
    u8 _a8[0x5a0 - 0xa8];
};
KSYS_CHECK_SIZE_NX150(WizzrobeCombat, 0x5a0);

}  // namespace uking::ai
