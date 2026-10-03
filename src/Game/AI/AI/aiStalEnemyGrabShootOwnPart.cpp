#include "Game/AI/AI/aiStalEnemyGrabShootOwnPart.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

StalEnemyGrabShootOwnPart::StalEnemyGrabShootOwnPart(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

StalEnemyGrabShootOwnPart::~StalEnemyGrabShootOwnPart() = default;

bool StalEnemyGrabShootOwnPart::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void StalEnemyGrabShootOwnPart::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void StalEnemyGrabShootOwnPart::calc_() {
    if (isFinished() || isFailed())
        return;

    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        if (isCurrentChild("投げる")) {
            setFinished();
            return;
        }
        if (child->isFinished() && mActor->getConnectedCalcChild()) {
            ksys::act::ai::InlineParamPack pack;
            pack.addVec3(*mTargetPos_d, "TargetPos", -1);
            changeChild("投げる", &pack);
        } else {
            setFailed();
        }
    } else if (isCurrentChild("投げる")) {
        child->setDynamicParam(*mTargetPos_d, "TargetPos");
    }
}

void StalEnemyGrabShootOwnPart::leave_() {
    mActor->resetConnectedCalcChild(false);
}

void StalEnemyGrabShootOwnPart::loadParams_() {
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

}  // namespace uking::ai
