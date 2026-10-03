#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class DgnObj_DLC_CogWheel_Physics_Ctr : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(DgnObj_DLC_CogWheel_Physics_Ctr, ksys::act::ai::Ai)
public:
    explicit DgnObj_DLC_CogWheel_Physics_Ctr(const InitArg& arg);
    ~DgnObj_DLC_CogWheel_Physics_Ctr() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;
    bool handleMessage_(const ksys::Message& message) override;

    void sub_710035ED38();

protected:
    // static_param at offset 0x38
    const bool* mStateRot_s{};
};

}  // namespace uking::ai
