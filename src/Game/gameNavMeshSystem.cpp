#include "Game/gameNavMeshSystem.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Physics/System/physHavokAI.h"
#include "KingSystem/Physics/System/physUserTag.h"

namespace uking {

// Constructor 0x7100e8f4a8 and the reverse teardown in 0x7100e8ec6c establish
// the NavMeshObjMaybe member, rigid body and record stride. The ctor also stores
// the vtable at 0x71024ed718 in the sub-object at +0xb8, whose back-pointer to
// the entry follows at +0xc0; that is the rigid body's user tag.
struct NavMeshSystem::Entry {
    // The rigid body's user tag for this entry. Its vtable's RTTI slots return
    // phys::UserTag's type info, so the class is a plain UserTag subclass (no
    // SEAD_RTTI_OVERRIDE); it only overrides the shape-change notification,
    // which re-registers the nav mesh object with the entry's new body.
    struct Tag : public ksys::phys::UserTag {
        void onBodyShapeChanged(ksys::phys::RigidBody* body) override;

        Entry* _8;
    };

    ~Entry() {
        nav.sub_7100F7F6A0();
        if (body) {
            if (body->isAddedToWorld())
                body->removeFromWorldImmediately(nullptr);
            delete body;
        }
        body = nullptr;
    }
    static_assert(sizeof(Tag) == 0x10);

    ksys::phys::NavMeshObjMaybe nav;
    ksys::phys::RigidBody* body;
    Tag tag;
    u8 _c8[0x260 - 0xc8];
};

void NavMeshSystem::Entry::Tag::onBodyShapeChanged(ksys::phys::RigidBody*) {
    _8->nav.sub_7100F7F428(_8->body);
}

// NON_MATCHING: the singleton disposer and deleteInstance inline the buffer teardown
// differently; the disposer also saves an extra register around the base destructor.
SEAD_SINGLETON_DISPOSER_IMPL(NavMeshSystem)

// NON_MATCHING: the buffer teardown is outlined into Buffer<Entry>::freeBuffer.
NavMeshSystem::~NavMeshSystem() {
    mEntries.freeBuffer();
}

}  // namespace uking
