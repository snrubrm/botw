#pragma once

#include "Game/AI/Action/actionHorseRideCommand.h"
#include "Game/AI/aiUnk_7102357d20.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class HorseRideTurnCommand : public HorseRideCommand {
    SEAD_RTTI_OVERRIDE(HorseRideTurnCommand, HorseRideCommand)
public:
    explicit HorseRideTurnCommand(const InitArg& arg);
    ~HorseRideTurnCommand() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
    bool m32(ksys::act::Actor* actor) override;

    Unk_710239cca0 _58{mActor, 0x3800005};
};

KSYS_CHECK_SIZE_NX150(HorseRideTurnCommand, 0xc0);

}  // namespace uking::action
