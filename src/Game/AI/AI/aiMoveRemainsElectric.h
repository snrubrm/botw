#pragma once

#include "Game/AI/AI/aiRailMoveRemains.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class MoveRemainsElectric : public RailMoveRemains {
    SEAD_RTTI_OVERRIDE(MoveRemainsElectric, RailMoveRemains)
public:
    explicit MoveRemainsElectric(const InitArg& arg);
    ~MoveRemainsElectric() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;
    bool m40() override;
    f32 m43() override;

protected:
    // static_param at offset 0x80
    const float* mReactiveRange_s{};
    // static_param at offset 0x88
    const float* mDemoCallWaitTime_s{};
    // static_param at offset 0x90
    const sead::Vector3f* mCannonOffset_s{};
    // static_param at offset 0x98
    const sead::Vector3f* mWeakPointOffset_s{};
    // map_unit_param at offset 0xa0
    const bool* mIsJoinRemainsBattle_m{};

    // Members not recovered yet (class size from the factory).
    u8 _a8[0x540 - 0xa8];
};
KSYS_CHECK_SIZE_NX150(MoveRemainsElectric, 0x540);

}  // namespace uking::ai
