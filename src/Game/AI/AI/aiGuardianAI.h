#pragma once

#include "Game/Actor/actGuardian.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class GuardianAI : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(GuardianAI, ksys::act::ai::Ai)
public:
    explicit GuardianAI(const InitArg& arg);
    ~GuardianAI() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

    // 0x710040da6c (lane1 s21): the actor as a Guardian (DynamicCast), or nullptr.
    act::Guardian* sub_710040DA6C();

protected:
};

}  // namespace uking::ai
