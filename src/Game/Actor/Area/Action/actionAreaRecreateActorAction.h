#pragma once

#include "Game/Actor/Area/Action/actionAreaActionBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class AreaRecreateActorAction : public AreaActionBase {
    SEAD_RTTI_OVERRIDE(AreaRecreateActorAction, AreaActionBase)
public:
    explicit AreaRecreateActorAction(const InitArg& arg);
    ~AreaRecreateActorAction() override;

    bool init_(sead::Heap* heap) override;

protected:
    bool m15(const ksys::act::ActorLinkConstDataAccess& accessor) override;
    sead::Buffer<Payload>* m6() override { return &_38; }

    sead::Buffer<Payload> _38;
};
KSYS_CHECK_SIZE_NX150(AreaRecreateActorAction, 0x48);

}  // namespace uking::action
