#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"
#include "KingSystem/System/Timer.h"

namespace uking::ai {

class GuardianMiniOnNoNavMesh : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(GuardianMiniOnNoNavMesh, ksys::act::ai::Ai)
public:
    explicit GuardianMiniOnNoNavMesh(const InitArg& arg);
    ~GuardianMiniOnNoNavMesh() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const int* mChangeToIceTimer_s{};
    ksys::act::BaseProcLink _40;
    ksys::Timer _50{0, 0};
    bool _5c{};
    bool _5d{};
};

}  // namespace uking::ai
