#include "Game/AI/AI/aiSubsAngleSelect.h"
#include <math/seadMathCalcCommon.h>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

SubsAngleSelect::SubsAngleSelect(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

SubsAngleSelect::~SubsAngleSelect() = default;

bool SubsAngleSelect::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

// NON_MATCHING: the original builds the target direction with an integer-domain sign flip/select for
// dir.y (fmov/eor/csel) and keeps the actor pointer cached; the float form here compiles differently.
f32 SubsAngleSelect::getFrontDot() const {
    auto* actor = mActor;
    sead::Vector3f diff = actor->getMtx().getTranslation() - *mTargetPos_d;
    sead::Vector3f dir{-diff.x, *mYRotOnly_s ? 0.0f : -diff.y, -diff.z};
    dir.normalize();
    sead::Vector3f front;
    actor->getMtx().getBase(front, 2);
    return front.dot(dir);
}

void SubsAngleSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    const f32 dot = getFrontDot();
    if (dot < sead::Mathf::cos(*mSubsAngle_s)) {
        ksys::act::ai::InlineParamPack child_params;
        child_params.addVec3(*mTargetPos_d, "TargetPos", -1);
        changeChild("角度差大", &child_params);
    } else {
        ksys::act::ai::InlineParamPack child_params;
        child_params.addVec3(*mTargetPos_d, "TargetPos", -1);
        changeChild("角度差小", &child_params);
    }
}

void SubsAngleSelect::calc_() {
    auto* child = getCurrentChild();
    if (child->isChangeable() && !*mCheckOnce_s) {
        const bool is_small = isCurrentChild("角度差小");
        const f32 dot = getFrontDot();
        if (is_small) {
            if (dot < sead::Mathf::cos(*mSubsAngle_s)) {
                ksys::act::ai::InlineParamPack child_params;
                child_params.addVec3(*mTargetPos_d, "TargetPos", -1);
                changeChild("角度差大", &child_params);
                return;
            }
        } else if (!(dot < sead::Mathf::cos(*mSubsAngle_s))) {
            ksys::act::ai::InlineParamPack child_params;
            child_params.addVec3(*mTargetPos_d, "TargetPos", -1);
            changeChild("角度差小", &child_params);
            return;
        }
    }
    child->setDynamicParam(*mTargetPos_d, "TargetPos");
}

void SubsAngleSelect::leave_() {
    ksys::act::ai::Ai::leave_();
}

void SubsAngleSelect::loadParams_() {
    getStaticParam(&mSubsAngle_s, "SubsAngle");
    getStaticParam(&mCheckOnce_s, "CheckOnce");
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getStaticParam(&mYRotOnly_s, "YRotOnly");
}

bool SubsAngleSelect::isFailed() const {
    return ksys::act::ai::Ai::isFailed() || getCurrentChild()->isFailed();
}

}  // namespace uking::ai
