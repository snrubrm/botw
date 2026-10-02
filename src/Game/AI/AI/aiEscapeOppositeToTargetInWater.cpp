#include "Game/AI/AI/aiEscapeOppositeToTargetInWater.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

EscapeOppositeToTargetInWater::EscapeOppositeToTargetInWater(const InitArg& arg)
    : ksys::act::ai::Ai(arg) {}

EscapeOppositeToTargetInWater::~EscapeOppositeToTargetInWater() = default;

bool EscapeOppositeToTargetInWater::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void EscapeOppositeToTargetInWater::enter_(ksys::act::ai::InlineParamPack* params) {
    _6c = mActor->getMtx().getTranslation();
    m34();
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(_60, "TargetPos", -1);
    pack.addVec3(*mTargetPos_d, "MoveAwayFromPos", -1);
    changeChild("移動", &pack);
}

void EscapeOppositeToTargetInWater::calc_() {
    if (isFinished())
        return;
    if (isFailed())
        return;

    auto* child = getCurrentChild();
    if (!child) {
        setFailed();
        return;
    }

    if (child->isFinished() || child->isFailed()) {
        if (isCurrentChild("移動")) {
            changeChild("待機");
            return;
        }
        if (isCurrentChild("待機")) {
            setFinished();
            return;
        }
    }

    if (!isCurrentChild("移動"))
        return;

    const sead::Vector3f pos = mActor->getMtx().getTranslation();
    if ((pos - _6c).squaredLength() > *mRunAwayDistanceMax_s * *mRunAwayDistanceMax_s)
        changeChild("待機");
}

void EscapeOppositeToTargetInWater::leave_() {
    ksys::act::ai::Ai::leave_();
}

void EscapeOppositeToTargetInWater::loadParams_() {
    getStaticParam(&mRunAwayDistanceMax_s, "RunAwayDistanceMax");
    getStaticParam(&mAllowRandAngleVertical_s, "AllowRandAngleVertical");
    getStaticParam(&mAllowRandAngleHorizontal_s, "AllowRandAngleHorizontal");
    getStaticParam(&mDivePercent_s, "DivePercent");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

}  // namespace uking::ai
