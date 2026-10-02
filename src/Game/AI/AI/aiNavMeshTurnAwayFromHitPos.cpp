#include "Game/AI/AI/aiNavMeshTurnAwayFromHitPos.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

NavMeshTurnAwayFromHitPos::NavMeshTurnAwayFromHitPos(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

NavMeshTurnAwayFromHitPos::~NavMeshTurnAwayFromHitPos() = default;

bool NavMeshTurnAwayFromHitPos::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void NavMeshTurnAwayFromHitPos::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void NavMeshTurnAwayFromHitPos::calc_() {
    if (isFinished() || isFailed())
        return;

    auto* child = getCurrentChild();
    if (child) {
        if (!child->isFinished() && !child->isFailed())
            return;

        if (!child->isFailed()) {
            if (isCurrentChild("回転") && *mMoveToSafePosAfterTurn_s) {
                ksys::act::ai::InlineParamPack params;
                params.addVec3(_60, "TargetPos", -1);
                changeChild("移動", &params);
            } else {
                setFinished();
            }
            return;
        }
    }
    setFailed();
}

void NavMeshTurnAwayFromHitPos::leave_() {
    ksys::act::ai::Ai::leave_();
}

void NavMeshTurnAwayFromHitPos::loadParams_() {
    getStaticParam(&mNumLOSCheckMax_s, "NumLOSCheckMax");
    getStaticParam(&mLOSCheckLength_s, "LOSCheckLength");
    getStaticParam(&mMoveToSafePosAfterTurn_s, "MoveToSafePosAfterTurn");
    getDynamicParam(&mHitPos_d, "HitPos");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

}  // namespace uking::ai
