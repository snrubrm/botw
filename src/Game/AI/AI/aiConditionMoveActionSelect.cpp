#include "Game/AI/AI/aiConditionMoveActionSelect.h"
#include "Game/AI/aiUnk_7100742478.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

ConditionMoveActionSelect::ConditionMoveActionSelect(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

ConditionMoveActionSelect::~ConditionMoveActionSelect() = default;

bool ConditionMoveActionSelect::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void ConditionMoveActionSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    _58 = false;
    changeChild("条件成功", params);
}

void ConditionMoveActionSelect::calc_() {
    bool reachable = true;
    if (*mCheckLineReachable_s)
        reachable = sub_7100742588(nullptr, mActor->m45(), mTargetPos_d, 10.0f);

    if (!_58 && reachable && isCurrentChild("条件失敗")) {
        changeToConditionSuccess();
    } else if ((!reachable || _58) && isCurrentChild("条件成功")) {
        changeToConditionFail();
    } else {
        getCurrentChild()->setDynamicParam(*mTargetPos_d, "TargetPos");
    }

    auto* child = getCurrentChild();
    if (child && (child->isFinished() || child->isFailed())) {
        if (child->isFailed()) {
            if (isCurrentChild("条件失敗")) {
                setFailed();
            } else {
                _58 = true;
                changeToConditionFail();
            }
        } else {
            setFinished();
        }
    }
}

void ConditionMoveActionSelect::leave_() {
    ksys::act::ai::Ai::leave_();
}

void ConditionMoveActionSelect::loadParams_() {
    getStaticParam(&mCheckLineReachable_s, "CheckLineReachable");
    getDynamicParam(&mDistanceKept_d, "DistanceKept");
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getDynamicParam(&mTargetActor_d, "TargetActor");
}

void ConditionMoveActionSelect::changeToConditionSuccess() {
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(*mTargetPos_d, "TargetPos", -1);
    if (mTargetActor_d)
        pack.addActor(*mTargetActor_d, "TargetActor", -1);
    if (mDistanceKept_d)
        pack.addFloat(*mDistanceKept_d, "DistanceKept", -1);
    changeChild("条件成功", &pack);
}

void ConditionMoveActionSelect::changeToConditionFail() {
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(*mTargetPos_d, "TargetPos", -1);
    if (mTargetActor_d)
        pack.addActor(*mTargetActor_d, "TargetActor", -1);
    if (mDistanceKept_d)
        pack.addFloat(*mDistanceKept_d, "DistanceKept", -1);
    changeChild("条件失敗", &pack);
}

}  // namespace uking::ai
