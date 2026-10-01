#pragma once

#include "Game/AI/Action/actionStopASPlay.h"
#include "KingSystem/ActorSystem/actAiAction.h"
#include "KingSystem/System/VFRValue.h"

namespace uking::action {

class NeckSpin : public StopASPlay {
    SEAD_RTTI_OVERRIDE(NeckSpin, StopASPlay)
public:
    explicit NeckSpin(const InitArg& arg);
    ~NeckSpin() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
    virtual float m32();
    virtual void m33();

    // static_param at offset 0x48
    const float* mSpinSpeed_s{};
    // static_param at offset 0x50
    const float* mNeckUDAngle_s{};
    ksys::VFRValue _58;
    f32 _64 = 0;
};

KSYS_CHECK_SIZE_NX150(NeckSpin, 0x68);

}  // namespace uking::action
