#include "Game/gameNavMeshSystem.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Physics/System/physHavokAI.h"

namespace uking {

// Constructor 0x7100e8f4a8 and the reverse teardown in 0x7100e8ec6c establish
// the NavMeshObjMaybe member, rigid body and record stride.
struct NavMeshSystem::Entry {
    ~Entry() {
        nav.sub_7100F7F6A0();
        if (body) {
            if (body->isAddedToWorld())
                body->removeFromWorldImmediately(nullptr);
            delete body;
        }
        body = nullptr;
    }
    ksys::phys::NavMeshObjMaybe nav;
    ksys::phys::RigidBody* body;
    u8 _b8[0x260 - 0xb8];
};

// NON_MATCHING: the singleton disposer and deleteInstance inline the buffer teardown
// differently; the disposer also saves an extra register around the base destructor.
SEAD_SINGLETON_DISPOSER_IMPL(NavMeshSystem)

// NON_MATCHING: the buffer teardown is outlined into Buffer<Entry>::freeBuffer.
NavMeshSystem::~NavMeshSystem() {
    mEntries.freeBuffer();
}

}  // namespace uking
