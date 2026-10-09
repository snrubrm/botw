#include "Game/AI/AI/aiOctarockOptionRoot.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/Physics/System/physInstanceSet.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actPhysicsUserTag.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include <prim/seadDelegate.h>

namespace uking::ai {

// Native calc 4ecffc constructs this 8-byte contact filter with vtable 240da18.
// The vtable has invoke, clone and isNoDummy slots of the existing delegate interface.
class Unk_710240da18 : public sead::IDelegate2R<ksys::phys::RigidBody*, ksys::phys::RigidBody*, bool> {
public:
    bool invoke(ksys::phys::RigidBody*, ksys::phys::RigidBody* other) override;
};
KSYS_CHECK_SIZE_NX150(Unk_710240da18, 8);

// 0x71004ed34c: accept contact with a player actor.
bool Unk_710240da18::invoke(ksys::phys::RigidBody*, ksys::phys::RigidBody* other) {
    if (other) {
        auto* tag = sead::DynamicCast<ksys::act::PhysicsUserTag>(other->getUserTag());
        if (tag) {
            ksys::act::ActorConstDataAccess accessor;
            tag->acquireActor(&accessor);
            if (ksys::act::isPlayerProfile(accessor))
                return true;
        }
    }
    return false;
}

OctarockOptionRoot::OctarockOptionRoot(const InitArg& arg) : SimpleLiftable(arg) {}

OctarockOptionRoot::~OctarockOptionRoot() = default;

bool OctarockOptionRoot::init_(sead::Heap* heap) {
    return SimpleLiftable::init_(heap);
}

void OctarockOptionRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    SimpleLiftable::enter_(params);
    if (auto* physics = mActor->getPhysics()) {
        physics->sub_7100FBAC4C(ksys::phys::ContactLayer::EntityGround);
        physics->sub_7100FBAC4C(ksys::phys::ContactLayer::EntityGroundObject);
        physics->sub_7100FBAC4C(ksys::phys::ContactLayer::EntityGroundRough);
        physics->sub_7100FBAC4C(ksys::phys::ContactLayer::EntityGroundSmooth);
    }
    if (*mIsMimicry_s)
        sub_71005DD1CC(mActor, false, 1.0f, 5.0f);
}

void OctarockOptionRoot::leave_() {
    if (auto* physics = mActor->getPhysics())
        physics->sub_7100FBAD74();
}

void OctarockOptionRoot::loadParams_() {
    getStaticParam(&mIsBreakable_s, "IsBreakable");
    getStaticParam(&mIsMimicry_s, "IsMimicry");
}

}  // namespace uking::ai
