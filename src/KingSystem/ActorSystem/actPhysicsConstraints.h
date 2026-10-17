#pragma once

#include <container/seadBuffer.h>
#include "KingSystem/Utils/Types.h"

namespace ksys::phys {
class Constraint;
class RigidBody;
}

namespace ksys::act {

class Actor;

class PhysicsConstraints {
public:
    PhysicsConstraints();
    ~PhysicsConstraints();

    bool initialize(Actor* actor, sead::Heap* heap);
    void finalize();
    void calc();
    // 0x7100d40194: detach body 1 when it is `body`, while actor access is safe.
    void sub_7100D40194(phys::RigidBody* body);

    s32 size() const { return mConstraints.size(); }

    // 0x7100d40338 (lane1 s22): requests every constraint that is active or has a pending request to
    // be switched off (Constraint::sub_7100F6A074); true if there was one. Placeholder name.
    bool sub_7100D40338();
    void sub_7100D403A8();

    // Iterated by AirOctaWoodBridge::calc_.
    sead::Buffer<phys::Constraint*> mConstraints;

private:
    bool _10 = false;
    bool _11 = false;
};
KSYS_CHECK_SIZE_NX150(PhysicsConstraints, 0x18);

}  // namespace ksys::act
