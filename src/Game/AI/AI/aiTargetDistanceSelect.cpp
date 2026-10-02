#include "Game/AI/AI/aiTargetDistanceSelect.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

TargetDistanceSelect::TargetDistanceSelect(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

TargetDistanceSelect::~TargetDistanceSelect() = default;

bool TargetDistanceSelect::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void TargetDistanceSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    if (m34() <= *mBoundaryDistance_s * *mBoundaryDistance_s)
        sub_71005BE078();
    else
        sub_71005BE164();
}

void TargetDistanceSelect::sub_71005BE078() {
    ksys::act::ai::InlineParamPack params;
    params.addVec3(*mTargetPos_d, "TargetPos", -1);
    params.addVec3(*mTargetPos_d, "MoveAwayFromPos", -1);
    changeChild("内側", &params);
}

void TargetDistanceSelect::sub_71005BE164() {
    ksys::act::ai::InlineParamPack params;
    params.addVec3(*mTargetPos_d, "TargetPos", -1);
    params.addVec3(*mTargetPos_d, "MoveAwayFromPos", -1);
    changeChild("外側", &params);
}

void TargetDistanceSelect::calc_() {
    float distance = *mBoundaryDistance_s;
    if (isCurrentChild("内側"))
        distance += *mOverlapDistance_s;
    else if (isCurrentChild("外側"))
        distance -= *mOverlapDistance_s;

    const float distance_sq = m34();
    auto* child = getCurrentChild();
    if (child->isFinished()) {
        if (child->isFinished())
            setFinished();
        else
            setFailed();
    } else if (child->isFailed()) {
        if (child->isFinished())
            setFinished();
        else
            setFailed();
    } else if (child->isChangeable()) {
        if (distance_sq <= distance * distance) {
            if (!isCurrentChild("内側"))
                sub_71005BE078();
        } else {
            if (!isCurrentChild("外側"))
                sub_71005BE164();
        }
    }

    if (*mIsUpdateTarget_s)
        child->setDynamicParam(*mTargetPos_d, "TargetPos");
}

void TargetDistanceSelect::leave_() {
    ksys::act::ai::Ai::leave_();
}

void TargetDistanceSelect::loadParams_() {
    getStaticParam(&mBoundaryDistance_s, "BoundaryDistance");
    getStaticParam(&mOverlapDistance_s, "OverlapDistance");
    getStaticParam(&mIsUpdateTarget_s, "IsUpdateTarget");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

bool TargetDistanceSelect::isFailed() const {
    return ksys::act::ai::Ai::isFailed() || getCurrentChild()->isFailed();
}

bool TargetDistanceSelect::isFinished() const {
    return ksys::act::ai::Ai::isFinished() || getCurrentChild()->isFinished();
}

float TargetDistanceSelect::m34() {
    return (mActor->getMtx().getTranslation() - *mTargetPos_d).squaredLength();
}

}  // namespace uking::ai
