#include "Game/AI/Action/actionActivateAttackSensor.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/ActorSystem/actAttackSensor.h"

namespace uking::action {

ActivateAttackSensor::ActivateAttackSensor(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ActivateAttackSensor::~ActivateAttackSensor() = default;

bool ActivateAttackSensor::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

// NON_MATCHING: identical instructions; only the register naming of the pointer temporaries (x8/x9) and the position of the
// `ldr w2` (AtAttr) differ
void ActivateAttackSensor::enter_(ksys::act::ai::InlineParamPack* params) {
    _98 = ksys::Timer(*mFramesActive_s, *mFramesActive_s);
    _a4 = false;
    if (*mIsChangeable_s)
        mFlags.set(Flag::Changeable);
    auto* sensor = getActorAttackSensor(mActor);
    sensor->activateAttackSensor(*mAtType_s, *mAtAttr_s,
                                 *(*mUseMapUnitParamForDamage_s ? mAttackPower_m : mAtDamage_s),
                                 *mAtPower_s,
                                 f32(*mAtPowerReduce_s), *mAtImpact_s, *mAtShieldBreakPower_s,
                                 *mAtDirType_s, false, 1, -1);
    sub_71007A2C30(mActor, mAtkSensorName_s, nullptr);
    sub_71007A302C(mActor, mAtkSensorName_s, nullptr);
}

void ActivateAttackSensor::leave_() {
    sub_71007A2D7C(mActor, mAtkSensorName_s);
    sub_71007A3270(mActor, mAtkSensorName_s, nullptr);
}

void ActivateAttackSensor::loadParams_() {
    getStaticParam(&mAtDamage_s, "AtDamage");
    getStaticParam(&mAtPower_s, "AtPower");
    getStaticParam(&mAtPowerReduce_s, "AtPowerReduce");
    getStaticParam(&mAtImpact_s, "AtImpact");
    getStaticParam(&mAtShieldBreakPower_s, "AtShieldBreakPower");
    getStaticParam(&mAtType_s, "AtType");
    getStaticParam(&mAtAttr_s, "AtAttr");
    getStaticParam(&mAtDirType_s, "AtDirType");
    getStaticParam(&mFramesActive_s, "FramesActive");
    getStaticParam(&mIsSuccessFinishCounterEnd_s, "IsSuccessFinishCounterEnd");
    getStaticParam(&mIsChangeable_s, "IsChangeable");
    getStaticParam(&mUseMapUnitParamForDamage_s, "UseMapUnitParamForDamage");
    getStaticParam(&mAtkSensorName_s, "AtkSensorName");
    getMapUnitParam(&mAttackPower_m, "AttackPower");
}

void ActivateAttackSensor::calc_() {
    if (_a4)
        return;
    _98.update();
    if (_98.value <= sead::Mathf::epsilon()) {
        sub_71007A2D7C(mActor, mAtkSensorName_s);
        sub_71007A3270(mActor, mAtkSensorName_s, nullptr);
        _a4 = true;
        if (*mIsSuccessFinishCounterEnd_s)
            setFinished();
    }
}

}  // namespace uking::action
