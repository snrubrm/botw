#include "Game/AI/AI/aiLynelNavMoveTarget.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

LynelNavMoveTarget::LynelNavMoveTarget(const InitArg& arg) : LynelNavMoveNoStop(arg) {}

LynelNavMoveTarget::~LynelNavMoveTarget() = default;

bool LynelNavMoveTarget::init_(sead::Heap* heap) {
    return LynelNavMoveNoStop::init_(heap);
}

void LynelNavMoveTarget::enter_(ksys::act::ai::InlineParamPack* params) {
    LynelNavMoveNoStop::enter_(params);
}

void LynelNavMoveTarget::leave_() {
    LynelNavMoveNoStop::leave_();
}

void LynelNavMoveTarget::loadParams_() {
    LynelNavMoveNoStop::loadParams_();
    getStaticParam(&mStopGear_s, "StopGear");
    getStaticParam(&mCliffCheckDist_s, "CliffCheckDist");
}

void LynelNavMoveTarget::calc_() {
    const auto changeToLookAround = [this] {
        ksys::act::ai::InlineParamPack pack;
        pack.addVec3(*mTargetPos_d, "TargetPos", -1);
        changeChild("見まわす", &pack);
    };

    auto* child = getCurrentChild();
    if (isCurrentChild("ブレーキ")) {
        if (!child->isFinished() && !child->isFailed()) {
            sub_7100493058();
            sub_71004930D0();
            return;
        }
        if (sub_7100493790(false))
            return;
        if (!sub_7100492DDC()) {
            changeToLookAround();
            return;
        }
    } else if (isCurrentChild("回転")) {
        if (!child->isFinished() && !child->isFailed()) {
            sub_7100493058();
            return;
        }
        if (sub_710072E154(mActor, *mTargetPos_d, nullptr, -1)) {
            changeToGoStraight();
            return;
        }
        if (sub_7100492CB8()) {
            changeToMove();
            return;
        }
        if (!sub_7100492DDC()) {
            changeToLookAround();
            return;
        }
    } else if (isCurrentChild("見まわす")) {
        if (!child->isFinished() && !child->isFailed()) {
            if (child->isChangeable() && sub_7100493790(false))
                return;
            sub_7100493058();
            sub_71004930D0();
            return;
        }
        if (sub_7100493790(false))
            return;
    } else {
        LynelNavMoveNoStop::calc_();
        return;
    }
    sub_71004923C0();
    setFailed();
}

bool LynelNavMoveTarget::m35() {
    return true;
}

}  // namespace uking::ai
