#pragma once

#include "Game/AI/AI/aiPreyNormal.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

// vtable 0x710241b1f8 (m2 0x7100554de8, D0 0x71005550c8): the awareness filter of RupeeRabbitNormal::m43.
// Placeholder name.
class Unk_710241b1f8 : public ksys::act::Unk_71024dccf8 {
public:
    bool m2(ksys::act::Unk_71024dc978* entry) override;
};

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
