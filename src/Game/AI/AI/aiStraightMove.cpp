#include "Game/AI/AI/aiStraightMove.h"
#include <random/seadGlobalRandom.h>
#include "Game/AI/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Utils/MathUtil.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

StraightMove::StraightMove(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

StraightMove::~StraightMove() = default;

bool StraightMove::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void StraightMove::enter_(ksys::act::ai::InlineParamPack* params) {
    sead::Vector3f pos;
    sub_71005AC38C(0.0f, *mAngleLimit_s, *mDistanceMin_s, *mDistanceMax_s, &pos);
    m34(pos);
}

void StraightMove::calc_() {
    auto* child = getCurrentChild();
    if (!child)
        return;
    if (!child->isFinished() && !child->isFailed())
        return;

    if (!child->isFailed()) {
        setFinished();
        return;
    }

    if (!*mIsRetryMove_s) {
        setFailed();
        return;
    }

    sead::Vector3f pos;
    sub_71005AC38C(*mRetryAngleMin_s, *mRetryAngleMax_s, *mDistanceMin_s, *mDistanceMax_s, &pos);
    m34(pos);
}

void StraightMove::leave_() {
    ksys::act::ai::Ai::leave_();
}

void StraightMove::loadParams_() {
    getStaticParam(&mAngleLimit_s, "AngleLimit");
    getStaticParam(&mDistanceMax_s, "DistanceMax");
    getStaticParam(&mDistanceMin_s, "DistanceMin");
    getStaticParam(&mRetryAngleMax_s, "RetryAngleMax");
    getStaticParam(&mRetryAngleMin_s, "RetryAngleMin");
    getStaticParam(&mIsRetryMove_s, "IsRetryMove");
}

// NON_MATCHING: instruction-identical except the order of three argument-saving moves after the first
// compare (mov v10 / v8 / x19 in the original)
void StraightMove::sub_71005AC38C(f32 min_angle, f32 max_angle, f32 min_dist, f32 max_dist,
                                  sead::Vector3f* out) {
    const sead::Vector3f pos = mActor->getMtx().getTranslation();

    f32 angle = sead::GlobalRandom::instance()->getF32Range(
        min_angle, sead::Mathf::max(min_angle, max_angle));
    angle *= f32(s32(sead::GlobalRandom::instance()->getU32() & 2) - 1);
    const f32 dist = sead::GlobalRandom::instance()->getF32Range(
        min_dist, sead::Mathf::max(min_dist, max_dist));

    sead::Vector3f dir = ksys::util::getCol(mActor->getMtx(), 2);
    const sead::Vector3f up = getUpDir(mActor);
    ksys::util::sub_71011EFA00(&dir, dir, up);
    ksys::util::sub_71011EF010(&dir, angle);
    dir.normalize();
    *out = pos + dir * dist;
}

void StraightMove::m34(const sead::Vector3f& pos) {
    ksys::act::ai::InlineParamPack params;
    params.addVec3(pos, "TargetPos", -1);
    params.addVec3(pos, "MoveAwayFromPos", -1);
    changeChild("移動", &params);
}

}  // namespace uking::ai
