#include "Game/Damage/dmgDamageMgrPlayer.h"

namespace uking::dmg {

bool DamageMgrPlayer::checkDerivedRuntimeTypeInfoStatic(
    const sead::RuntimeTypeInfo::Interface* typeInfo) {
    return typeInfo == DamageMgrPlayer::getRuntimeTypeInfoStatic() ||
           typeInfo == DamageManager::getRuntimeTypeInfoStatic() ||
           typeInfo == DamageManagerBase::getRuntimeTypeInfoStatic() ||
           typeInfo == DamageManagerBase_UnknownBase1::getRuntimeTypeInfoStatic();
}

bool DamageMgrPlayer::checkDerivedRuntimeTypeInfo(
    const sead::RuntimeTypeInfo::Interface* typeInfo) const {
    return checkDerivedRuntimeTypeInfoStatic(typeInfo);
}

const sead::RuntimeTypeInfo::Interface* DamageMgrPlayer::getRuntimeTypeInfo() const {
    return getRuntimeTypeInfoStatic();
}

void DamageMgrPlayer::resetDamage() {
    _22c = 0;
    DamageManager::resetDamage();
}

s32 DamageMgrPlayer::m52() {
    return 12;
}

void DamageMgrPlayer::m55() {
    if (_231)
        return;
    DamageManager::m55();
}

}  // namespace uking::dmg
