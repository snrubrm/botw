#include "Game/AI/AI/aiConditionMoveActionSelect.h"
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
