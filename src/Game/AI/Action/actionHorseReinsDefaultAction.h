#pragma once

#include "Game/Actor/actHorseBindSets.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class HorseReinsDefaultAction : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(HorseReinsDefaultAction, ksys::act::ai::Action)
public:
    explicit HorseReinsDefaultAction(const InitArg& arg);
    // Defined inline: HorseReinsBindAction's D1 / D0 inline it.
    ~HorseReinsDefaultAction() override = default;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    /* 0x20 */ act::Unk_71024e9450 _20;
};

}  // namespace uking::action
