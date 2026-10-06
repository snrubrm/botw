#include "Game/Damage/dmgDamageManager.h"
#include "Game/Actor/actWeapon.h"
#include "Game/AI/aiUnk_7100736460.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actImpulseBaseProcLink.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"

namespace uking::dmg {

void DamageManager::preDelete1() {
    if (mStruct20_a) {
        delete mStruct20_a;
        mStruct20_a = nullptr;
    }
    if (mStruct20_b) {
        delete mStruct20_b;
        mStruct20_b = nullptr;
    }
}

f32 DamageManager::sub_71006D8DE8() {
    auto* link = m37();
    if (link->hasProc()) {
        ksys::act::ActorConstDataAccess accessor;
        ksys::act::acquireActor(link, &accessor);
        if (ksys::act::getWeaponCommonIsPikohan(accessor) ||
            dlc::isOneHitObliteratorActorAccessor(accessor, true))
            return 2.0f;
    }
    return 1.0f;
}

s32 DamageManager::sub_71006D8534() const {
    return _220 ? _220->mHits.size() : 0;
}

ksys::act::ActorAtk::Unk_710079e64c::Unk1* DamageManager::getAttackInfo_() {
    s32 index;
    switch (getDamageType()) {
    case 2:
        index = _6c;
        if (index < 0)
            return nullptr;
        break;
    case 6:
        if (!_216.isOn(0x100))
            return nullptr;
        index = _88;
        if (index < 0)
            return nullptr;
        break;
    default:
        return nullptr;
    }
    return ::sub_71007A255C(mActor, index);
}

s32 DamageManager::getNumCallbacks() {
    return 7;
}

bool DamageManager::checkDamageFlags(s32 bit) {
    return (1 << bit) & _8c;
}

bool DamageManager::m42() {
    return checkDamageFlags(14);
}

bool DamageManager::isSlowTime() {
    if (DamageManagerBase::isSlowTime())
        return true;
    auto* info = getAttackInfo_();
    return info && info->sub_71007A1F78(0x4000000);
}

bool DamageManager::m40(s32* out) {
    *out = -1;
    if (auto* info = getAttackInfo_()) {
        *out = info->_bc;
        return true;
    }
    return false;
}

// NON_MATCHING: the original sets up its stack frame at the top (no shrink wrapping around the call)
// NON_MATCHING: the original ends the failure paths with a tail call of getDummyBaseProcLink() (the call is not a tail
// call in ours: its result joins the other returns)
ksys::act::BaseProcLink* DamageManager::getAttacker() {
    switch (getDamageType()) {
    case 2:
    case 10:
        if (_6c < 0)
            return &ksys::act::getDummyBaseProcLink();
        if (auto* info = ::sub_71007A255C(mActor, _6c))
            return &info->_d8;
        return &ksys::act::getDummyBaseProcLink();
    case 3:
        if (!::hasAttackInfo(mActor))
            return &ksys::act::getDummyBaseProcLink();
        if (auto* info = ::getAttackInfo(mActor, 0))
            return &info->_50;
        return &ksys::act::getDummyBaseProcLink();
    case 4:
    case 11:
        if (auto* link = mActor->getImpulseBaseProcLink())
            return &link->mLink;
        return &ksys::act::getDummyBaseProcLink();
    case 6:
        if (!_216.isOn(0x100) || _88 < 0)
            return &ksys::act::getDummyBaseProcLink();
        if (auto* info = ::sub_71007A255C(mActor, _88))
            return &info->_d8;
        return &ksys::act::getDummyBaseProcLink();
    default:
        return &ksys::act::getDummyBaseProcLink();
    }
}

// NON_MATCHING: same tail call difference as getAttacker
ksys::act::BaseProcLink* DamageManager::m37() {
    switch (getDamageType()) {
    case 2:
    case 10:
        if (_6c < 0)
            return &ksys::act::getDummyBaseProcLink();
        if (auto* info = ::sub_71007A255C(mActor, _6c))
            return &info->_e8;
        return &ksys::act::getDummyBaseProcLink();
    case 3:
        if (!::hasAttackInfo(mActor))
            return &ksys::act::getDummyBaseProcLink();
        if (auto* info = ::getAttackInfo(mActor, 0))
            return &info->_50;
        return &ksys::act::getDummyBaseProcLink();
    case 4:
    case 11:
        if (auto* link = mActor->getImpulseBaseProcLink())
            return &link->mLink;
        return &ksys::act::getDummyBaseProcLink();
    case 6:
        if (!_216.isOn(0x100) || _88 < 0)
            return &ksys::act::getDummyBaseProcLink();
        if (auto* info = ::sub_71007A255C(mActor, _88))
            return &info->_e8;
        return &ksys::act::getDummyBaseProcLink();
    default:
        return &ksys::act::getDummyBaseProcLink();
    }
}

// NON_MATCHING: the original duplicates the `info ? &info->_20 : nullptr` tail in both arms of the damage kind switch
ksys::phys::MaterialMask* DamageManager::m33() {
    auto* info = getAttackInfo_();
    return info ? &info->_20 : nullptr;
}

// NON_MATCHING: same tail duplication as m33
ksys::phys::MaterialMask* DamageManager::tgSensorMaterialOnHitMaybe() {
    auto* info = getAttackInfo_();
    return info ? &info->_38 : nullptr;
}

bool DamageManager::m29(sead::Vector3f* out) {
    if (getDamageType() == 7 && _216.isOn(0x40)) {
        *out = _cc;
        out->normalize();
        return true;
    }
    return DamageManagerBase::m29(out);
}

bool DamageManager::m30(sead::Vector3f* out) {
    if (getDamageType() == 7 && _216.isOn(0x40)) {
        *out = _cc;
        out->normalize();
        return true;
    }
    return DamageManagerBase::m30(out);
}

bool DamageManager::m41() {
    if (auto* info = getAttackInfo_())
        return info->_fc & 1;
    return false;
}

s32 DamageManager::m49(s32 damageTypeMaybe) {
    if (_8c & 0x10)
        return 1;
    return DamageManagerBase::m49(damageTypeMaybe);
}

bool DamageManager::sub_71006D82D4() const {
    if (!_219)
        return false;
    return _220 && _220->mHits.size() > 0;
}

bool DamageManager::sub_71006D83B8(s32 bit) const {
    return _220->mHits.back()._18 & (1 << bit);
}

s32 DamageManager::sub_71006D8304() const {
    return _220->mHits.back()._0;
}

s32 DamageManager::sub_71006D8340() const {
    return _220->mHits.back()._14;
}

s32 DamageManager::sub_71006D837C() const {
    return _220->mHits.back()._10;
}

}  // namespace uking::dmg
