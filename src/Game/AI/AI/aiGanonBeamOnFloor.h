#pragma once

#include "Game/AI/AI/aiLastBossShootNormalArrowRoot.h"
#include <math/seadMatrix.h>
#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/System/VFRValue.h"

namespace uking::ai {

class GanonBeamOnFloor : public LastBossShootNormalArrowRoot {
    SEAD_RTTI_OVERRIDE(GanonBeamOnFloor, LastBossShootNormalArrowRoot)
public:
    explicit GanonBeamOnFloor(const InitArg& arg);
    ~GanonBeamOnFloor() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

    bool m38() override;

    // 0x71003e4208 (not decompiled): turns `_298` towards the target.
    void sub_71003E4208();

protected:
    // static_param at offset 0x260
    const float* mTurnStartAng_s{};
    // static_param at offset 0x268
    const float* mKeepMinDist_s{};
    // static_param at offset 0x270
    const float* mTurnRate_s{};
    // static_param at offset 0x278
    sead::SafeString mWalkAS_s{};
    // static_param at offset 0x288
    sead::SafeString mTurnAS_s{};
    sead::Matrix33f _298;
    ksys::VFRValue _2bc;
    ksys::VFRValue _2c8;
    bool _2d4 = false;
    bool _2d5 = false;
};
KSYS_CHECK_SIZE_NX150(GanonBeamOnFloor, 0x2d8);

}  // namespace uking::ai
