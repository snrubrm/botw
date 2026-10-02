#include "Game/AI/Action/actionDynamicAttackPowerExplode.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectAttack.h"
#include "KingSystem/Resource/Actor/resResourceGParamList.h"
#include "KingSystem/ActorSystem/actAttackSensor.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

DynamicAttackPowerExplode::DynamicAttackPowerExplode(const InitArg& arg)
    : AttackPowerExplode(arg) {}

DynamicAttackPowerExplode::~DynamicAttackPowerExplode() = default;

bool DynamicAttackPowerExplode::init_(sead::Heap* heap) {
    return AttackPowerExplode::init_(heap);
}

void DynamicAttackPowerExplode::enter_(ksys::act::ai::InlineParamPack* params) {
    AttackPowerExplode::enter_(params);
}

void DynamicAttackPowerExplode::leave_() {
    AttackPowerExplode::leave_();
}

void DynamicAttackPowerExplode::loadParams_() {
    AttackPowerExplode::loadParams_();
    getStaticParam(&mAttackPower_s, "AttackPower");
    getStaticParam(&mMinDamage_s, "MinDamage");
    getStaticParam(&mPlayerDamage_s, "PlayerDamage");
}

void DynamicAttackPowerExplode::calc_() {
    AttackPowerExplode::calc_();
}

int DynamicAttackPowerExplode::m35() {
    return *mAttackPower_s;
}

int DynamicAttackPowerExplode::m36() {
    return *mMinDamage_s;
}

int DynamicAttackPowerExplode::m37() {
    return *mPlayerDamage_s;
}

void DynamicAttackPowerExplode::m34(ksys::act::AttackSensor* sensor) {
    sensor->activateAttackSensor(
        0x10, sub_710012B058(), m35(),
        mActor->getParam()->getRes().mGParamList->getAttack()->mImpulse.ref(), 0.0f,
        mActor->getParam()->getRes().mGParamList->getAttack()->mGuardBreakPower.ref(), 0x1e, -1,
        false, m36(), m37());
}

}  // namespace uking::action
