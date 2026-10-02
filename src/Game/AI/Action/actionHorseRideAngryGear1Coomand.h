#pragma once

#include "Game/AI/Action/actionHorseRideCommand.h"
#include "Game/AI/aiUnk_7102357d20.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class HorseRideAngryGear1Coomand : public HorseRideCommand {
    SEAD_RTTI_OVERRIDE(HorseRideAngryGear1Coomand, HorseRideCommand)
public:
    explicit HorseRideAngryGear1Coomand(const InitArg& arg);
    ~HorseRideAngryGear1Coomand() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
    bool m32(ksys::act::Actor* actor) override;

    Unk_710239b6b8 _58{mActor, 0x380000d};
};

KSYS_CHECK_SIZE_NX150(HorseRideAngryGear1Coomand, 0x70);

}  // namespace uking::action
