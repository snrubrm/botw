#include "Game/AI/AI/aiGuardAndRevenge.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

GuardAndRevenge::GuardAndRevenge(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

bool GuardAndRevenge::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void GuardAndRevenge::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(*mTargetPos_d, "TargetPos", -1);
    changeChild("ガード", &pack);
    mFlags.reset(Flag::Changeable);
}

void GuardAndRevenge::leave_() {
    ksys::act::ai::Ai::leave_();
}

void GuardAndRevenge::loadParams_() {
    getStaticParam(&mDrownDepth_s, "DrownDepth");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

bool GuardAndRevenge::isFinished() const {
    return ActionBase::isFinished() || (!isCurrentChild("ガード") && getCurrentChild()->isFinished());
}

void GuardAndRevenge::calc_() {
    bool drowning = false;
    if (*mDrownDepth_s > 0.0f && mActor->get68f().load()) {
        const f32 y = mActor->getMtx().m[1][3];
        drowning = mActor->get6f0() - y > *mDrownDepth_s;
    }

    if (drowning) {
        changeChild("水死");
    } else {
        auto* child = getCurrentChild();
        if (child->isFinished() || child->isFailed()) {
            if (isCurrentChild("ガード")) {
                ksys::act::ai::InlineParamPack pack;
                pack.addVec3(*mTargetPos_d, "TargetPos", -1);
                mFlags.set(Flag::Changeable);
                changeChild("反撃", &pack);
            } else {
                setFinished();
            }
        }
    }
    getCurrentChild()->setDynamicParam(*mTargetPos_d, "TargetPos");
}

}  // namespace uking::ai
