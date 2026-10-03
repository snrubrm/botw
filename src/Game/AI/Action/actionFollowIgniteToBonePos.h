#pragma once

#include "Game/AI/Action/actionRotateTurnToTarget.h"
#include "Game/AI/Action/actionUnk_7102360d20.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class FollowIgniteToBonePos : public RotateTurnToTarget {
    SEAD_RTTI_OVERRIDE(FollowIgniteToBonePos, RotateTurnToTarget)
public:
    explicit FollowIgniteToBonePos(const InitArg& arg);
    ~FollowIgniteToBonePos() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
    bool handleMessage_(const ksys::Message* message) override;

    sead::Vector3f sub_710005B104();

    // static_param at offset 0x78
    const float* mLocalOffSetX_s{};
    // static_param at offset 0x80
    const float* mLocalOffSetY_s{};
    // static_param at offset 0x88
    const float* mLocalOffSetZ_s{};
    // static_param at offset 0x90
    const bool* mIsIgnitePosYZero_s{};
    // static_param at offset 0x98
    sead::SafeString mBoneName_s{};
    sead::SafeString _a8;
    u64 _b8 = 0;
    Unk_7102360d20 _c0{this};
};
KSYS_CHECK_SIZE_NX150(FollowIgniteToBonePos, 0x118);

}  // namespace uking::action
