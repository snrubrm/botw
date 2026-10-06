#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class MoveToCameraFrontXZ : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(MoveToCameraFrontXZ, ksys::act::ai::Ai)
public:
    explicit MoveToCameraFrontXZ(const InitArg& arg);
    ~MoveToCameraFrontXZ() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

    // 0x71004b38a8 (placeholder name)
    void changeToAvoidPlayerMove(const sead::Vector3f& a, const sead::Vector3f& b);

protected:
    // 0x71004b43e4 (placeholder name): `out` is AvoidPlayerDist from the player, towards the direction
    // derived from the (normalised) offsets of `a` and `b` from the player position.
    void sub_71004B43E4(sead::Vector3f* out, const sead::Vector3f& a, const sead::Vector3f& b);

    // static_param at offset 0x38
    const int* mReverseTimer_s{};
    // static_param at offset 0x40
    const int* mReverseCount_s{};
    // static_param at offset 0x48
    const int* mWeaponIdx_s{};
    // static_param at offset 0x50
    const float* mDistFromPlayer_s{};
    // static_param at offset 0x58
    const float* mMinDistFromPlayer_s{};
    // static_param at offset 0x60
    const float* mAvoidPlayerDist_s{};
    // static_param at offset 0x68
    const float* mAddLineCheckNavRadius_s{};
    // static_param at offset 0x70
    const float* mReachableRadius_s{};
    // static_param at offset 0x78
    const bool* mIsSuccessByLineReachable_s{};
    int _80{};
    int _84{};
    sead::Vector3f _88{0, 0, 0};
};

}  // namespace uking::ai
