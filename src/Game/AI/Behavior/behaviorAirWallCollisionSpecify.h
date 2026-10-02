#pragma once

#include <prim/seadDelegate.h>
#include "KingSystem/ActorSystem/actAiBehavior.h"

namespace ksys::phys {
class RigidBody;
}

namespace uking::behavior {

// Sets the ground hit mask of an AirWall actor's rigid bodies through a delegate (m7/m8 need the AirWall
// actor class, which does not exist yet).
class AirWallCollisionSpecify : public ksys::act::ai::Behavior {
    SEAD_RTTI_OVERRIDE(AirWallCollisionSpecify, ksys::act::ai::Behavior)
public:
    explicit AirWallCollisionSpecify(const InitArg& arg);
    void m7() override;
    void m8() override;
    void loadParams() override;
    // 0x71006163b4
    void sub_71006163B4(ksys::phys::RigidBody* body);
    // 0x7100616700
    void sub_7100616700(ksys::phys::RigidBody* body);

    /* 0x28 */ sead::Delegate1<AirWallCollisionSpecify, ksys::phys::RigidBody*> _28{this, &AirWallCollisionSpecify::sub_71006163B4};
    /* 0x48 */ s32 _48 = 3;
    /* 0x50 */ const int* mAirWallCollision_m{};
};
KSYS_CHECK_SIZE_NX150(AirWallCollisionSpecify, 0x58);

}  // namespace uking::behavior
