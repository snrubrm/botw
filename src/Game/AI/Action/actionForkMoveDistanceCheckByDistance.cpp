#include "Game/AI/Action/actionForkMoveDistanceCheckByDistance.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

ForkMoveDistanceCheckByDistance::ForkMoveDistanceCheckByDistance(const InitArg& arg) : Fork(arg) {}

ForkMoveDistanceCheckByDistance::~ForkMoveDistanceCheckByDistance() = default;

bool ForkMoveDistanceCheckByDistance::init_(sead::Heap* heap) {
    return Fork::init_(heap);
}

void ForkMoveDistanceCheckByDistance::enter_(ksys::act::ai::InlineParamPack* params) {
    Fork::enter_(params);
    mActor->getMtx().getTranslation(_38);
}

void ForkMoveDistanceCheckByDistance::leave_() {
    Fork::leave_();
}

void ForkMoveDistanceCheckByDistance::loadParams_() {
    Fork::loadParams_();
    getStaticParam(&mIsCheckOnlyXZ_s, "IsCheckOnlyXZ");
}

// NON_MATCHING: same structure as ForkEndByDistance::calc_ (branch on IsCheckOnlyXZ, no fcsel); the original loads the
// actor Z translation with an integer load and allocates x9 / x10 for the actor / flag pointers.
void ForkMoveDistanceCheckByDistance::calc_() {
    Fork::calc_();
    const sead::Vector3f pos = mActor->getMtx().getTranslation();
    const bool only_xz = *mIsCheckOnlyXZ_s;
    const f32 dx = _38.x - pos.x;
    const f32 dz = _38.z - pos.z;
    f32 sum;
    if (only_xz) {
        sum = dx * dx;
    } else {
        const f32 dy = _38.y - pos.y;
        sum = dx * dx + dy * dy;
    }
    if (sead::Mathf::sqrt(dz * dz + sum) >= m32())
        setEndState();
}

float ForkMoveDistanceCheckByDistance::m32() {
    return 0.0f;
}

}  // namespace uking::action
