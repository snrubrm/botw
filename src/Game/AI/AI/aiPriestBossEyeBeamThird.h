#pragma once

#include "Game/AI/AI/aiPriestBossEyeBeam.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class PriestBossEyeBeamThird : public PriestBossEyeBeam {
    SEAD_RTTI_OVERRIDE(PriestBossEyeBeamThird, PriestBossEyeBeam)
public:
    explicit PriestBossEyeBeamThird(const InitArg& arg);
    ~PriestBossEyeBeamThird() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

    sead::SafeString m46() override { return "ThirdBeam"; }

protected:
    void sub_7100516FAC(const sead::Vector3f& pos, bool is_arrived);

    // aitree_variable at offset 0xb8
    bool* mIsArrivedAtDestination_a{};
    // aitree_variable at offset 0xc0
    sead::Vector3f* mDestinationPos_a{};
    // aitree_variable at offset 0xc8
    sead::Vector3f* mFacePos_a{};
    bool _d0 = false;
    bool _d1 = false;
};
KSYS_CHECK_SIZE_NX150(PriestBossEyeBeamThird, 0xd8);

}  // namespace uking::ai
