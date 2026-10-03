#include "Game/AI/Action/actionTargetCircleMoveKeepDist.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "math/seadMathCalcCommon.h"

namespace uking::action {

TargetCircleMoveKeepDist::TargetCircleMoveKeepDist(const InitArg& arg) : TargetCircle(arg) {}

TargetCircleMoveKeepDist::~TargetCircleMoveKeepDist() = default;

bool TargetCircleMoveKeepDist::init_(sead::Heap* heap) {
    return TargetCircle::init_(heap);
}

void TargetCircleMoveKeepDist::enter_(ksys::act::ai::InlineParamPack* params) {
    const sead::Vector3f& target = *mTargetPos_d;
    const sead::Vector3f& pos = mActor->getMtx().getTranslation();
    const f32 dx = target.x - pos.x;
    const f32 dz = target.z - pos.z;
    const f32 dist = sead::Mathf::sqrt(dx * dx + dz * dz);
    _90 = sead::Mathf::max(*mRotDist_s, dist);
    TargetCircle::enter_(params);
    playAS(mASName_s.cstr(), true, 0, 0, -1.0f);
}

void TargetCircleMoveKeepDist::leave_() {
    TargetCircle::leave_();
}

void TargetCircleMoveKeepDist::loadParams_() {
    TargetCircle::loadParams_();
    getStaticParam(&mASName_s, "ASName");
}

void TargetCircleMoveKeepDist::calc_() {
    TargetCircle::calc_();
}

f32 TargetCircleMoveKeepDist::m32() {
    return _90;
}

}  // namespace uking::action
