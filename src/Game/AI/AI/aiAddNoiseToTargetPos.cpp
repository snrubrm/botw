#include "Game/AI/AI/aiAddNoiseToTargetPos.h"
#include <random/seadGlobalRandom.h>
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Utils/MathUtil.h"

namespace uking::ai {

addNoiseToTargetPos::addNoiseToTargetPos(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

addNoiseToTargetPos::~addNoiseToTargetPos() = default;

bool addNoiseToTargetPos::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

// NON_MATCHING: the original loads Vector3f::ey before reading the actor's front vector and keeps the
// random numbers in other registers (same operations and operand order otherwise).
void addNoiseToTargetPos::enter_(ksys::act::ai::InlineParamPack* params) {
    const f32 left_max = *mRandLeftMax_s;
    const f32 right_max = *mRandRightMax_s;
    const f32 y_min = *mRandYMin_s;
    const f32 y_max = *mRandYMax_s;
    const f32 dist_min = *mRandDistMin_s;
    const f32 dist_max = *mRandDistMax_s;
    const f32 side = sead::GlobalRandom::instance()->getF32Range(left_max, right_max);
    const f32 height = sead::GlobalRandom::instance()->getF32Range(y_min, y_max);
    const f32 dist = sead::GlobalRandom::instance()->getF32Range(dist_min, dist_max);

    sead::Vector3f right;
    mActor->getMtx().getBase(right, 0);
    right.normalize();
    right.y = 0.0f;
    right.normalize();

    sead::Vector3f front;
    mActor->getMtx().getBase(front, 2);
    front.y = 0.0f;
    front.normalize();

    _78 = sead::Vector3f::ey * height + right * side;
    _78 += front * dist;

    sead::Vector3f target;
    sub_71002F8D1C(&target, *mTargetPos_d, _78);
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(target, "TargetPos", -1);
    changeChild("行動", &pack);
}

void addNoiseToTargetPos::leave_() {
    ksys::act::ai::Ai::leave_();
}

void addNoiseToTargetPos::sub_71002F8D1C(sead::Vector3f* result, const sead::Vector3f& target,
                                         const sead::Vector3f& noise) {
    const sead::Vector3f pos = mActor->getMtx().getTranslation();
    sead::Vector3f dir = target;
    dir -= pos;
    dir.normalize();
    sead::Vector3f point = target + noise;
    sead::Vector3f offset = point - pos;
    if (offset.dot(dir) < 0.0f) {
        sead::Vector3f perpendicular;
        ksys::util::sub_71011EFA00(&perpendicular, offset, dir);
        point = pos + perpendicular;
    }
    *result = point;
}

void addNoiseToTargetPos::calc_() {
    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        if (child->isFinished())
            setFinished();
        else
            setFailed();
    } else if (*mIsUpdateEveryFrame_s) {
        sead::Vector3f target;
        sub_71002F8D1C(&target, *mTargetPos_d, _78);
        child->setDynamicParam(target, "TargetPos");
    }
}

void addNoiseToTargetPos::loadParams_() {
    getStaticParam(&mRandYMin_s, "RandYMin");
    getStaticParam(&mRandYMax_s, "RandYMax");
    getStaticParam(&mRandLeftMax_s, "RandLeftMax");
    getStaticParam(&mRandRightMax_s, "RandRightMax");
    getStaticParam(&mRandDistMin_s, "RandDistMin");
    getStaticParam(&mRandDistMax_s, "RandDistMax");
    getStaticParam(&mIsUpdateEveryFrame_s, "IsUpdateEveryFrame");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

}  // namespace uking::ai
