#include "Game/AI/Action/actionMoveToTargetCurve.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"

namespace uking::action {

MoveToTargetCurve::MoveToTargetCurve(const InitArg& arg) : MoveToTargetCurveBase(arg) {}

MoveToTargetCurve::~MoveToTargetCurve() = default;

bool MoveToTargetCurve::init_(sead::Heap* heap) {
    return MoveToTargetCurveBase::init_(heap);
}

void MoveToTargetCurve::enter_(ksys::act::ai::InlineParamPack* params) {
    MoveToTargetCurveBase::enter_(params);
}

void MoveToTargetCurve::leave_() {
    MoveToTargetCurveBase::leave_();
}

void MoveToTargetCurve::loadParams_() {
    MoveToTargetCurveBase::loadParams_();
    getMapUnitParam(&mTargetPosition_m, "TargetPosition");
}

void MoveToTargetCurve::calc_() {
    MoveToTargetCurveBase::calc_();
}

void MoveToTargetCurve::m32() {
    if (auto* body = mActor->getMainBody())
        body->setContactAll();
}

void MoveToTargetCurve::m33(f32 dist, sead::Vector3f* pos) {
    if (auto* body = mActor->getMainBody()) {
        sead::Matrix34f mtx = mActor->getMtx();
        mtx.setTranslation(*pos);
        body->changePositionAndRotation(mtx, sead::Mathf::epsilon());
    }
    if (_60 > dist / _58)
        setFinished();
}

void MoveToTargetCurve::m34(sead::Vector3f* target) {
    target->set(*mTargetPosition_m);
}

f32 MoveToTargetCurve::m35(const sead::Vector3f* from, const sead::Vector3f* to) {
    const f32 dy = to->y - from->y;
    const f32 height = *mMaxHeight_s;
    return height > dy ? height : dy + 5.0f;
}

}  // namespace uking::action
