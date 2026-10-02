#pragma once

#include "Game/AI/Action/actionHorseRideMoveCommand.h"
#include "Game/AI/aiUnk_7102357d20.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class HorseRideChaseCommand : public HorseRideMoveCommand {
    SEAD_RTTI_OVERRIDE(HorseRideChaseCommand, HorseRideMoveCommand)
public:
    explicit HorseRideChaseCommand(const InitArg& arg);
    ~HorseRideChaseCommand() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
    bool m32(ksys::act::Actor* actor) override;

    // static_param at offset 0x98
    const float* mChaseKeepDist_s{};
    Unk_710239bdc0 _a0{mActor, 0x3800008};
};

KSYS_CHECK_SIZE_NX150(HorseRideChaseCommand, 0x110);

}  // namespace uking::action
