#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"
#include "KingSystem/ActorSystem/actBaseProcHandle.h"

namespace ksys::phys {
class RigidBody;
}

namespace uking::action {

class ItemAmiiboCreateFromDropTable : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(ItemAmiiboCreateFromDropTable, ksys::act::ai::Action)
public:
    explicit ItemAmiiboCreateFromDropTable(const InitArg& arg);
    ~ItemAmiiboCreateFromDropTable() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
    // 0x71001bbdec (placeholder name): fills _8d0 with random offsets and clears _a60.
    void sub_71001BBDEC();

    // Filled from the PairActor_N / FlagActor_N / NotFlagActor_N strings by parsePairActor / parseFlagActor
    // (layout not decompiled yet).
    struct PairActor {
        sead::FixedSafeString<64> first;
        sead::FixedSafeString<64> second;
    };
    struct FlagActor {
        sead::FixedSafeString<128> actor;
        sead::FixedSafeString<64> flag;
    };
    // 0x71001bfa64 / 0x71001bfe54 (CSV names): split a comma-separated PairActor / FlagActor string.
    void parsePairActor(PairActor* out, const sead::SafeString& names);
    void parseFlagActor(FlagActor* out, const sead::SafeString& names);
    // 0x71001bce24 (CSV name): places the drop area body (_a80) on the ground below `pos`, aligned to the ground
    // normal, and adds it to the world.
    void initCreatePosition(const sead::Vector3f& pos);
    // 0x71001bccc8 (CSV name): CreateOffset in the frame facing the player (z toward the player, y up).
    void calculateCreatePosition(sead::Vector3f* out);

    // static_param at offset 0x20
    const int* mCreateInterval_s{};
    // static_param at offset 0x28
    const int* mClearSealNum_s{};
    // static_param at offset 0x30
    const int* mHitRateAdjustStart_s{};
    // static_param at offset 0x38
    const int* mHitRateAdjustEnd_s{};
    // static_param at offset 0x40
    const float* mCreateArea_s{};
    // static_param at offset 0x48
    const float* mBigHitRate1st_s{};
    // static_param at offset 0x50
    const float* mBigHitRate2nd_s{};
    // static_param at offset 0x58
    const float* mBigHitRate3rd_s{};
    // static_param at offset 0x60
    const float* mGreatHitRate1st_s{};
    // static_param at offset 0x68
    const float* mGreatHitRate2nd_s{};
    // static_param at offset 0x70
    const float* mGreatHitRate3rd_s{};
    // static_param at offset 0x78
    const float* mDropNumRate1st_s{};
    // static_param at offset 0x80
    const float* mDropNumRate2nd_s{};
    // static_param at offset 0x88
    const float* mDropNumRate3rd_s{};
    // static_param at offset 0x90
    const float* mSmallHitRate1st_s{};
    // static_param at offset 0x98
    const float* mSmallHitRate2nd_s{};
    // static_param at offset 0xa0
    const float* mSmallHitRate3rd_s{};
    // static_param at offset 0xa8
    sead::SafeString mPairActor_0_s{};
    // static_param at offset 0xb8
    sead::SafeString mPairActor_1_s{};
    // static_param at offset 0xc8
    sead::SafeString mPairActor_2_s{};
    // static_param at offset 0xd8
    sead::SafeString mFlagActor_0_s{};
    // static_param at offset 0xe8
    sead::SafeString mFlagActor_1_s{};
    // static_param at offset 0xf8
    sead::SafeString mFlagActor_2_s{};
    // static_param at offset 0x108
    sead::SafeString mNotFlagActor_0_s{};
    // static_param at offset 0x118
    sead::SafeString mNotFlagActor_1_s{};
    // static_param at offset 0x128
    const sead::Vector3f* mCreateOffset_s{};
    u8 _130[0x210 - 0x130];
    PairActor mPairActors[3];
    FlagActor mFlagActors[5];
    // Random drop offsets in [-1, 1]^2, each at least 0.5 away from the three before it (sub_71001BBDEC).
    sead::Vector2f _8d0[50];
    bool _a60;
    u8 _a61[0xa68 - 0xa61];
    ksys::act::BaseProcHandle _a68;
    u8 _a78[0xa80 - 0xa78];
    ksys::phys::RigidBody* _a80{};
    u8 _a88[0xa8d - 0xa88];
    bool _a8d = false;
};

}  // namespace uking::action
