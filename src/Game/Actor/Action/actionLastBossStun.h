#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"
#include "KingSystem/System/Timer.h"
#include <math/seadMatrix.h>
#include <math/seadVector.h>

namespace uking::action {

class LastBossStun : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(LastBossStun, ksys::act::ai::Action)
public:
    explicit LastBossStun(const InitArg& arg);
    ~LastBossStun() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const float* mStunTime_s{};
    // static_param at offset 0x28
    const float* mAddStunTime_s{};
    // static_param at offset 0x30
    const float* mShockWaveDownTime_s{};
    bool _38 = false;
    bool _39 = false;
    bool _3a = false;
    bool _3b = false;
    ksys::Timer _3c;
    sead::Vector3f _48;
    u8 _54[0x60 - 0x54];
    sead::Matrix33f _60;
};

}  // namespace uking::action
