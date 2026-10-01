#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class SiteBossBlowOff : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(SiteBossBlowOff, ksys::act::ai::Ai)
public:
    explicit SiteBossBlowOff(const InitArg& arg);
    ~SiteBossBlowOff() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

protected:
    // dynamic_param at offset 0x38
    bool* mIsPlayDamageAnm_d{};
    void* _40{};
    u32 _48 = 0;
};
KSYS_CHECK_SIZE_NX150(SiteBossBlowOff, 0x50);

}  // namespace uking::ai
