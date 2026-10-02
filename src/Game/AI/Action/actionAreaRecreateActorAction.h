#pragma once

#include "Game/AI/Action/actionAreaTagAction.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class AreaRecreateActorAction : public AreaTagAction {
    SEAD_RTTI_OVERRIDE(AreaRecreateActorAction, AreaTagAction)
public:
    explicit AreaRecreateActorAction(const InitArg& arg);
    ~AreaRecreateActorAction() override;

    bool init_(sead::Heap* heap) override;

protected:
    bool m15(const ksys::act::ActorConstDataAccess& accessor) override;
    sead::Buffer<Payload>* m6() override { return &_38; }

    sead::Buffer<Payload> _38;
};
KSYS_CHECK_SIZE_NX150(AreaRecreateActorAction, 0x48);

}  // namespace uking::action
