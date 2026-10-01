#pragma once

#include "Game/AI/AI/aiSwarmEscapeDie.h"
#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/ActorSystem/actBaseProcHandle.h"

namespace uking::ai {

class SwarmStopTimerEscape : public SwarmEscapeDie {
    SEAD_RTTI_OVERRIDE(SwarmStopTimerEscape, SwarmEscapeDie)
public:
    explicit SwarmStopTimerEscape(const InitArg& arg);
    ~SwarmStopTimerEscape() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

protected:
    void sub_71005B31CC();

    // static_param at offset 0x70
    sead::SafeString mStopActorName_s{};
    ksys::act::BaseProcHandle _80;
};
KSYS_CHECK_SIZE_NX150(SwarmStopTimerEscape, 0x90);

}  // namespace uking::ai
