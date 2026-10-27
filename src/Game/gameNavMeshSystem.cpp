#include "Game/gameNavMeshSystem.h"
#include "KingSystem/Physics/RigidBody/Shape/physBoxShape.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Physics/RigidBody/physRigidBodyBox.h"
#include "KingSystem/Physics/RigidBody/physRigidBodyParam.h"
#include "KingSystem/Physics/System/physHavokAI.h"
#include "KingSystem/Physics/System/physUserTag.h"
#include <math/seadBoundBox.h>

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
        explicit Tag(Entry* entry) : _8(entry) {}

        void onBodyShapeChanged(ksys::phys::RigidBody* body) override;

        Entry* _8;
    };

    struct Box {
        sead::Vector3f min;
        sead::Vector3f max;
    };

    Entry();

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
    static_assert(sizeof(sead::BoundBox3f) == 0x18);

    ksys::phys::NavMeshObjMaybe nav;
    ksys::phys::RigidBody* body;
    Tag tag;
    // One slot per sub-material (the `id & 0xffff` of sub_7100E8F1C0, clamped to
    // 16 slottable ids), plus the union of the occupied slots that the rigid
    // body's extents follow.
    sead::SafeArray<sead::BoundBox3f, 16> boxes;
    sead::BoundBox3f bounds;
};

void NavMeshSystem::Entry::Tag::onBodyShapeChanged(ksys::phys::RigidBody*) {
    _8->nav.sub_7100F7F428(_8->body);
}

NavMeshSystem::Entry::Entry() : nav(), body(nullptr), tag(this), boxes() {}

// NON_MATCHING: identical instructions except the loop preheader's counter copy
// (`mov w21, w23`); clang keeps the counter in the size register here instead of
// moving it aside for the motion-type constant.
void NavMeshSystem::init(sead::Heap* heap) {
    if (!mEntries.tryAllocBuffer(0x14, heap) && mEntries.size() == 0)
        return;

    for (auto& entry : mEntries) {
        ksys::phys::BoxParam param;
        param.motion_type = ksys::phys::MotionType::Keyframed;
        param.contact_layer = ksys::phys::ContactLayer::EntityNoHit;
        param.name = "NavMeshGrassFire";
        entry.body = ksys::phys::BoxRigidBody::make(&param, heap);
        entry.body->setUserTag(&entry.tag);
        entry.nav.sub_7100F7EF8C(entry.body, 2, true, ksys::phys::NavMeshSubMaterial::Fire, 0,
                                 sead::SafeString("NavMeshGrassFire"));
    }
}

// NON_MATCHING: the singleton disposer and deleteInstance inline the buffer teardown
// differently; the disposer also saves an extra register around the base destructor.
SEAD_SINGLETON_DISPOSER_IMPL(NavMeshSystem)

// NON_MATCHING: the buffer teardown is outlined into Buffer<Entry>::freeBuffer.
NavMeshSystem::~NavMeshSystem() {
    mEntries.freeBuffer();
}

}  // namespace uking
