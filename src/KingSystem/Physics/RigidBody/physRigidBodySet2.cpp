#include "KingSystem/Physics/RigidBody/physRigidBodySet.h"

namespace ksys::phys {

RigidBodySet2::RigidBodySet2(const sead::SafeString& name, RigidBodyResource* resource)
    : RigidBodySet(name) {
    _38 = 0;
    _28 = resource;
    _30 = nullptr;
}

}  // namespace ksys::phys
