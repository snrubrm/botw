#include "Game/AI/Behavior/behaviorGiantGuardWeakPoint.h"
#include "Game/AI/aiUnk_7100724C64.h"
#include "Game/AI/aiUnk_71025be918.h"

namespace uking::behavior {

GiantGuardWeakPoint::GiantGuardWeakPoint(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

void GiantGuardWeakPoint::m8() {
    auto* actor = mActor;
    const f32 delay = *mDelayTime_s;
    _128 = ksys::Timer(delay, delay);
    _134 = sub_71007271D4(actor);
    _135 = _134 && sub_7100726F20(actor);
}

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

// NON_MATCHING: the original tests the decremented count with b.ne on the subs flags (cbnz here)
GiantGuardWeakPoint::~GiantGuardWeakPoint() {
    if (_138) {
        auto* unit = sead::DynamicCast<Unk_71025be918>(*_138);
        if (unit && unit->_98 > 0 && --unit->_98 == 0) {
            *_138 = nullptr;
            delete unit;
        }
        _138 = nullptr;
    }
}

}  // namespace uking::behavior
