#pragma once

#include <container/seadSafeArray.h>
#include "Game/AI/Action/actionAreaTagAction.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class AreaOutRecreateActorAction : public AreaTagAction {
    SEAD_RTTI_OVERRIDE(AreaOutRecreateActorAction, AreaTagAction)
public:
    explicit AreaOutRecreateActorAction(const InitArg& arg);
    ~AreaOutRecreateActorAction() override;

    bool init_(sead::Heap* heap) override;

protected:
    void m2() override { _58 = 0; }
    bool m15(const ksys::act::ActorConstDataAccess& accessor) override;
    void m5() override;
    sead::Buffer<Payload>* m6() override { return &_38; }

    sead::Buffer<Payload> _38;
    // Indices of the map objects (linked by Recreate links) that entered the area.
    sead::SafeArray<u32, 4> _48{};
    int _58 = 0;
};
KSYS_CHECK_SIZE_NX150(AreaOutRecreateActorAction, 0x60);

}  // namespace uking::action
