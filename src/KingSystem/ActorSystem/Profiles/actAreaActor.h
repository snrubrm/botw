#pragma once

#include <prim/seadDelegate.h>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::phys {
class RigidBody;
}  // namespace ksys::phys

namespace ksys::act {

// Names from the CSV (AreaActor::ctor 0x7100e252b8, AirWall::construct 0x7100e2452c: new(0x8a0), Area::construct
// 0x7100e24c34: new(0x898)). AirWall's RTTI static is at 0x71025afe68. The namespace is a guess.
// TODO: incomplete (only what the AirWall behaviors need; overrides and the AreaActor fields are not
// declared yet).
class AreaActor : public Actor {
    SEAD_RTTI_OVERRIDE(AreaActor, Actor)
public:
    /* 0x840 */ u8 _840[0x890 - 0x840];
};
KSYS_CHECK_SIZE_NX150(AreaActor, 0x890);

class AirWall : public AreaActor {
    SEAD_RTTI_OVERRIDE(AirWall, AreaActor)
public:
    using RigidBodyCallback = sead::IDelegate1<phys::RigidBody*>;

    // 0x7100e245b8 / 0x7100e245c0 (not decompiled): set _890 / _898 and update the rigid bodies
    // (0x7100e2677c).
    void sub_7100E245B8(RigidBodyCallback* callback);
    void sub_7100E245C0(RigidBodyCallback* callback);

    /* 0x890 */ RigidBodyCallback* _890;
    /* 0x898 */ RigidBodyCallback* _898;
};
KSYS_CHECK_SIZE_NX150(AirWall, 0x8a0);

}  // namespace ksys::act
