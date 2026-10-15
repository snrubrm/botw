#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/ActorSystem/actBaseProcHandle.h"
#include "KingSystem/ActorSystem/actInfoData.h"

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
    bool sub_71005FACD8();
    void sub_71005FA684();
    // 0x71005fc498: the ray from `start` to `end` hits something that is neither water nor bog
    bool sub_71005FC498(const sead::Vector3f& start, const sead::Vector3f& end);
    // 0x71005fc01c: changes to the "召喚魔法" child
    void sub_71005FC01C();
    // 0x71005fadc4: clears _59d, then changes to the "武器攻撃" child
    void sub_71005FADC4();
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
    struct SummonActor {
        sead::FixedSafeString<64> name;
        ksys::act::InfoData::InvalidLifeConditions conditions{};
        bool isFlyActor;
    };
    static_assert(sizeof(SummonActor) == 0x270);
    SummonActor* mSelectedSummonActor = nullptr;
    sead::SafeArray<SummonActor, 2> mSummonActors;
    s32 _590 = 0;
    s32 mMagicWeatherType = 0;
    s32 _598 = 0;
    bool _59c = false;
    bool _59d = true;
    u8 _59e[0x5a0 - 0x59e];
};
KSYS_CHECK_SIZE_NX150(WizzrobeCombat, 0x5a0);

}  // namespace uking::ai
