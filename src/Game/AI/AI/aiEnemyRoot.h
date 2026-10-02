#pragma once

#include "Game/AI/aiUnk_7102357210.h"
#include "Game/AI/aiUnk_7102357d20.h"
#include "KingSystem/ActorSystem/actAiAi.h"

// Unnamed 12-byte object embedded in EnemyRoot (ctor 0x7100700834, dtor 0x7100700840; both in another
// translation unit). Placeholder name is the ctor address.
class Unk_7100700834 {
public:
    Unk_7100700834();
    ~Unk_7100700834();

    u32 _0;
    u32 _4;
    bool _8;
};

// Unnamed 0x18-byte fall-height helper that EnemyRoot::init_ allocates (when FallHeight >= 0) and
// its destructor deletes; no vtable or out-of-line constructor. Its non-virtual functions are at
// 0x7100702370 / 0x7100702384 (same translation unit as Unk_7100700834). Placeholder name = first
// function address.
struct Unk_7100702370 {
    Unk_7100702370(ksys::act::Actor* actor, const float* fall_height)
        : mActor(actor), mFallHeight(fall_height) {}

    void sub_7100702370();
    void sub_7100702384();

    ksys::act::Actor* mActor;
    const float* mFallHeight;
    f32 _10 = 0;
    u8 _14 = 0;
};
KSYS_CHECK_SIZE_NX150(Unk_7100702370, 0x18);

namespace uking::ai {

class EnemyRoot : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(EnemyRoot, ksys::act::ai::Ai)
public:
    explicit EnemyRoot(const InitArg& arg);
    ~EnemyRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;
    bool handleMessage_(const ksys::Message& message) override;

    virtual void m34(ksys::act::ai::InlineParamPack* params);
    virtual bool m35();
    virtual bool m36() { return isCurrentChild("リアクション"); }
    virtual void m37();
    virtual void m38() {
        if (isCurrentChild("水中"))
            *mIsTrgChangeUnderWaterState_a = true;
        changeChild("通常");
    }
    virtual void m39();
    virtual void m40();
    virtual bool m41() { return isCurrentChild("水中"); }
    virtual void m42();
    virtual void m43();
    virtual bool m44() { return !isCurrentChild("所持") && !m36(); }

protected:
    Unk_7100702370* _38{};
    // static_param at offset 0x40
    const float* mInWaterDepth_s{};
    // static_param at offset 0x48
    const float* mOutOfWaterOffset_s{};
    // static_param at offset 0x50
    const float* mSpreadDist_s{};
    // static_param at offset 0x58
    const float* mSmallSpreadDist_s{};
    // static_param at offset 0x60
    const bool* mIgnoreHell_s{};
    // static_param at offset 0x68
    sead::SafeString mFortressTag_s{};
    // map_unit_param at offset 0x78
    const bool* mIsNearCreate_m{};
    // map_unit_param at offset 0x80
    sead::SafeString mEquipItem1_m{};
    // map_unit_param at offset 0x90
    sead::SafeString mEquipItem2_m{};
    // map_unit_param at offset 0xa0
    sead::SafeString mEquipItem3_m{};
    // map_unit_param at offset 0xb0
    sead::SafeString mEquipItem4_m{};
    // map_unit_param at offset 0xc0
    sead::SafeString mRideHorseName_m{};
    // aitree_variable at offset 0xd0
    int* mCreateDeadConditionType_a{};
    // aitree_variable at offset 0xd8
    int* mForceSealSilentKillCount_a{};
    // aitree_variable at offset 0xe0
    bool* mIsTrgChangeUnderWaterState_a{};
    Unk_71024507c8 _e8{0x1800004};
    Unk_71023eaec8 _128{mActor, 0x8000017};
    Unk_71023eaef0 _198{mActor, 0x80000b3};
    bool _1c8 = false;
    Unk_7100700834 _1cc;
};
KSYS_CHECK_SIZE_NX150(EnemyRoot, 0x1d8);

}  // namespace uking::ai
