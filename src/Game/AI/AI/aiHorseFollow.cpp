#include "Game/AI/AI/aiHorseFollow.h"

namespace uking::ai {

HorseFollow::HorseFollow(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

HorseFollow::~HorseFollow() = default;

bool HorseFollow::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void HorseFollow::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void HorseFollow::leave_() {
    ksys::act::ai::Ai::leave_();
}

void HorseFollow::loadParams_() {
    getStaticParam(&mDistanceSuccessEnd_s, "DistanceSuccessEnd");
    getStaticParam(&mDistanceMovingToward_s, "DistanceMovingToward");
    getStaticParam(&mDistanceRequestingPath_s, "DistanceRequestingPath");
    getStaticParam(&mDistanceGivingUp_s, "DistanceGivingUp");
    getStaticParam(&mDistanceThresholdCry_s, "DistanceThresholdCry");
    getStaticParam(&mDistanceCheckAvoidance_s, "DistanceCheckAvoidance");
    getStaticParam(&mTargetVelocitySuccessEnd_s, "TargetVelocitySuccessEnd");
    getStaticParam(&mUpdateTargetPosFrames_s, "UpdateTargetPosFrames");
    getStaticParam(&mUpdateTargetPosFramesNear_s, "UpdateTargetPosFramesNear");
    getStaticParam(&mSuccessEndDelays_s, "SuccessEndDelays");
    getStaticParam(&mSideDistance_s, "SideDistance");
    getStaticParam(&mTargetVelocityDistanceSec_s, "TargetVelocityDistanceSec");
    getStaticParam(&mIsAvoidNavMeshActor_s, "IsAvoidNavMeshActor");
    getStaticParam(&mIsTargetPosEqualToLeaderPos_s, "IsTargetPosEqualToLeaderPos");
    getStaticParam(&mCanIgnorePlayer_s, "CanIgnorePlayer");
    getStaticParam(&mSelfPositionOffsetLocal_s, "SelfPositionOffsetLocal");
    getDynamicParam(&mDistanceKept_d, "DistanceKept");
    getDynamicParam(&mTargetActor_d, "TargetActor");
}

void HorseFollow::m34(sead::Vector3f* out, const sead::Vector3f& pos, const sead::Vector3f& target_pos,
                      const sead::Vector3f& target_velocity, const sead::Vector3f& up) {
    out->set(target_pos);

    if (*mSideDistance_s > 0.0f) {
        sead::Vector3f dir = target_pos - pos;
        dir.normalize();
        const f32 dot = dir.dot(up);
        sead::Vector3f side(up.x - dir.x * dot, 0.0f, up.z - dir.z * dot);
        if (side.normalize() == 0.0f)
            side.setCross(up, sead::Vector3f::ey);
        out->setScaleAdd(*mSideDistance_s, side, *out);
    }

    if (*mTargetVelocityDistanceSec_s > 0.0f)
        out->setScaleAdd(*mTargetVelocityDistanceSec_s * 30.0f, target_velocity, *out);
}

}  // namespace uking::ai
