#include "Game/AI/AI/aiOctarockOptionRoot.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/Physics/System/physInstanceSet.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

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
