#pragma once

#include <prim/seadSafeString.h>
#include "Game/AI/Action/actionAreaActorObserve.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class AreaActorObserveByActorTag : public AreaActorObserve {
    SEAD_RTTI_OVERRIDE(AreaActorObserveByActorTag, AreaActorObserve)
public:
    explicit AreaActorObserveByActorTag(const InitArg& arg);
    ~AreaActorObserveByActorTag() override;

    bool init_(sead::Heap* heap) override;
    void m9() override;

protected:
    void m32() override;
    bool m37(const ksys::act::ActorConstDataAccess& accessor) override;

    // Hash of the ActorTag map unit parameter.
    u32 _60 = 0;
    // map_unit_param (loaded by m32)
    sead::SafeString mActorTag_m;
};
KSYS_CHECK_SIZE_NX150(AreaActorObserveByActorTag, 0x78);

}  // namespace uking::action
