#pragma once

#include <math/seadBoundBox.h>
#include "Game/AI/Action/actionWillBallAction.h"
#include "Game/AI/aiUnk_NavMeshCallback.h"
#include "KingSystem/ActorSystem/actAiAction.h"
#include "KingSystem/Physics/System/physHavokAI.h"

namespace uking::action {

// The singleton at 0x710260de68 is ksys::phys::HavokAI (HavokAI::createInstance stores it; the old placeholder name
// is kept as an alias for its callers).
using Unk_710260de68 = ksys::phys::HavokAI;

class WillBallAvoidCenterDist : public WillBallAction {
    SEAD_RTTI_OVERRIDE(WillBallAvoidCenterDist, WillBallAction)
public:
    explicit WillBallAvoidCenterDist(const InitArg& arg);
    ~WillBallAvoidCenterDist() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
    void m32(sead::Vector3f* direction, f32* distance, f32* progress) override;

    // static_param at offset 0x98
    const float* mDist_s{};
    // static_param at offset 0xa0
    const float* mMaxDist_s{};
    // static_param at offset 0xa8
    const float* mMiddleDist_s{};
    // dynamic_param at offset 0xb0
    sead::Vector3f* mCenterPos_d{};
};

}  // namespace uking::action
