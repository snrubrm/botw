#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"
#include "Game/Actor/Action/actionSandwormTackleMove.h"
#include "Game/Actor/aiUnk_710073E688.h"
#include "KingSystem/System/Timer.h"

namespace uking::action {

class MultiVacuumBase : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(MultiVacuumBase, ksys::act::ai::Action)
public:
    explicit MultiVacuumBase(const InitArg& arg);
    ~MultiVacuumBase() override;

    bool init_(sead::Heap* heap) override;
    bool handleAck_(const ksys::MessageAck* ack) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
    // Complete 1EE31C is the vacuum update used by calc_ 1EE164.
    void sub_71001EE31C();

    // static_param at offset 0x20
    const int* mTime_s{};
    // static_param at offset 0x28
    const int* mAddTimeVacuuming_s{};
    // static_param at offset 0x30
    const int* mAddTimeNearVacuuming_s{};
    // static_param at offset 0x38
    const int* mVacuumNum_s{};
    // static_param at offset 0x40
    const int* mChangeableTiming_s{};
    // static_param at offset 0x48
    const float* mEndDist_s{};
    // static_param at offset 0x50
    const float* mMaxDist_s{};
    // static_param at offset 0x58
    const float* mTargetAccRate_s{};
    // static_param at offset 0x60
    const float* mTargetSpeed_s{};
    // static_param at offset 0x68
    const float* mBaseWeight_s{};
    // static_param at offset 0x70
    const float* mVacuumAngle_s{};
    // static_param at offset 0x78
    const float* mNearDist_s{};
    // static_param at offset 0x80
    sead::SafeString mStartAS_s{};
    // static_param at offset 0x90
    sead::SafeString mLoopAS_s{};
    // static_param at offset 0xa0
    sead::SafeString mEndAS_s{};
    // static_param at offset 0xb0
    const sead::Vector3f* mVacuumPosOffset_s{};
    Unk_SandwormTackleTarget _b8;
    // Complete 1EDA44 constructs the vacuum state, then a 64-byte string buffer.
    // Independent init 1EDD7C and enter 1EDFE8 pass both objects to their native APIs.
    Unk_710073e688 _118;
    sead::FixedSafeString<64> _148;
    u32 _1a0 = 0;
    s32 _1a4 = 0;
    ksys::Timer _1a8;
    bool _1b4 = false;
    bool _1b5 = false;
    int _1b8 = 0;
    u8 _1bc[0x1c0 - 0x1bc];
};

KSYS_CHECK_SIZE_NX150(MultiVacuumBase, 0x1c0);

}  // namespace uking::action
