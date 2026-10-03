#include "Game/AI/Action/actionMoveToTargetDir.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Utils/MathUtil.h"

namespace uking::action {

MoveToTargetDir::MoveToTargetDir(const InitArg& arg) : MoveToTargetBase(arg) {}

MoveToTargetDir::~MoveToTargetDir() = default;

bool MoveToTargetDir::init_(sead::Heap* heap) {
    return MoveToTargetBase::init_(heap);
}

void MoveToTargetDir::enter_(ksys::act::ai::InlineParamPack* params) {
    MoveToTargetBase::enter_(params);
    if (auto* body = mActor->getMainBody())
        body->changeMotionType(ksys::phys::MotionType::Keyframed);
    _60 = *mDynTargetPos_d;
}

void MoveToTargetDir::leave_() {
    MoveToTargetBase::leave_();
    if (auto* body = mActor->getMainBody())
        body->changeMotionType(ksys::phys::MotionType::Dynamic);
}

void MoveToTargetDir::loadParams_() {
    MoveToTargetBase::loadParams_();
    getDynamicParam(&mFrontDir_d, "FrontDir");
    getDynamicParam(&mDynTargetPos_d, "DynTargetPos");
    getDynamicParam(&mDynStartPos_d, "DynStartPos");
    getMapUnitParam(&mRailMoveSpeed_m, "RailMoveSpeed");
}

// NON_MATCHING: the original loads *mDynTargetPos_d before _60 for `_60 - *mDynTargetPos_d`; ours loads
// _60 first (rest identical).
void MoveToTargetDir::calc_() {
    MoveToTargetBase::calc_();
    auto* body = mActor->getMainBody();
    if (!body)
        return;

    f32 angle;
    sead::Vector3f axis;
    sead::Vector3f front;
    sead::Vector3f dir;
    sead::Matrix34f mtx;
    body->getTransform(&mtx);
    mtx.getBase(front, 2);
    dir = _60 - *mDynTargetPos_d;
    dir.normalize();
    ksys::util::sub_71011EEB08(&axis, &angle, front, dir, sead::Vector3f::ey);
    body->setAngularVelocity(axis * angle * 30.0f, sead::Mathf::epsilon());
    _60 = *mDynTargetPos_d;
}

bool MoveToTargetDir::m32(sead::Vector3f* pos, const sead::Vector3f* target) {
    MoveToTargetBase::m32(pos, target);
    return false;
}

f32 MoveToTargetDir::m33() {
    return *mRailMoveSpeed_m;
}

}  // namespace uking::action
