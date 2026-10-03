#pragma once

#include <math/seadVector.h>
#include <prim/seadRuntimeTypeInfo.h>
#include <prim/seadSafeString.h>
#include "KingSystem/Utils/Types.h"

namespace ksys::phys {

class RigidBody;

class UserTag {
    SEAD_RTTI_BASE(UserTag)
public:
    // Argument of m5. CharacterController::sub_7100F62790 (the event handler of the controller's
    // collisions) passes its own argument to the user tag of the controller's rigid body and then
    // stores a copy of it (0x48 bytes) in the controller (+0x180 / +0x1c8).
    struct Unk5 {
        u32 _0;
        f32 _4;
        u32 _8;
        u8 _c;
        u8 _d;  // 3 / 4: tested by PhysicsUserTag::m5 and the controller
        u8 _e;
        u8 _f;
        u32 _10;
        u32 _14;
        u32 _18;
        RigidBody* _20;  // the other body (PhysicsUserTag::m5 reads its type)
        u32 _28;
        u32 _2c;
        u32 _30;
        f32 _34;
        sead::Vector3f _38;
        f32 _44;
    };
    KSYS_CHECK_SIZE_NX150(Unk5, 0x48);

    UserTag() = default;

    /// Called when a rigid body goes beyond the broadphase border.
    /// The default implementation just notifies the rigid body of this callback.
    virtual void onMaxPositionExceeded(RigidBody* body);
    virtual void onImpulse(RigidBody* body_a, RigidBody* body_b, float impulse_a);
    virtual void onBodyShapeChanged(RigidBody* body);
    virtual void m5(Unk5* arg);
    virtual const sead::SafeString& getName() const { return sead::SafeString::cEmptyString; }
    virtual void m7(RigidBody* rigid_body, int a);
    virtual const sead::SafeString& getName(RigidBody* rigid_body) const {
        return sead::SafeString::cEmptyString;
    }
    virtual ~UserTag() = default;
};
KSYS_CHECK_SIZE_NX150(UserTag, 0x8);

}  // namespace ksys::phys
