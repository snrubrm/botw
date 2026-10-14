#include "Game/Actor/AI/aiSetTargetPosForFlyThroughMove.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

SetTargetPosForFlyThroughMove::SetTargetPosForFlyThroughMove(const InitArg& arg)
    : ksys::act::ai::Ai(arg) {}

SetTargetPosForFlyThroughMove::~SetTargetPosForFlyThroughMove() = default;

bool SetTargetPosForFlyThroughMove::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void SetTargetPosForFlyThroughMove::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(*mTargetPos_d, "TargetPos", -1);
    changeChild("移動", &pack);
}

// NON_MATCHING: the two SafeString temporaries at the end are stored with two str each instead of one stp
void SetTargetPosForFlyThroughMove::calc_() {
    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        if (isCurrentChild("移動")) {
            if (!child->isFinished()) {
                setFailed();
            } else {
                sub_7100568EA8(&_50);
                ksys::act::ai::InlineParamPack pack;
                pack.addVec3(_50, "TargetPos", -1);
                changeChild("通過移動", &pack);
            }
        } else if (child->isFinished()) {
            setFinished();
        } else {
            setFailed();
        }
    } else if (child->isChangeable() && isCurrentChild("移動")) {
        const sead::Vector3f diff = mActor->getMtx().getTranslation() - *mTargetPos_d;
        if (diff.length() <= *mTargetPosFixDist_s) {
            sub_7100568EA8(&_50);
            ksys::act::ai::InlineParamPack pack;
            pack.addVec3(_50, "TargetPos", -1);
            changeChild("通過移動", &pack);
        }
    }

    const bool is_through = isCurrentChild("通過移動");
    getCurrentChild()->setDynamicParam(is_through ? _50 : *mTargetPos_d, "TargetPos");
}

void SetTargetPosForFlyThroughMove::leave_() {
    ksys::act::ai::Ai::leave_();
}

void SetTargetPosForFlyThroughMove::loadParams_() {
    getStaticParam(&mTargetPosFixDist_s, "TargetPosFixDist");
    getStaticParam(&mThroughDist_s, "ThroughDist");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

}  // namespace uking::ai
