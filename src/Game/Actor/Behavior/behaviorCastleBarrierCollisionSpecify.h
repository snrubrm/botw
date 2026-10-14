#pragma once

#include <prim/seadDelegate.h>
#include "KingSystem/ActorSystem/actAiBehavior.h"

namespace ksys::phys {
class RigidBody;
}

namespace uking::behavior {

class CastleBarrierCollisionSpecify : public ksys::act::ai::Behavior {
    SEAD_RTTI_OVERRIDE(CastleBarrierCollisionSpecify, ksys::act::ai::Behavior)
public:
    explicit CastleBarrierCollisionSpecify(const InitArg& arg);
    bool m6(sead::Heap* heap) override;
    void m8() override;
    void m9() override;
    // 0x710061bcb0
    void sub_710061BCB0(ksys::phys::RigidBody* body);

    /* 0x28 */ sead::Delegate1<CastleBarrierCollisionSpecify, ksys::phys::RigidBody*> _28{this, &CastleBarrierCollisionSpecify::sub_710061BCB0};
};
KSYS_CHECK_SIZE_NX150(CastleBarrierCollisionSpecify, 0x48);

}  // namespace uking::behavior
