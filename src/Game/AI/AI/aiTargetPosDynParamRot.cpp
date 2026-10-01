#include "Game/AI/AI/aiTargetPosDynParamRot.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

TargetPosDynParamRot::TargetPosDynParamRot(const InitArg& arg) : TargetPosAI(arg) {}

TargetPosDynParamRot::~TargetPosDynParamRot() = default;

bool TargetPosDynParamRot::init_(sead::Heap* heap) {
    return TargetPosAI::init_(heap);
}

void TargetPosDynParamRot::enter_(ksys::act::ai::InlineParamPack* params) {
    TargetPosAI::enter_(params);
}

void TargetPosDynParamRot::calc_() {
    TargetPosAI::calc_();
}

void TargetPosDynParamRot::leave_() {
    TargetPosAI::leave_();
}

void TargetPosDynParamRot::loadParams_() {
    TargetPosAI::loadParams_();
    getStaticParam(&mMinDist_s, "MinDist");
    getDynamicParam(&mAngle_d, "Angle");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

void TargetPosDynParamRot::m35(sead::Vector3f* pos) {
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

void TargetPosDynParamRot::m36(sead::Vector3f* pos) {
    mActor->getMtx().getTranslation(*pos);
}

}  // namespace uking::ai
