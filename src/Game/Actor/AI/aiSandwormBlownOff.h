#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class SandwormBlownOff : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(SandwormBlownOff, ksys::act::ai::Ai)
public:
    explicit SandwormBlownOff(const InitArg& arg);
    ~SandwormBlownOff() override;

    bool isFinished() const override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const float* mBlownOffTimer_s{};
    f32 _40 = 0;
    u32 _44 = 0;
    u32 _48 = 0;
};
KSYS_CHECK_SIZE_NX150(SandwormBlownOff, 0x50);

}  // namespace uking::ai
