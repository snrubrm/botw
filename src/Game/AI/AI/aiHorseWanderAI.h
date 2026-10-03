#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::act {
class HorseBase;
}

namespace uking::ai {

class HorseWanderAI : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(HorseWanderAI, ksys::act::ai::Ai)
public:
    explicit HorseWanderAI(const InitArg& arg);
    ~HorseWanderAI() override;
    void calc_() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // Inline-only in the original (name guess; evidence: enter_'s SafeString temporaries sit above the param pack).
    void changeToFollowLeader(ksys::act::ai::InlineParamPack* pack, act::HorseBase* horse);
};

}  // namespace uking::ai
