#include "KingSystem/Physics/RigidBody/physRigidBodySet.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Physics/RigidBody/physRigidBodySetParamAccessor.h"

namespace ksys::phys {

RigidBodySet1::RigidBodySet1(const sead::SafeString& name) : RigidBodySet(name) {}

RigidBodySet1::~RigidBodySet1() {
    // NON_MATCHING: the original recomputes the body-array address from this for every
    // access; ours keeps it in a saved register (one extra mov, writeback addressing).
    const s32 num = getRigidBodies().size();
    for (s32 i = 0; i < num; ++i) {
        if (getRigidBodies()[i]->isAddedToWorld())
            getRigidBodies()[i]->removeFromWorldImmediately();
        delete getRigidBodies()[i];
    }
    getRigidBodies().freeBuffer();
}

bool RigidBodySet1::sub_71012B047C(RigidBodySetParamAccessor* accessor, sead::Heap* heap) {
    // NON_MATCHING: same array-address caching difference as the destructor above.
    const int count = accessor->m0();
    getRigidBodies().allocBuffer(count, heap, 8);
    for (s32 i = 0; i < count; ++i) {
        RigidBody* body = accessor->m1(i, heap);
        if (!body) {
            const s32 num = getRigidBodies().size();
            for (s32 j = 0; j < num; ++j) {
                if (getRigidBodies()[j]->isAddedToWorld())
                    getRigidBodies()[j]->removeFromWorldImmediately();
                delete getRigidBodies()[j];
            }
            getRigidBodies().freeBuffer();
            return false;
        }
        getRigidBodies().pushBack(body);
    }
    return true;
}

}  // namespace ksys::phys
