#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"
#include "KingSystem/System/Timer.h"
#include <math/seadMatrix.h>

namespace uking::action {

class LastBossDemoWarp : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(LastBossDemoWarp, ksys::act::ai::Action)
public:
    explicit LastBossDemoWarp(const InitArg& arg);
    ~LastBossDemoWarp() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const float* mWarpTime_s{};
    // static_param at offset 0x28
    const bool* mIsUpdateHomePos_s{};
    // static_param at offset 0x30
    sead::SafeString mWarpAnchorUniqName_s{};
    ksys::Timer _40{0, 0, 0};
    float _4c = 0.0f;
    float _50 = 0.0f;
    sead::Matrix34f _54;
    sead::Matrix33f _84;
};

}  // namespace uking::action
