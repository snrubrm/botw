#pragma once

#include "Game/AI/aiUnk_7102357210.h"
#include "Game/AI/aiUnk_7102357d20.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class GuardianMiniBlownOff : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(GuardianMiniBlownOff, ksys::act::ai::Ai)
public:
    explicit GuardianMiniBlownOff(const InitArg& arg);
    ~GuardianMiniBlownOff() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;
    bool handleMessage_(const ksys::Message* message) override;

    void sub_7100419D88(f32 value);

protected:
    // static_param at offset 0x38
    const float* mRotNeckAngle_s{};
    // static_param at offset 0x40
    const float* mRotNeckSpeed_s{};
    Unk_71023f83e8* _48{};
    Unk_7102450498 _50;
};
KSYS_CHECK_SIZE_NX150(GuardianMiniBlownOff, 0xa0);

}  // namespace uking::ai
