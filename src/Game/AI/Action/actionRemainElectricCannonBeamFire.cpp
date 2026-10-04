#include "Game/AI/Action/actionRemainElectricCannonBeamFire.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"

namespace uking::action {

RemainElectricCannonBeamFire::RemainElectricCannonBeamFire(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

RemainElectricCannonBeamFire::~RemainElectricCannonBeamFire() = default;

bool RemainElectricCannonBeamFire::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void RemainElectricCannonBeamFire::enter_(ksys::act::ai::InlineParamPack* params) {
    _48 = 5.0f;
    const sead::Vector3f pos = *mTargetPos_d;
    sub_710022AF50(pos, false);
    _58 = 0;
    sub_71007A44E4(mActor, true);
}

void RemainElectricCannonBeamFire::leave_() {
    if (_50 && _50->isAddedToWorld())
        _50->removeFromWorld();
}

void RemainElectricCannonBeamFire::loadParams_() {
    getStaticParam(&mAtkDamage_s, "AtkDamage");
    getStaticParam(&mMinDamage_s, "MinDamage");
    getDynamicParam(&mIsProtected_d, "IsProtected");
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getDynamicParam(&mSafePos_d, "SafePos");
}

void RemainElectricCannonBeamFire::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
