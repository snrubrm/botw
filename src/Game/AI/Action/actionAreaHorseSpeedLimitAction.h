#pragma once

#include "Game/AI/Action/actionAreaTagAction.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class AreaHorseSpeedLimitAction : public AreaTagAction {
    SEAD_RTTI_OVERRIDE(AreaHorseSpeedLimitAction, AreaTagAction)
public:
    explicit AreaHorseSpeedLimitAction(const InitArg& arg);
    ~AreaHorseSpeedLimitAction() override;

    bool init_(sead::Heap* heap) override;

protected:
    bool m15(const ksys::act::ActorConstDataAccess& accessor) override;
    sead::Buffer<Payload>* m6() override { return &_38; }

    sead::Buffer<Payload> _38;
};
KSYS_CHECK_SIZE_NX150(AreaHorseSpeedLimitAction, 0x48);

}  // namespace uking::action
