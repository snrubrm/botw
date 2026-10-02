#include "Game/AI/Behavior/behaviorGiantGuardWeakPoint.h"

namespace uking::behavior {

GiantGuardWeakPoint::GiantGuardWeakPoint(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

void GiantGuardWeakPoint::loadParams() {
    getStaticParam(&mTargetBone_s, "TargetBone");
    getStaticParam(&mDelayTime_s, "DelayTime");
    getStaticParam(&mWeakPointArmorIdx_s, "WeakPointArmorIdx");
    getStaticParam(&mGuardAngleRange_s, "GuardAngleRange");
    getStaticParam(&mRestLifeRate_s, "RestLifeRate");
    getStaticParam(&mGuardStartAS_s, "GuardStartAS");
    getStaticParam(&mGuardLoopAS_s, "GuardLoopAS");
    getStaticParam(&mGuardEndAS_s, "GuardEndAS");
    getStaticParam(&mGuardTgName_s, "GuardTgName");
    getStaticParam(&mPartialBoneName_s, "PartialBoneName");
    getAITreeVariable(&mGiantPartBoneUnit_a, "GiantPartBoneUnit");
}

}  // namespace uking::behavior
