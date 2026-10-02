#include "Game/AI/Action/actionDemoChangeEntityNoHit.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Physics/RigidBody/physRigidBodySet.h"
#include "KingSystem/Physics/System/physInstanceSet.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

DemoChangeEntityNoHit::DemoChangeEntityNoHit(const InitArg& arg) : ksys::act::ai::Action(arg) {}

DemoChangeEntityNoHit::~DemoChangeEntityNoHit() = default;

bool DemoChangeEntityNoHit::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void DemoChangeEntityNoHit::loadParams_() {
    getStaticParam(&mSetMotionType_s, "SetMotionType");
    getStaticParam(&mIsNoHit_s, "IsNoHit");
}

bool DemoChangeEntityNoHit::oneShot_() {
    auto* physics = mActor->getPhysics();
    if (!physics)
        return false;

    if (auto* set = physics->findBodyByName(*sub_71007A24E4())) {
        for (int i = 0; i < set->getRigidBodies().size(); ++i) {
            auto* body = set->getRigidBodies()[i];
            if (!body)
                continue;
            // The original tests SetMotionType here (IsNoHit is never read).
            if (*mSetMotionType_s)
                body->setContactLayer(ksys::phys::ContactLayer::EntityNoHit);
            else
                physics->sub_7100FBAF18(body);
            if (*mSetMotionType_s >= 0 && *mSetMotionType_s <= 2)
                body->changeMotionType(ksys::phys::MotionType(*mSetMotionType_s));
        }
    }
    return true;
}

}  // namespace uking::action
