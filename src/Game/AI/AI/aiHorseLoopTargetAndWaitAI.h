#pragma once

#include <prim/seadEnum.h>
#include "Game/AI/AI/aiHorseLoopTarget.h"
#include "Game/AI/aiFlagByte.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class HorseLoopTargetAndWaitAI : public HorseLoopTarget {
    SEAD_RTTI_OVERRIDE(HorseLoopTargetAndWaitAI, HorseLoopTarget)
public:
    explicit HorseLoopTargetAndWaitAI(const InitArg& arg);
    ~HorseLoopTargetAndWaitAI() override;

    bool handleMessage_(const ksys::Message* message) override;
    ksys::map::Rail* m34() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

protected:
    // Bit index of _18c (a SEAD_ENUM in the original: the index goes through a stack round trip);
    // the name and the number of values are guesses.
    SEAD_ENUM(Flag, _0)

    // 0x7100e5ca78 (placeholder name): called by enter_ (true) and calc_ (false).
    void sub_7100E5CA78(bool enter);

    // static_param at offset 0x170
    const float* mChangeWaitRate_s{};
    // static_param at offset 0x178
    const float* mMaxWaitTime_s{};
    // static_param at offset 0x180
    const float* mMinWaitTime_s{};
    f32 _188 = 0.0f;
    FlagByte<Flag> _18c;  // bit 0: this AI holds WildHorseMgr's busy flag
};

}  // namespace uking::ai
