#include "Game/AI/AI/aiTargetPosRotFromMyPos.h"
#include <random/seadGlobalRandom.h>
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

TargetPosRotFromMyPos::TargetPosRotFromMyPos(const InitArg& arg) : TargetPosAI(arg) {}

TargetPosRotFromMyPos::~TargetPosRotFromMyPos() = default;

bool TargetPosRotFromMyPos::init_(sead::Heap* heap) {
    return TargetPosAI::init_(heap);
}

void TargetPosRotFromMyPos::enter_(ksys::act::ai::InlineParamPack* params) {
    mAngle = *mIsRandSign_s ?
                 s32((sead::GlobalRandom::instance()->getU32() & 2) - 1) * *mAngle_s :
                 *mAngle_s;
    TargetPosAI::enter_(params);
}

void TargetPosRotFromMyPos::calc_() {
    TargetPosAI::calc_();
}

void TargetPosRotFromMyPos::leave_() {
    TargetPosAI::leave_();
}

// NON_MATCHING: the original computes the later params' `this + off` addresses before the first call
// and keeps them in callee-saved registers (extra frame slot); same family as WeaponOnetimeUse
void TargetPosRotFromMyPos::loadParams_() {
    TargetPosAI::loadParams_();
    getStaticParam(&mIsRandSign_s, "IsRandSign");
    getStaticParam(&mAngle_s, "Angle");
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getStaticParam(&mMinDist_s, "MinDist");
}

void TargetPosRotFromMyPos::m35(sead::Vector3f* pos) {
    const sead::Vector3f target = *mTargetPos_d;
    const sead::Vector3f my_pos = mActor->getMtx().getTranslation();
    sead::Vector3f diff = target - my_pos;

    const f32 xz_dist = sead::Mathf::sqrt(diff.x * diff.x + diff.z * diff.z);
    const f32 min_dist = *mMinDist_s;
    if (xz_dist < min_dist) {
        const f32 len = sead::Vector3f(diff.x, 0.0f, diff.z).length();
        if (len > 0.0f) {
            const f32 scale = min_dist / len;
            diff.x *= scale;
            diff.z *= scale;
        }
    }

    sead::Matrix34f mtx;
    mtx.makeR(mAngle);
    diff.rotate(mtx);
    *pos = diff + my_pos;
}

}  // namespace uking::ai
