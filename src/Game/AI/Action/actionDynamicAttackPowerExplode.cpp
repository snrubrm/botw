#include "Game/AI/Action/actionDynamicAttackPowerExplode.h"

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

}  // namespace uking::action
