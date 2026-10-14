#include "Game/Actor/AI/aiTargetPosDynParamRotFromMyPos.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

TargetPosDynParamRotFromMyPos::TargetPosDynParamRotFromMyPos(const InitArg& arg) : TargetActorPos(arg) {}

TargetPosDynParamRotFromMyPos::~TargetPosDynParamRotFromMyPos() = default;

bool TargetPosDynParamRotFromMyPos::init_(sead::Heap* heap) {
    return TargetActorPos::init_(heap);
}

void TargetPosDynParamRotFromMyPos::enter_(ksys::act::ai::InlineParamPack* params) {
    TargetActorPos::enter_(params);
}

void TargetPosDynParamRotFromMyPos::calc_() {
    TargetActorPos::calc_();
}

void TargetPosDynParamRotFromMyPos::leave_() {
    TargetActorPos::leave_();
}

void TargetPosDynParamRotFromMyPos::loadParams_() {
    TargetActorPos::loadParams_();
    getStaticParam(&mMinDist_s, "MinDist");
    getDynamicParam(&mAngle_d, "Angle");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

void TargetPosDynParamRotFromMyPos::m35(sead::Vector3f* pos) {
    const sead::Vector3f target = *mTargetPos_d;
    sead::Vector3f center;
    m36(&center);
    sead::Vector3f diff = target - center;

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

    const sead::Vector3f angle = *mAngle_d;
    sead::Matrix34f mtx;
    mtx.makeR(angle);
    diff.rotate(mtx);
    *pos = diff + center;
}

void TargetPosDynParamRotFromMyPos::m36(sead::Vector3f* pos) {
    mActor->getMtx().getTranslation(*pos);
}

}  // namespace uking::ai
