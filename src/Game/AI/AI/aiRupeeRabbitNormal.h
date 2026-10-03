#pragma once

#include "Game/AI/AI/aiPreyNormal.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class RupeeRabbitNormal : public PreyNormal {
    SEAD_RTTI_OVERRIDE(RupeeRabbitNormal, PreyNormal)
public:
    explicit RupeeRabbitNormal(const InitArg& arg);
    ~RupeeRabbitNormal() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

    bool m42() override;
    ksys::act::Unk_7100d78e50* m43(s32 idx, bool skip_own_target) override;

protected:
    // map_unit_param at offset 0x340
    const bool* mDeleteEndNushiTime_m{};
    /* 0x348 */ ksys::Timer _348;
};
KSYS_CHECK_SIZE_NX150(RupeeRabbitNormal, 0x358);

}  // namespace uking::ai
