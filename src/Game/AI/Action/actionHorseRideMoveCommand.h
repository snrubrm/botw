#pragma once

#include "Game/AI/Action/actionHorseRideCommand.h"
#include "Game/AI/aiUnk_7102357d20.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class HorseRideMoveCommand : public HorseRideCommand {
    SEAD_RTTI_OVERRIDE(HorseRideMoveCommand, HorseRideCommand)
public:
    explicit HorseRideMoveCommand(const InitArg& arg);
    ~HorseRideMoveCommand() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
    bool m32(ksys::act::Actor* actor) override;

    // static_param at offset 0x58
    const int* mGear_s{};
    Unk_710239c018 _60{mActor, 0x380000b};
    Unk_710239c040 _80{mActor, 0x380000c};
};

KSYS_CHECK_SIZE_NX150(HorseRideMoveCommand, 0x98);

}  // namespace uking::action
