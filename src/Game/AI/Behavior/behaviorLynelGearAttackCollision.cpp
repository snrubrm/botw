#include "Game/AI/Behavior/behaviorLynelGearAttackCollision.h"

namespace uking::behavior {

LynelGearAttackCollision::LynelGearAttackCollision(const InitArg& arg)
    : ksys::act::ai::Behavior(arg) {}

// Empty-statement body as in upstream's GameDataFlagSelector::~GameDataFlagSelector() (96101229):
// the original keeps the vtable store that a defaulted destructor drops (SafeString member).
LynelGearAttackCollision::~LynelGearAttackCollision() {
    ;
}

bool LynelGearAttackCollision::m6(sead::Heap* heap) {
    return true;
}

void LynelGearAttackCollision::m9() {}

void LynelGearAttackCollision::loadParams() {
    getStaticParam(&mAttackIntensity_s, "AttackIntensity");
    getStaticParam(&mDamageScaleGear0_s, "DamageScaleGear0");
    getStaticParam(&mDamageScaleGear1_s, "DamageScaleGear1");
    getStaticParam(&mDamageScaleGear2_s, "DamageScaleGear2");
    getStaticParam(&mDamageScaleGear3_s, "DamageScaleGear3");
    getStaticParam(&mDamageScaleGearTop_s, "DamageScaleGearTop");
    getStaticParam(&mIsGuardPierce_s, "IsGuardPierce");
    getStaticParam(&mIsForceGuardBreak_s, "IsForceGuardBreak");
    getStaticParam(&mIsIniviciblePierce_s, "IsIniviciblePierce");
    getStaticParam(&mAttackRigidName_s, "AttackRigidName");
}

}  // namespace uking::behavior
