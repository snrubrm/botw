#include "Game/AI/AI/aiEnemyNotice.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

EnemyNotice::EnemyNotice(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

void EnemyNotice::enter_(ksys::act::ai::InlineParamPack* params) {
    if (sub_710072DDB8(*mTargetPos_d, mActor->getMtx(), *mTurnStartAngle_s)) {
        ksys::act::ai::InlineParamPack pack;
        pack.addVec3(*mTargetPos_d, "TargetPos", -1);
        changeChild("追跡", &pack);
    } else {
        ksys::act::ai::InlineParamPack pack;
        pack.addVec3(*mTargetPos_d, "TargetPos", -1);
        changeChild("ターン", &pack);
    }
}

void EnemyNotice::leave_() {
    sub_71005DB3EC(mActor);
}

void EnemyNotice::loadParams_() {
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getStaticParam(&mTurnStartAngle_s, "TurnStartAngle");
}

bool EnemyNotice::isFinished() const {
    return isCurrentChild("追跡") && getCurrentChild()->isFinished();
}

bool EnemyNotice::isFailed() const {
    return isCurrentChild("追跡") && getCurrentChild()->isFailed();
}

// NON_MATCHING: stack slot of pos (the target places it below the param pack)
void EnemyNotice::calc_() {
    sead::Vector3f pos = *mTargetPos_d;
    sub_71005DB198(&pos, mActor);
    sub_71005DB068(mActor, pos);

    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        if (isCurrentChild("ターン")) {
            ksys::act::ai::InlineParamPack pack;
            pack.addVec3(*mTargetPos_d, "TargetPos", -1);
            changeChild("追跡", &pack);
        } else if (isFailed()) {
            setFailed();
        } else {
            setFinished();
        }
    } else {
        getCurrentChild()->setDynamicParam(*mTargetPos_d, "TargetPos");
    }
}

}  // namespace uking::ai
