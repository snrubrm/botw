#pragma once

#include "Game/Actor/Action/actionHorseRideCommand.h"
#include "Game/Actor/aiUnk_7102357d20.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class HorseRideSetGearCommand : public HorseRideCommand {
    SEAD_RTTI_OVERRIDE(HorseRideSetGearCommand, HorseRideCommand)
public:
    explicit HorseRideSetGearCommand(const InitArg& arg);
    ~HorseRideSetGearCommand() override;

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

KSYS_CHECK_SIZE_NX150(HorseRideSetGearCommand, 0x98);

}  // namespace uking::action
