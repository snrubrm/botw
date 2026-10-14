#include "Game/Actor/AI/aiTrolleyGrabbedByMagnet.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actUnk_71006e45c4.h"

namespace uking::ai {

TrolleyGrabbedByMagnet::TrolleyGrabbedByMagnet(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

TrolleyGrabbedByMagnet::~TrolleyGrabbedByMagnet() = default;

bool TrolleyGrabbedByMagnet::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void TrolleyGrabbedByMagnet::enter_(ksys::act::ai::InlineParamPack* params) {
    if (auto* body = mActor->getMainBody())
        body->setFrictionScale(0.0f);
    mFlags.set(Flag::Changeable);
}

// NON_MATCHING: scheduling of the final interpolation (loads of the current angular velocity)
// Turns the trolley towards the rail direction while it is grabbed by Magnesis (finishes when released on the rail).
void TrolleyGrabbedByMagnet::calc_() {
    const f32 rail_dist = *mRailDist_d;
    const sead::Vector3f rail_pos = *mRailPos_d;
    sead::Vector3f rail_dir = *mRailDir_d;

    auto* grab = mActor->m128();
    if (!grab || !grab->m2()) {
        if (rail_dist >= 0.0f && rail_dist < 1.0f)
            setFinished();
        else
            setFailed();
        return;
    }

    if (rail_dist < 0.0f)
        return;

    const auto& mtx = mActor->getMtx();
    const sead::Vector3f pos = mtx.getTranslation();
    const sead::Vector3f front{mtx(0, 2), mtx(1, 2), mtx(2, 2)};
    if (rail_dir.dot(front) < 0.0f)
        rail_dir = -rail_dir;

    sead::Vector3f side;
    side.setCross(sead::Vector3f::ey, rail_dir);
    side.normalize();
    sead::Vector3f up;
    up.setCross(rail_dir, side);

    sead::Matrix34f target_mtx;
    target_mtx.setBase(0, side);
    target_mtx.setBase(1, up);
    target_mtx.setBase(2, rail_dir);
    target_mtx.setBase(3, rail_pos);

    auto* body = mActor->getMainBody();
    if (!body)
        return;

    sead::Vector3f linear_velocity;
    body->getLinearVelocity(&linear_velocity);
    sead::Vector3f angular_velocity;
    body->getAngularVelocity(&angular_velocity);
    sead::Vector3f target_linear;
    sead::Vector3f target_angular;
    body->computeVelocities(&target_linear, &target_angular, target_mtx);

    const f32 t = sead::Mathf::clamp(((rail_pos - pos).length() - 1.0f) / 6.0f, 0.0f, 1.0f);
    const f32 rate = 1.0f - t;
    const f32 len = target_angular.normalize();
    const f32 speed = sead::Mathf::sign(len) * std::min(sead::Mathf::abs(len), 1.0f);
    target_angular = angular_velocity + (target_angular * speed - angular_velocity) * rate;
    body->setAngularVelocity(target_angular);
}

void TrolleyGrabbedByMagnet::leave_() {
    if (auto* body = mActor->getMainBody())
        body->setFrictionScale(1.0f);
}

void TrolleyGrabbedByMagnet::loadParams_() {
    getDynamicParam(&mRailDist_d, "RailDist");
    getDynamicParam(&mRailPos_d, "RailPos");
    getDynamicParam(&mRailDir_d, "RailDir");
}

}  // namespace uking::ai
