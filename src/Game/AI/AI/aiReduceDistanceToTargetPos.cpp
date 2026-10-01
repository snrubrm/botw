#include "Game/AI/AI/aiReduceDistanceToTargetPos.h"
#include <math/seadMathCalcCommon.h>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

ReduceDistanceToTargetPos::ReduceDistanceToTargetPos(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

ReduceDistanceToTargetPos::~ReduceDistanceToTargetPos() = default;

bool ReduceDistanceToTargetPos::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void ReduceDistanceToTargetPos::enter_(ksys::act::ai::InlineParamPack* params) {
    sub_710053AF70();
}

// NON_MATCHING: regalloc (dir.x/dir.z registers swapped, clamp operands)
void ReduceDistanceToTargetPos::sub_710053AF70() {
    const sead::Vector3f pos = mActor->getMtx().getTranslation();
    const sead::Vector3f target = *mTargetPos_d;
    sead::Vector3f dir = target - pos;
    const f32 dist = dir.normalize();
    f32 new_dist = dist * *mDistanceScale_s;
    if (*mMaxReduceDist_s >= 0.0f) {
        new_dist = dist - sead::Mathf::clamp(dist - new_dist, *mMinReduceDist_s,
                                             *mMaxReduceDist_s);
    }
    new_dist = sead::Mathf::clampMin(new_dist, *mMinDist_s);
    const sead::Vector3f target_pos = pos + dir * new_dist;

    ksys::act::ai::InlineParamPack params;
    params.addVec3(target_pos, "TargetPos", -1);
    changeChild("行動", &params);
}

// NON_MATCHING: regalloc (same as sub_710053AF70)
void ReduceDistanceToTargetPos::calc_() {
    const sead::Vector3f pos = mActor->getMtx().getTranslation();
    const sead::Vector3f target = *mTargetPos_d;
    sead::Vector3f dir = target - pos;
    const f32 dist = dir.normalize();
    f32 new_dist = dist * *mDistanceScale_s;
    if (*mMaxReduceDist_s >= 0.0f) {
        new_dist = dist - sead::Mathf::clamp(dist - new_dist, *mMinReduceDist_s,
                                             *mMaxReduceDist_s);
    }
    new_dist = sead::Mathf::clampMin(new_dist, *mMinDist_s);
    const sead::Vector3f target_pos = pos + dir * new_dist;
    getCurrentChild()->setDynamicParam(target_pos, "TargetPos");
}

void ReduceDistanceToTargetPos::leave_() {
    ksys::act::ai::Ai::leave_();
}

void ReduceDistanceToTargetPos::loadParams_() {
    getStaticParam(&mDistanceScale_s, "DistanceScale");
    getStaticParam(&mMinReduceDist_s, "MinReduceDist");
    getStaticParam(&mMaxReduceDist_s, "MaxReduceDist");
    getStaticParam(&mMinDist_s, "MinDist");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

}  // namespace uking::ai
