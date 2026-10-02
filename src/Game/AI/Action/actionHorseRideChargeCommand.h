#pragma once

#include "Game/AI/Action/actionHorseRideMoveCommand.h"
#include "Game/AI/aiUnk_7102357d20.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class HorseRideChargeCommand : public HorseRideMoveCommand {
    SEAD_RTTI_OVERRIDE(HorseRideChargeCommand, HorseRideMoveCommand)
public:
    explicit HorseRideChargeCommand(const InitArg& arg);
    ~HorseRideChargeCommand() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
    bool m32(ksys::act::Actor* actor) override;

    Unk_710239bc68 _98{mActor, 0x3800006};
};

KSYS_CHECK_SIZE_NX150(HorseRideChargeCommand, 0x108);

}  // namespace uking::action
