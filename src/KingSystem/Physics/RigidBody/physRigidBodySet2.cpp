#include "KingSystem/Physics/RigidBody/physRigidBodySet.h"
#include <Havok/Common/Serialize/Util/hkNativePackfileUtils.h>
#include "KingSystem/Physics/RigidBody/physRigidBody.h"

namespace ksys::phys {

RigidBodySet2::RigidBodySet2(const sead::SafeString& name, RigidBodyResource* resource)
    : RigidBodySet(name) {
    _38 = 0;
    _28 = resource;
    _30 = nullptr;
}

RigidBodySet2::~RigidBodySet2() {
    sub_71012AFEB8();
}

void RigidBodySet2::sub_71012AFEB8() {
    // NON_MATCHING: the original recomputes the body-array address from this for every
    // access; ours keeps it in a saved register (one extra mov, writeback addressing).
    // Tried direct mRigidBodies access (via protected): identical codegen. Logged HARD.
    const s32 num = getRigidBodies().size();
    for (s32 i = 0; i < num; ++i) {
        getRigidBodies()[i]->removeFromWorldImmediately();
        delete getRigidBodies()[i];
    }
    getRigidBodies().freeBuffer();
    if (_30) {
        hkNativePackfileUtils::unloadInPlace(_30, _38);
        delete[] static_cast<u8*>(_30);
        _30 = nullptr;
    }
}

}  // namespace ksys::phys
