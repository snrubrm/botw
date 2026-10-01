#include "Game/AI/AI/aiStraightMove.h"
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

void StraightMove::m34(const sead::Vector3f& pos) {
    ksys::act::ai::InlineParamPack params;
    params.addVec3(pos, "TargetPos", -1);
    params.addVec3(pos, "MoveAwayFromPos", -1);
    changeChild("移動", &params);
}

}  // namespace uking::ai
