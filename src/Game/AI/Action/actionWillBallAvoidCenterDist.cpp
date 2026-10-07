#include "Game/AI/Action/actionWillBallAvoidCenterDist.h"
#include <geom/seadGeometry.h>
#include <geom/seadSegment.h>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Utils/MathUtil.h"

namespace uking::action {

WillBallAvoidCenterDist::WillBallAvoidCenterDist(const InitArg& arg) : WillBallAction(arg) {}

WillBallAvoidCenterDist::~WillBallAvoidCenterDist() = default;

bool WillBallAvoidCenterDist::init_(sead::Heap* heap) {
    return WillBallAction::init_(heap);
}

void WillBallAvoidCenterDist::enter_(ksys::act::ai::InlineParamPack* params) {
    WillBallAction::enter_(params);
}

void WillBallAvoidCenterDist::leave_() {
    WillBallAction::leave_();
}

void WillBallAvoidCenterDist::loadParams_() {
    WillBallAction::loadParams_();
    getStaticParam(&mDist_s, "Dist");
    getStaticParam(&mMaxDist_s, "MaxDist");
    getStaticParam(&mMiddleDist_s, "MiddleDist");
    getDynamicParam(&mCenterPos_d, "CenterPos");
}

// NON_MATCHING: the original loads the actor position before mCenterPos_d (scheduling)
void WillBallAvoidCenterDist::calc_() {
    WillBallAction::calc_();
    const sead::Vector3f pos = mActor->getMtx().getTranslation();
    const sead::Vector3f center = *mCenterPos_d;
    sead::Vector3f diff = center - pos;
    diff.y = 0.0f;
    if (diff.length() > *mMaxDist_s)
        setFailed();
}

// NON_MATCHING: only the schedule of the stores that build the segment (the original stores `target.y = 0` after
// copying the start point, and copies the position with three separate stores).
void WillBallAvoidCenterDist::m32(sead::Vector3f* direction, f32* distance, f32* progress) {
    sead::Vector3f target = *mParams.mTargetPos_d;
    target.y += _8c;
    sead::Vector3f pos = mActor->getMtx().getTranslation();

    bool blocked = false;
    if (auto* query = Unk_710260de68::instance())
        blocked = query->sub_7100F85EB8(3.0f, &pos, &target, nullptr);

    pos.y = 0.0f;
    target.y = 0.0f;
    const sead::Segment3f segment{pos, target};
    sead::Vector3f center = *mCenterPos_d;
    center.y = 0.0f;

    if (blocked || !(sead::Geometry::calcSquaredDistancePointToSegment(center, segment, nullptr) <
                     *mDist_s * *mDist_s)) {
        WillBallAction::m32(direction, distance, progress);
        return;
    }

    WillBallAction::m32(direction, distance, progress);

    sead::Vector3f from_pos = pos - center;
    from_pos.normalize();
    sead::Vector3f to_target = target - center;
    const f32 target_dist = to_target.normalize();

    f32 angle;
    if (from_pos.z * to_target.x - from_pos.x * to_target.z < 0.0f) {
        direction->set(-from_pos.z, 0.0f, from_pos.x);
        if (target_dist > *mMiddleDist_s)
            angle = 5.0f;
        else if (target_dist < *mDist_s)
            angle = -5.0f;
        else
            return;
    } else {
        direction->set(from_pos.z, 0.0f, -from_pos.x);
        if (target_dist > *mMiddleDist_s)
            angle = -5.0f;
        else if (target_dist < *mDist_s)
            angle = 5.0f;
        else
            return;
    }
    ksys::util::sub_71011EF010(direction, angle);
}

}  // namespace uking::action
