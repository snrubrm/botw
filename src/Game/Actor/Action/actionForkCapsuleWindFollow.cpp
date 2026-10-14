#include "Game/Actor/Action/actionForkCapsuleWindFollow.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

ForkCapsuleWindFollow::ForkCapsuleWindFollow(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ForkCapsuleWindFollow::~ForkCapsuleWindFollow() {
    _40.destroy(false);
}

bool ForkCapsuleWindFollow::init_(sead::Heap* heap) {
    _40.sub_71010C42B4();
    return true;
}

// NON_MATCHING: matrix-product scheduling, as in calc_.
void ForkCapsuleWindFollow::enter_(ksys::act::ai::InlineParamPack* params) {
    sead::Vector3f dir = *mDir_s;
    dir.normalize();
    if (dir.x == 0.0f && dir.y == 0.0f && dir.z == 0.0f)
        dir = sead::Vector3f::ez;
    sub_7100149878(&_c8, sead::Vector3f::ez, dir);

    sead::Matrix34f matrix;
    sead::Matrix34CalcCommon<f32>::multiply(matrix, mActor->getMtx(), _c8);
    _40.sub_71010C449C(*mSpeed_s, *mRadius_s * mActor->getScale().y, *mLength_s, matrix);
}

void ForkCapsuleWindFollow::leave_() {
    _40.destroy(false);
}

void ForkCapsuleWindFollow::loadParams_() {
    getStaticParam(&mRadius_s, "Radius");
    getStaticParam(&mSpeed_s, "Speed");
    getStaticParam(&mLength_s, "Length");
    getStaticParam(&mDir_s, "Dir");
}

// NON_MATCHING: matrix-product loads, arithmetic and stores have different scheduling.
void ForkCapsuleWindFollow::calc_() {
    sead::Matrix34f matrix;
    sead::Matrix34CalcCommon<f32>::multiply(matrix, mActor->getMtx(), _c8);
    _40.sub_71010C449C(*mSpeed_s, *mRadius_s * mActor->getScale().y, *mLength_s, matrix);
}

bool ForkCapsuleWindFollow::hasUpdateForPreDeleteCb() {
    return true;
}

bool ForkCapsuleWindFollow::updateForPreDelete() {
    return _40.sub_71010C4284();
}

// NON_MATCHING: same arithmetic (sead makeVectorRotation + fromQuat) but different register allocation and a
// different operand order in the quaternion-to-matrix products.
bool ForkCapsuleWindFollow::sub_7100149878(sead::Matrix33f* mtx, const sead::Vector3f& from,
                                           const sead::Vector3f& to) {
    sead::Quatf q;
    const bool ok = q.makeVectorRotation(from, to);
    mtx->fromQuat(q);
    return ok;
}

}  // namespace uking::action
