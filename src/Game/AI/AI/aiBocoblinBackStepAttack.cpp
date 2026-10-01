#include "Game/AI/AI/aiBocoblinBackStepAttack.h"
#include <random/seadGlobalRandom.h>
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

BocoblinBackStepAttack::BocoblinBackStepAttack(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

BocoblinBackStepAttack::~BocoblinBackStepAttack() = default;

void BocoblinBackStepAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    if (sead::GlobalRandom::instance()->getS32Range(0, 100) < *mAttackPer_d) {
        sead::Vector3f pos = *mTargetPos_d;
        ksys::act::ai::InlineParamPack pack;
        pack.addVec3(pos, "TargetPos", -1);
        changeChild("バックステップアタック", &pack);
    } else {
        sead::Vector3f pos = *mTargetPos_d;
        ksys::act::ai::InlineParamPack pack;
        pack.addVec3(pos, "TargetPos", -1);
        changeChild("バックステップ", &pack);
    }
}

bool BocoblinBackStepAttack::isChangeable() const {
    return getCurrentChild()->isChangeable();
}

bool BocoblinBackStepAttack::isFinished() const {
    return ksys::act::ai::Ai::isFinished() || getCurrentChild()->isFinished();
}

void BocoblinBackStepAttack::loadParams_() {
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getDynamicParam(&mAttackPer_d, "AttackPer");
}

void BocoblinBackStepAttack::calc_() {
    getCurrentChild()->setDynamicParam(*mTargetPos_d, "TargetPos");
    if (getCurrentChild()->isFinished())
        setFinished();
    else if (getCurrentChild()->isFailed())
        setFailed();
}

}  // namespace uking::ai
