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
    void leave_() override;
    void loadParams_() override;

protected:
    // map_unit_param at offset 0x340
    const bool* mDeleteEndNushiTime_m{};
    /* 0x348 */ ksys::Timer _348;
};
KSYS_CHECK_SIZE_NX150(RupeeRabbitNormal, 0x358);

}  // namespace uking::ai
