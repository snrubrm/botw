#include "Game/Actor/AI/aiOctarockOptionRoot.h"
#include "Game/Actor/aiUnk_71005D6D10.h"
#include "KingSystem/Physics/System/physInstanceSet.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actPhysicsUserTag.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include <prim/seadDelegate.h>
#include "Game/Actor/Damage/dmgDamageManager.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/ActorSystem/actReaction.h"
#include "KingSystem/Physics/RigidBody/physRigidBodySet.h"
#include "KingSystem/XLink/xlinkActorUtil.h"

namespace uking::ai {

// Native calc 4ecffc constructs this 8-byte contact filter with vtable 240da18.
// The vtable has invoke, clone and isNoDummy slots of the existing delegate interface.
namespace {
class Unk_710240da18 : public sead::IDelegate2R<ksys::phys::RigidBody*, ksys::phys::RigidBody*, bool> {
public:
    bool invoke(ksys::phys::RigidBody*, ksys::phys::RigidBody* other) override;
};
}  // namespace
KSYS_CHECK_SIZE_NX150(Unk_710240da18, 8);

// 0x71004ed34c: accept contact with a player actor.
bool Unk_710240da18::invoke(ksys::phys::RigidBody*, ksys::phys::RigidBody* other) {
    if (other) {
        auto* tag = sead::DynamicCast<ksys::act::PhysicsUserTag>(other->getUserTag());
        if (tag) {
            ksys::act::ActorLinkConstDataAccess accessor;
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

void OctarockOptionRoot::calc_() {
    SimpleLiftable::calc_();

    if (*mIsBreakable_s) {
        auto* parent = sead::DynamicCast<ksys::act::Actor>(mActor->getConnectedCalcParent());
        if (!parent || sub_71007A2604(parent) || sub_71007A2604(mActor)) {
            if (mActor->m135())
                mActor->m135()->_4 = 1;
            callDeleteAndCreateDropAndEmit(mActor, 0);
        }
    }

    if (sub_71007A274C(mActor)) {
        auto* manager = sead::DynamicCast<act::DamageManager>(mActor->getDamageMgr());
        sead::Vector3f pos;
        if (manager && manager->getPosition(&pos)) {
            ksys::eft::sub_710105E000(mActor, 13, 1.0f);
            ksys::eft::searchAndEmitSLink(mActor, "Hit", false);
            Unk_71012419b4 handle{};
            xlinkSearchAndEmit(mActor, "Hit", 0, &handle);
            handle.sub_71012419B4(pos);
        }
    }

    auto* set = mActor->getRigidBodyByName(sub_71007A24D0()->cstr());
    if (!set || set->getRigidBodies().size() == 0)
        return;
    auto* body = set->getRigidBody(0);
    if (!body)
        return;
    Unk_710240da18 filter;
    if (!ksys::act::sub_7100EEB078(body, nullptr, &filter))
        return;
    auto* reaction = ksys::act::Reaction::instance();
    if (reaction && reaction->_a8)
        reaction->_a8->sub_7100EC66FC(mActor);
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
