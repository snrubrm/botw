#pragma once

#include <gsys/gsysModelAccessKey.h>
#include <container/seadSafeArray.h>
#include <math/seadVector.h>
#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/System/Timer.h"

namespace ksys::phys {
class RayCastForRequest;
}

namespace uking::ai {

class SiteBossApproachRoot : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(SiteBossApproachRoot, ksys::act::ai::Ai)
public:
    explicit SiteBossApproachRoot(const InitArg& arg);
    ~SiteBossApproachRoot() override;
    bool isChangeable() const override { return true; }

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const float* mCheckWallDist_s{};
    // static_param at offset 0x40
    const float* mApproachTime_s{};
    // static_param at offset 0x48
    const float* mEndDist_s{};
    // static_param at offset 0x50
    const float* mEndFarDist_s{};
    // static_param at offset 0x58
    const float* mAttackStartDist_s{};
    // static_param at offset 0x60
    const bool* mDoAttack_s{};
    // dynamic_param at offset 0x68
    bool* mIsMoveSide_d{};
    // dynamic_param at offset 0x70
    sead::Vector3f* mTargetPos_d{};
    bool _78 = false;
    bool _79 = true;
    ksys::Timer _7c{};
    ksys::Timer _88{};
    f32 _94 = 0;
    f32 _98 = 0;
    // Wall-check ray casts (released in enter_ / leave_) and their result positions (zeroed together by one
    // memset in the constructor, which the compiler places after the BoneAccessKeyEx constructor).
    sead::SafeArray<ksys::phys::RayCastForRequest*, 5> mRayCasts;
    sead::SafeArray<sead::Vector3f, 5> _c8;
    sead::Vector3f _104[15];
    sead::Vector3f _1b8[5];
    gsys::BoneAccessKeyEx _1f8;
    sead::Vector3f _230;
};
KSYS_CHECK_SIZE_NX150(SiteBossApproachRoot, 0x240);

}  // namespace uking::ai
