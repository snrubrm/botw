#pragma once

#include <prim/seadDelegate.h>
#include "KingSystem/ActorSystem/actAiBehavior.h"

namespace ksys::phys {
class RigidBody;
}

namespace uking::behavior {

class AirWallMaterialSpecify : public ksys::act::ai::Behavior {
    SEAD_RTTI_OVERRIDE(AirWallMaterialSpecify, ksys::act::ai::Behavior)
public:
    explicit AirWallMaterialSpecify(const InitArg& arg);
    void m8() override;
    // 0x7100616964
    void sub_7100616964(ksys::phys::RigidBody* body);

    /* 0x28 */ sead::Delegate1<AirWallMaterialSpecify, ksys::phys::RigidBody*> _28{this, &AirWallMaterialSpecify::sub_7100616964};
    /* 0x48 */ u32 _48;
    /* 0x4c */ u32 _4c;
    /* 0x50 */ u64 _50;
};
KSYS_CHECK_SIZE_NX150(AirWallMaterialSpecify, 0x58);

}  // namespace uking::behavior
