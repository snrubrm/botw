#include "Game/AI/Action/actionForkEndByDistance.h"
#include <math/seadMathCalcCommon.h>
#include "Game/AI/aiUnk_71007320F0.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

ForkEndByDistance::ForkEndByDistance(const InitArg& arg) : Fork(arg) {}

ForkEndByDistance::~ForkEndByDistance() = default;

bool ForkEndByDistance::init_(sead::Heap* heap) {
    return Fork::init_(heap);
}

void ForkEndByDistance::enter_(ksys::act::ai::InlineParamPack* params) {
    Fork::enter_(params);
}

void ForkEndByDistance::leave_() {
    Fork::leave_();
}

void ForkEndByDistance::loadParams_() {
    Fork::loadParams_();
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mEndMode_s, "EndMode");
    getStaticParam(&mEndDist_s, "EndDist");
    getStaticParam(&mIsOnlyXZ_s, "IsOnlyXZ");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

// NON_MATCHING: the original loads the actor Z translation with an integer load (ldr w; fmov) and orders the position loads
// differently; the branches, sums and end checks are identical
void ForkEndByDistance::calc_() {
    Fork::calc_();
    auto* actor = mActor;
    sead::Vector3f pos;
    actor->getMtx().getTranslation(pos);
    const f32 dx = pos.x - mTargetPos_d->x;
    const f32 dz = pos.z - mTargetPos_d->z;
    f32 sum;
    if (*mIsOnlyXZ_s) {
        sum = dx * dx;
    } else {
        const f32 dy = pos.y - mTargetPos_d->y;
        sum = dx * dx + dy * dy;
    }
    const f32 dist = sead::Mathf::sqrt(dz * dz + sum);
    const f32 end_dist = sub_71007320F0(actor, *mWeaponIdx_s) + *mEndDist_s;
    if (*mEndMode_s) {
        if (dist >= end_dist)
            setEndState();
    } else {
        if (dist <= end_dist)
            setEndState();
    }
}

}  // namespace uking::action
