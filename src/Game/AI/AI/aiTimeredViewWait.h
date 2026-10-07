#pragma once

#include "Game/AI/AI/aiViewWait.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class TimeredViewWait : public ViewWait {
    SEAD_RTTI_OVERRIDE(TimeredViewWait, ViewWait)
public:
    explicit TimeredViewWait(const InitArg& arg);
    ~TimeredViewWait() override = default;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x60
    const int* mTime_s{};
    // static_param at offset 0x68
    const int* mTimeRand_s{};
    f32 _70{};
};

}  // namespace uking::ai
