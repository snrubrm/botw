#pragma once

#include <math/seadBoundBox.h>
#include <math/seadVector.h>
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class ChmVolRateCheck : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(ChmVolRateCheck, ksys::act::ai::Ai)
public:
    explicit ChmVolRateCheck(const InitArg& arg);
    ~ChmVolRateCheck() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const float* mVolTh_s{};
    // static_param at offset 0x40
    const float* mDebugScale_s{};
    // static_param at offset 0x48
    const bool* mDebugDraw_s{};
    // static_param at offset 0x50
    const bool* mIsInvalidBreakJudge_s{};
    // map_unit_param at offset 0x58
    const int* mFreezeTarget_m{};
    // map_unit_param at offset 0x60
    const float* mIceBreakScale_m{};
    sead::BoundBox3f _68;
    u32 _80 = 1;
    // The linked actor's AABB corners, transformed into this actor's local space.
    sead::Vector3f _84[8];
    // This actor's AABB (min, max).
    sead::Vector3f _e4;
    sead::Vector3f _f0;
    // AABB volumes of the linked actor / this actor.
    f32 _fc = 0;
    f32 _100 = 0;
    bool _104 = true;
};
KSYS_CHECK_SIZE_NX150(ChmVolRateCheck, 0x108);

}  // namespace uking::ai
