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
    // 0x710041e07c (placeholder name)
    void changeToOnIceMaker();

protected:
    // static_param at offset 0x38
    const int* mChangeToIceTimer_s{};
    ksys::act::BaseProcLink _40;
    ksys::Timer _50{0, 0};
    // 0x5c / 0x5d: two flag bytes (the original sets bit 0 of the u16)
    u16 _5c{};
};

}  // namespace uking::ai
