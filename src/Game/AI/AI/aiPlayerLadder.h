#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/System/Timer.h"

namespace uking::ai {

class PlayerLadder : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(PlayerLadder, ksys::act::ai::Ai)
public:
    explicit PlayerLadder(const InitArg& arg);
    ~PlayerLadder() override;

    bool isChangeable() const override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

    bool isFinished() const override;

protected:
    bool _38 = false;
    bool _39 = false;
    u32 _3c;
    ksys::Timer _40;  // reset to 0 by the ctor
    // static_param at offset 0x50
    const float* mLadderToClimbTime_s{};
};
KSYS_CHECK_SIZE_NX150(PlayerLadder, 0x58);

}  // namespace uking::ai
