#include "Game/AI/AI/aiEnemySyncAttack.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

EnemySyncAttack::EnemySyncAttack(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

// The original keeps the vtable store that a defaulted destructor drops (same form as upstream's
// GameDataFlagSelector::~GameDataFlagSelector() { ; }, commit 96101229).
EnemySyncAttack::~EnemySyncAttack() {
    ;
}

void EnemySyncAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void EnemySyncAttack::leave_() {
    auto* actor = mActor;
    if (actor && actor->getModel()) {
        actor->getASList()->sub_710115B01C(*mAttackASSlot_s, 0, true);
        actor->getASList()->sub_710115C11C();
    }
    if (auto* body = mActor->findPhysicsBodyByName(sub_71007A24BC()->cstr(), "AtkEnemyBody"))
        sub_71007A2D34(body);
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
