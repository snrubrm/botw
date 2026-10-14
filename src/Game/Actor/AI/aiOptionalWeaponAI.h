#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class OptionalWeaponAI : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(OptionalWeaponAI, ksys::act::ai::Ai)
public:
    explicit OptionalWeaponAI(const InitArg& arg);

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void loadParams_() override;

protected:
    // Declaration only.
    void sub_7100E1A544();
    void sub_7100E1A930();
};

}  // namespace uking::ai
