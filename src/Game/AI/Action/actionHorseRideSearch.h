#pragma once

#include "Game/AI/Action/actionHorseRide.h"
#include "Game/AI/aiUnk_7102357d20.h"
#include "KingSystem/System/Timer.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class HorseRideSearch : public HorseRide {
    SEAD_RTTI_OVERRIDE(HorseRideSearch, HorseRide)
public:
    explicit HorseRideSearch(const InitArg& arg);
    ~HorseRideSearch() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;
    bool isFinished() const override;

protected:
    void calc_() override;

    ksys::Timer _30;
    Unk_710239c820 _40{mActor, 0x3800007};
};

KSYS_CHECK_SIZE_NX150(HorseRideSearch, 0x58);

}  // namespace uking::action
