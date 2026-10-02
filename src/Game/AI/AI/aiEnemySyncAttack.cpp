#include "Game/AI/AI/aiEnemySyncAttack.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

EnemySyncAttack::EnemySyncAttack(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

EnemySyncAttack::~EnemySyncAttack() = default;

void EnemySyncAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void EnemySyncAttack::leave_() {
    ksys::act::ai::Ai::leave_();
}

void EnemySyncAttack::loadParams_() {
    getStaticParam(&mNormalASSlot_s, "NormalASSlot");
    getStaticParam(&mAttackASSlot_s, "AttackASSlot");
    getStaticParam(&mJustAvoidCheckLength_s, "JustAvoidCheckLength");
    getStaticParam(&mJustAvoidCheckAngle_s, "JustAvoidCheckAngle");
    getStaticParam(&mRootNodeName_s, "RootNodeName");
    getStaticParam(&mAttackNodeName_s, "AttackNodeName");
    getStaticParam(&mAttackNodeNameWait_s, "AttackNodeNameWait");
    getStaticParam(&mAttackASName_s, "AttackASName");
    getStaticParam(&mAtNodeName_s, "AtNodeName");
    getStaticParam(&mAttackDistMin_s, "AttackDistMin");
    getStaticParam(&mAttackDistMax_s, "AttackDistMax");
    getStaticParam(&mAttackInterval_s, "AttackInterval");
    getStaticParam(&mAttackIntervalRand_s, "AttackIntervalRand");
}

bool EnemySyncAttack::isChangeable() const {
    if (_c8)
        return false;
    return getCurrentChild()->isChangeable();
}

bool EnemySyncAttack::isFinished() const {
    if (ActionBase::isFinished())
        return true;
    if (isCurrentChild("行動") && getCurrentChild()->isFinished()) {
        auto* as_list = mActor->getASList();
        return as_list && as_list->x_4(*mAttackASSlot_s, 0);
    }
    return false;
}

bool EnemySyncAttack::isFailed() const {
    if (ActionBase::isFailed())
        return true;
    if (isCurrentChild("行動") && getCurrentChild()->isFailed()) {
        auto* as_list = mActor->getASList();
        return as_list && as_list->x_4(*mAttackASSlot_s, 0);
    }
    return false;
}

}  // namespace uking::ai
