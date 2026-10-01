#pragma once

#include "Game/AI/Action/actionElectricParalysis.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class CapturedActElectricParalyisis : public ElectricParalysis {
    SEAD_RTTI_OVERRIDE(CapturedActElectricParalyisis, ElectricParalysis)
public:
    explicit CapturedActElectricParalyisis(const InitArg& arg);
    ~CapturedActElectricParalyisis() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x40
    const float* mPauseDelayFrames_s{};
    float _48 = 0.0f;
    float _4c = 0.0f;
    int _50 = 0;
};

}  // namespace uking::action
