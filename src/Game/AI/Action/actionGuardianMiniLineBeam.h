#pragma once

#include "KingSystem/ActorSystem/actBaseProcLink.h"
#include "Game/AI/Action/actionSimpleLineBeam.h"
#include "KingSystem/ActorSystem/actAiAction.h"
#include "KingSystem/System/Timer.h"

namespace uking::action {

class GuardianMiniLineBeam : public SimpleLineBeam {
    SEAD_RTTI_OVERRIDE(GuardianMiniLineBeam, SimpleLineBeam)
public:
    explicit GuardianMiniLineBeam(const InitArg& arg);
    ~GuardianMiniLineBeam() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x50
    const int* mIceBlockBreakTime_s{};
    ksys::act::BaseProcLink _58;
    ksys::Timer _68{0.0f, 0.0f};
    u8 _74[0x4];
};
KSYS_CHECK_SIZE_NX150(GuardianMiniLineBeam, 0x78);

}  // namespace uking::action
