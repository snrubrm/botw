#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class KeeseRoam : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(KeeseRoam, ksys::act::ai::Ai)
public:
    explicit KeeseRoam(const InitArg& arg);
    ~KeeseRoam() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

    // 0x7100453f6c: picks the next roam point around the central position (false if none is usable).
    bool sub_7100453F6C(sead::Vector3f* out);
    // 0x7100454410: tries `tries` times to pick a point and move there.
    bool sub_7100454410(s32 tries);

protected:
    // Inline-only in the original (name guess; evidence: the param pack and name temporary sit above the caller's target).
    void changeToMove(const sead::Vector3f& target);

    // static_param at offset 0x38
    const float* mMinOffsetY_s{};
    // static_param at offset 0x40
    const float* mMaxOffsetY_s{};
    // static_param at offset 0x48
    const float* mRoamRadius_s{};
    // static_param at offset 0x50
    const float* mMinMoveDist_s{};
    // static_param at offset 0x58
    const float* mMaxMoveDist_s{};
    // static_param at offset 0x60
    const float* mNoWaitRatio_s{};
    // dynamic_param at offset 0x68
    sead::Vector3f* mCentralPos_d{};
    bool _70{};
    int _74 = 8;
};

}  // namespace uking::ai
