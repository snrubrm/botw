#pragma once

#include "Game/AI/Action/actionHorseRideMoveCommand.h"
#include "Game/AI/aiUnk_7102357d20.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class HorseRideMoveToCommand : public HorseRideMoveCommand {
    SEAD_RTTI_OVERRIDE(HorseRideMoveToCommand, HorseRideMoveCommand)
public:
    explicit HorseRideMoveToCommand(const InitArg& arg);
    ~HorseRideMoveToCommand() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
    bool m32(ksys::act::Actor* actor) override;

    Unk_710239c3a0 _98{mActor, 0x3800003};
};

KSYS_CHECK_SIZE_NX150(HorseRideMoveToCommand, 0x100);

}  // namespace uking::action
