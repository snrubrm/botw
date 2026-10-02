#include "Game/AI/AI/aiTargetPosDirLRSelect.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

TargetPosDirLRSelect::TargetPosDirLRSelect(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

TargetPosDirLRSelect::~TargetPosDirLRSelect() = default;

bool TargetPosDirLRSelect::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

// NON_MATCHING: scheduling — the original loads the actor's base vector and translation (six floats) before the
// target position; ours interleaves them
void TargetPosDirLRSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    sead::Vector3f left;
    mActor->getMtx().getBase(left, 0);
    const sead::Vector3f pos = mActor->getMtx().getTranslation();
    const sead::Vector3f diff = *mTargetPos_d - pos;
    if (left.dot(diff) < 0.0f) {
        ksys::act::ai::InlineParamPack child_params;
        child_params.addVec3(*mTargetPos_d, "TargetPos", -1);
        changeChild("右側", &child_params);
    } else {
        ksys::act::ai::InlineParamPack child_params;
        child_params.addVec3(*mTargetPos_d, "TargetPos", -1);
        changeChild("左側", &child_params);
    }
}

// NON_MATCHING: same scheduling difference as enter_
void TargetPosDirLRSelect::calc_() {
    auto* child = getCurrentChild();
    if (!child->isFinished() && !child->isFailed() && child->isChangeable() &&
        *mIsCheckEveryFrame_s) {
        const bool is_left = isCurrentChild("左側");
        sead::Vector3f left;
        mActor->getMtx().getBase(left, 0);
        const sead::Vector3f pos = mActor->getMtx().getTranslation();
    const sead::Vector3f diff = *mTargetPos_d - pos;
        const f32 dot = left.dot(diff);
        if (is_left) {
            if (dot < 0.0f) {
                ksys::act::ai::InlineParamPack child_params;
                child_params.addVec3(*mTargetPos_d, "TargetPos", -1);
                changeChild("右側", &child_params);
                return;
            }
        } else if (!(dot < 0.0f)) {
            ksys::act::ai::InlineParamPack child_params;
            child_params.addVec3(*mTargetPos_d, "TargetPos", -1);
            changeChild("左側", &child_params);
            return;
        }
    }
    getCurrentChild()->setDynamicParam(*mTargetPos_d, "TargetPos");
}

void TargetPosDirLRSelect::leave_() {
    ksys::act::ai::Ai::leave_();
}

void TargetPosDirLRSelect::loadParams_() {
    getStaticParam(&mIsCheckEveryFrame_s, "IsCheckEveryFrame");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

bool TargetPosDirLRSelect::isFailed() const {
    return ksys::act::ai::Ai::isFailed() || getCurrentChild()->isFailed();
}

}  // namespace uking::ai
