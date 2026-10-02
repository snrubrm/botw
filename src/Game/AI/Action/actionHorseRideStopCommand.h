#pragma once

#include "Game/AI/Action/actionHorseRideCommand.h"
#include "Game/AI/aiUnk_7102357d20.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class HorseRideStopCommand : public HorseRideCommand {
    SEAD_RTTI_OVERRIDE(HorseRideStopCommand, HorseRideCommand)
public:
    explicit HorseRideStopCommand(const InitArg& arg);
    ~HorseRideStopCommand() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
    bool m32(ksys::act::Actor* actor) override;

    Unk_710239c820 _58{mActor, 0x3800007};
};

KSYS_CHECK_SIZE_NX150(HorseRideStopCommand, 0x70);

}  // namespace uking::action
