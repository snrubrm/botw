#include "Game/AI/Action/actionForkCapsuleWindFollow.h"

namespace uking::action {

ForkCapsuleWindFollow::ForkCapsuleWindFollow(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ForkCapsuleWindFollow::~ForkCapsuleWindFollow() {
    _40.destroy(false);
}

bool ForkCapsuleWindFollow::init_(sead::Heap* heap) {
    _40.sub_71010C42B4();
    return true;
}

void ForkCapsuleWindFollow::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
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

void ForkCapsuleWindFollow::calc_() {
    ksys::act::ai::Action::calc_();
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
