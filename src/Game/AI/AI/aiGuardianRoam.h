#pragma once

#include "Game/AI/AI/aiGuardianAI.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class GuardianRoam : public GuardianAI {
    SEAD_RTTI_OVERRIDE(GuardianRoam, GuardianAI)
public:
    explicit GuardianRoam(const InitArg& arg);
    ~GuardianRoam() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const int* mMoveTime_s{};
    // static_param at offset 0x40
    const float* mMoveRadius_s{};
    f32 _48{};
    f32 _4c{};
};

}  // namespace uking::ai
