#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class WizzrobeCombatMove : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(WizzrobeCombatMove, ksys::act::ai::Ai)
public:
    explicit WizzrobeCombatMove(const InitArg& arg);
    ~WizzrobeCombatMove() override;

    bool isFinished() const override;
    bool isChangeable() const override { return false; }

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void calc_() override;
    void loadParams_() override;
    void sub_71005FD0AC();
    // Native enter/calc call these same-owner helpers with only this.
    void sub_71005FC9C0();
    void sub_71005FCB74();
    void sub_71005FD564();
    // 0x71005fd24c: two by-value Vector3f arguments are passed in s0-s5.
    bool sub_71005FD24C(sead::Vector3f* hit_position, sead::Vector3f start, sead::Vector3f end);

protected:
    // static_param at offset 0x38
    const int* mMoveCountMin_s{};
    // static_param at offset 0x40
    const int* mMoveCountMax_s{};
    // static_param at offset 0x48
    const float* mDistY_s{};
    // static_param at offset 0x50
    const float* mRetryLength_s{};
    // static_param at offset 0x58
    const float* mMaxDistXZ_s{};
    // static_param at offset 0x60
    const float* mMinDistXZ_s{};
    // static_param at offset 0x68
    const float* mEscapeLength_s{};
    // static_param at offset 0x70
    sead::SafeString mIgnoreHideActionASName_s{};
    // dynamic_param at offset 0x80
    sead::Vector3f* mTargetPos_d{};
    // dynamic_param at offset 0x88
    sead::Vector3f* mAttPos_d{};
    // aitree_variable at offset 0x90
    bool* mIsWizzrobeInBattleAreaFlag_a{};
    u8 _98[0xb0 - 0x98];
    // Native 5FCB74 stores the actor position here; calc compares the saved position.
    sead::Vector3f mStartPosition{0, 0, 0};
    s32 _bc = 0;
    s32 _c0 = 0;
    u32 _c4 = 0;
    bool _c8 = false;
};
KSYS_CHECK_SIZE_NX150(WizzrobeCombatMove, 0xd0);

}  // namespace uking::ai
