#pragma once

#include "Game/AI/AI/aiCreateActor.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class CreateCarryActor : public CreateActor {
    SEAD_RTTI_OVERRIDE(CreateCarryActor, CreateActor)
public:
    explicit CreateCarryActor(const InitArg& arg);
    ~CreateCarryActor() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;
    const sead::SafeString& m34() override;

protected:
    // map_unit_param at offset 0x68
    sead::SafeString mCarryActorName_m{};
};

}  // namespace uking::ai
