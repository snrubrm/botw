#include "Game/AI/Action/actionForkNoHitGroundCrawl.h"
#include "KingSystem/ActorSystem/actActor.h"
#include <algorithm>
#include <math/seadMathCalcCommon.h>
#include "Game/AI/aiUnk_71007377D4.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"

namespace uking::action {

ForkNoHitGroundCrawl::ForkNoHitGroundCrawl(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ForkNoHitGroundCrawl::~ForkNoHitGroundCrawl() = default;

bool ForkNoHitGroundCrawl::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ForkNoHitGroundCrawl::enter_(ksys::act::ai::InlineParamPack* params) {
    const auto& vel = mActor->getVelocity();
    const f32 speed = sead::Mathf::sqrt(vel.x * vel.x + vel.z * vel.z);
    _38.value = speed;
    _38.prev_value = speed;
    mFlags.set(Flag::Changeable);
}

void ForkNoHitGroundCrawl::leave_() {
    ksys::act::ai::Action::leave_();
}

void ForkNoHitGroundCrawl::loadParams_() {
    getStaticParam(&mMaxSpeed_s, "MaxSpeed");
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getStaticParam(&mEndRadius_s, "EndRadius");
}

// NON_MATCHING: the original recomputes &actor->getMtx() for the final copy (ours keeps it in a
// callee-saved register) and orders the dir subtractions differently
void ForkNoHitGroundCrawl::calc_() {
    _38 += 0.2f;

    auto* actor = mActor;
    sead::Vector3f pos;
    actor->getMtx().getTranslation(pos);
    sead::Vector3f dir = *mTargetPos_d - pos;
    f32 dist = dir.normalize();
    if (dist < *mMaxSpeed_s)
        _38.setToMin(dist);
    else
        _38.setToMin(*mMaxSpeed_s);
    _38.updateStats();

    pos += dir * sead::Mathf::min(dist, _38.mean);
    pos.y += 1.0f;
    const f32 y = pos.y;
    pos.y = mTargetPos_d->y + 1.0f;
    if (!somePositionCalc(&pos, pos, -sead::Vector3f::ey, 10.0f)) {
        pos.y = y;
        if (!somePositionCalc(&pos, pos, -sead::Vector3f::ey, 10.0f))
            pos.y += -10.0f;
    }

    sead::Matrix34f mtx = actor->getMtx();
    mtx.setTranslation(pos);
    if (auto* body = actor->getMainBody())
        body->changePositionAndRotation(mtx, sead::Mathf::epsilon());

    const sead::Vector2f diff(pos.x - mTargetPos_d->x, pos.z - mTargetPos_d->z);
    if (diff.length() < *mEndRadius_s)
        setFinished();
}

}  // namespace uking::action
