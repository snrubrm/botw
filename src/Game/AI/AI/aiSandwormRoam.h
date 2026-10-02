#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/ActorSystem/actUnk_7100d3bc4c.h"

namespace uking::ai {

class SandwormRoam : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(SandwormRoam, ksys::act::ai::Ai)
public:
    explicit SandwormRoam(const InitArg& arg);
    ~SandwormRoam() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

    void sub_710055D3F8();

protected:
    // static_param at offset 0x38
    const float* mJumpTimerBase_s{};
    // static_param at offset 0x40
    const float* mJumpTimerRand_s{};
    // static_param at offset 0x48
    const float* mJumpDistanceXZ_s{};
    ksys::act::Unk_7100d3bce4 _50{mActor};
};
KSYS_CHECK_SIZE_NX150(SandwormRoam, 0x68);

}  // namespace uking::ai
