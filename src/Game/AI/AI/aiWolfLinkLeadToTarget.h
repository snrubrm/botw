#pragma once

#include "Game/AI/AI/aiLeadToTarget.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::act {
class WolfLink;
}

namespace uking::ai {

class WolfLinkLeadToTarget : public LeadToTarget {
    SEAD_RTTI_OVERRIDE(WolfLinkLeadToTarget, LeadToTarget)
public:
    explicit WolfLinkLeadToTarget(const InitArg& arg);
    ~WolfLinkLeadToTarget() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    act::WolfLink* _98{};
    bool _a0 = false;
};
KSYS_CHECK_SIZE_NX150(WolfLinkLeadToTarget, 0xa8);

}  // namespace uking::ai
