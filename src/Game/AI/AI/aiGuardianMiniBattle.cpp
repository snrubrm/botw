#include "Game/AI/AI/aiGuardianMiniBattle.h"
#include "Game/AI/AI/aiGuardianMiniRoot.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/System/physNavMeshCharacter.h"

namespace uking::ai {

GuardianMiniBattle::GuardianMiniBattle(const InitArg& arg) : EnemyBattle(arg) {}

GuardianMiniBattle::~GuardianMiniBattle() = default;

bool GuardianMiniBattle::init_(sead::Heap* heap) {
    _144 = 100;
    return true;
}

void GuardianMiniBattle::enter_(ksys::act::ai::InlineParamPack* params) {
    EnemyBattle::enter_(params);
}

void GuardianMiniBattle::leave_() {
    EnemyBattle::leave_();
}

void GuardianMiniBattle::loadParams_() {
    EnemyBattle::loadParams_();
    getStaticParam(&mRootNodeName_s, "RootNodeName");
    getStaticParam(&mArm1NodeName_s, "Arm1NodeName");
    getStaticParam(&mArm2NodeName_s, "Arm2NodeName");
    getStaticParam(&mArm3NodeName_s, "Arm3NodeName");
    getStaticParam(&mASSlotRight_s, "ASSlotRight");
    getStaticParam(&mASSlotLeft_s, "ASSlotLeft");
    getStaticParam(&mASSlotBack_s, "ASSlotBack");
    getStaticParam(&mRollingInterval_s, "RollingInterval");
    getStaticParam(&mBaseDist_s, "BaseDist");
    getStaticParam(&mFarDist_s, "FarDist");
    getStaticParam(&mIsIgnoreArmCondition_s, "IsIgnoreArmCondition");
    getStaticParam(&mTurnMoveTime_s, "TurnMoveTime");
    getStaticParam(&mTurnMovePer_s, "TurnMovePer");
    getStaticParam(&mTurnMoveStartDist_s, "TurnMoveStartDist");
    getStaticParam(&mCounterStartDamageCount_s, "CounterStartDamageCount");
    getStaticParam(&mCounterStartTime_s, "CounterStartTime");
    getStaticParam(&mCheckOnNoNavMesh_s, "CheckOnNoNavMesh");
    getAITreeVariable(&mDamagedCount_a, "DamagedCount");
}

bool GuardianMiniBattle::isChangeable() const {
    return isCurrentChild("戦闘準備") || isCurrentChild("旋回移動");
}

void GuardianMiniBattle::m44() {}

// NON_MATCHING: the original loads NavMeshCharacter::_2a4 as a word and masks it with 0xffff; ours uses ldrh
bool GuardianMiniBattle::m45() {
    if (!sub_71004282EC(mActor))
        return false;
    auto* nav = mActor->m45();
    if (nav && (nav->_2a4 & 0xffff) == 0x17)
        return false;
    if (*mCounterStartTime_s < 1)
        return false;
    return _1a0.value <= sead::Mathf::epsilon();
}

}  // namespace uking::ai
