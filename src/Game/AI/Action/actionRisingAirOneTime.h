#pragma once

#include "Game/AI/Action/actionAscendingCurrent.h"
#include "KingSystem/ActorSystem/actAiAction.h"
#include "KingSystem/ActorSystem/actUnk_7100d3bc4c.h"

namespace uking::action {

class RisingAirOneTime : public AscendingCurrent {
    SEAD_RTTI_OVERRIDE(RisingAirOneTime, AscendingCurrent)
public:
    explicit RisingAirOneTime(const InitArg& arg);
    ~RisingAirOneTime() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x80
    const float* mLostCounter_s{};
    ksys::act::Unk_7100d3bce4 _88{mActor};
};

}  // namespace uking::action
