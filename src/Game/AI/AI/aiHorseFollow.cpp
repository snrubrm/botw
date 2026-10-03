#include "Game/AI/AI/aiHorseFollow.h"
#include <math/seadMathCalcCommon.h>
#include "Game/Actor/actHorseStrings.h"
#include "Game/Actor/actRideable.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/System/Timer.h"
#include "KingSystem/XLink/xlinkActorUtil.h"

namespace uking::ai {

HorseFollow::HorseFollow(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

HorseFollow::~HorseFollow() = default;

bool HorseFollow::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void HorseFollow::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void HorseFollow::calc_() {
    if (_cc >= 0.0f) {
        ksys::Timer::update(&_cc, 1.0f);
        if (_cc >= *mSuccessEndDelays_s)
            setFinished();
        return;
    }

    const f32 dist = m35();
    const f32 cry_dist = *mDistanceThresholdCry_s;
    if (cry_dist > sead::Mathf::epsilon()) {
        auto* as_list = mActor->getASList();
        const f32 cry_dist_sq = cry_dist * cry_dist;
        if (!(dist < cry_dist_sq) || !(cry_dist_sq <= _d0)) {
            if (as_list->x_1(1, 0) == act::sUnk_71026031a0 && as_list->x_4(1, 0)) {
                if (auto* rideable = mActor->m132())
                    rideable->_18.sub_7100E78E00();
                else
                    as_list->sub_710115B01C(1, 0, true);
            }
        } else if (as_list->x_1(1, 0) != act::sUnk_71026031a0) {
            as_list->startAnimationMaybe(-1.0f, -1.0f, act::sUnk_71026031a0, 1, 0, true);
            ksys::eft::searchAndEmitSLink(mActor, "CryComing", false);
        }
        _d0 = dist;
    }
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
