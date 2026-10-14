#pragma once

#include <math/seadMatrix.h>
#include "KingSystem/ActorSystem/actAiAction.h"
#include "KingSystem/System/Timer.h"

namespace uking::action {

class LastBossFlyWait : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(LastBossFlyWait, ksys::act::ai::Action)
public:
    explicit LastBossFlyWait(const InitArg& arg);
    ~LastBossFlyWait() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;
    bool isChangeable() const override;

protected:
    void calc_() override;
    // Target matrix of the flight, passed by calc_ to the character controller.
    virtual void m32(sead::Matrix34f* mtx);
    virtual float* m33() { return &_90; }
    virtual void m34() {}

    // static_param at offset 0x20
    const int* mDamageCounter_s{};
    // static_param at offset 0x28
    const float* mAmplitude_s{};
    // static_param at offset 0x30
    const float* mTime_s{};
    // static_param at offset 0x38
    const float* mMoveRate_s{};
    // static_param at offset 0x40
    const float* mEndTime_s{};
    // static_param at offset 0x48
    const float* mEndTimeRandRange_s{};
    // static_param at offset 0x50
    const float* mBaseYOffset_s{};
    // static_param at offset 0x58
    const bool* mIsChemicalOff_s{};
    // static_param at offset 0x60
    sead::SafeString mWaitAS_s{};
    // dynamic_param at offset 0x70
    bool* mIsResetEndTime_d{};
    ksys::Timer _78;
    ksys::Timer _84;
    float _90 = 0.0f;
    float _94 = 0.0f;
    int _98 = 0;
};

}  // namespace uking::action
