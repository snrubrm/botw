#include "Game/AI/Action/actionAirWallHorse.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/Physics/RigidBody/Shape/Box/physBoxRigidBody.h"
#include "KingSystem/Physics/RigidBody/physRigidBodySet.h"
#include "KingSystem/Physics/System/physInstanceSet.h"

namespace uking::action {

AirWallHorse::AirWallHorse(const InitArg& arg) : ksys::act::ai::Action(arg) {}

AirWallHorse::~AirWallHorse() = default;

bool AirWallHorse::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void AirWallHorse::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* physics = mActor->getPhysics();
    if (!physics)
        return;
    auto* set = physics->findBodyByName(*sub_71007A24E4());
    if (!set)
        return;
    const int num_bodies = set->getRigidBodies().size();
    for (int i = 0; i < num_bodies; ++i) {
        if (auto* box = sead::DynamicCast<ksys::phys::BoxRigidBody>(set->getRigidBody(i))) {
            sead::Vector3f extents;
            extents.x = mActor->getScale().x * 2;
            extents.y = mActor->getScale().y * 2;
            extents.z = mActor->getScale().z * 2;
            box->setExtents(extents);
        }
    }
    physics->setMtxAndScale(mActor->getMtx(), false, false, 1.0f);
    physics->sub_7100FBA9BC();
    physics->sub_7100FC012C(nullptr);
}

void AirWallHorse::leave_() {
    ksys::act::ai::Action::leave_();
}

void AirWallHorse::loadParams_() {}

void AirWallHorse::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
