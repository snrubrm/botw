#include "Game/Actor/actWeapon.h"
#include "Game/Actor/actNPC.h"
#include <algorithm>
#include <prim/seadScopedLock.h>
#include <random/seadGlobalRandom.h>
#include "Game/Damage/dmgInfoManager.h"
#include "Game/UI/uiPauseMenuDataMgr.h"
#include "Game/UI/uiUtils.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actUnk_71006e45c4.h"
#include "KingSystem/ActorSystem/Profiles/actPlayerOrEnemy.h"
#include "KingSystem/ActorSystem/Profiles/actPlayerBase.h"
#include "KingSystem/ActorSystem/Profiles/actBullet.h"
#include "KingSystem/ActorSystem/LOD/actLodState.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actActorWeapons.h"
#include "KingSystem/ActorSystem/actChemical.h"
#include "KingSystem/ActorSystem/actGlobalParameter.h"
#include "KingSystem/ActorSystem/actInfoCommon.h"
#include "KingSystem/ActorSystem/actInfoData.h"
#include "KingSystem/ActorSystem/actInstParamPack.h"
#include "KingSystem/GameData/gdtCommonFlagsUtils.h"
#include "KingSystem/Map/mapObject.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Physics/RigidBody/physRigidBodyAccessor.h"
#include "KingSystem/Resource/Actor/resResourceGParamList.h"
#include "KingSystem/Resource/Actor/resResourceActorLink.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectGlobal.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectAttack.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectBow.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectMasterSword.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectGuardianMiniWeapon.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectShield.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectWeaponCommon.h"
#include "KingSystem/Utils/Byaml/Byaml.h"
#include "KingSystem/XLink/xlinkActorUtil.h"

// 0x71008ba7d8: declaration only; original source namespace is unknown.
bool isActiveEventDemo000Or001Or002();

// Source ownership is unknown; declaration only.
void weaponBroken(ksys::act::Actor* actor);

// Source ownership is unknown; declaration only.
void dropActorFromPorchCalculateMtx(sead::Matrix34f* matrix, ksys::act::Actor* actor);

// Source ownership is unknown; declarations only.
void callGetDemoHandler(ksys::act::Actor* actor, const sead::SafeString& name);
bool emitActorGetDemoSound(const sead::SafeString& name);

// Source ownership is unknown; declaration only.
void emitItemKirakira_Plus(sead::Vector3f position, bool flag);

namespace uking::act {

void Weapon::m181() {
    weaponBroken(this);
    _fc8 = true;
}

ksys::act::Unk_71025ae620* Weapon::getDropData() {
    return mDropData;
}

ksys::act::Actor::Unk3* Weapon::m135() {
    return &_1008;
}

s32* Weapon::getLife() {
    return &mLife;
}

ksys::act::Unk_71025b08f8* Weapon::m126() {
    return _d98;
}

uking::dmg::DamageManagerBase* Weapon::getDamageMgr() {
    return mDamageMgr;
}

ksys::act::Unk_71006e45c4* Weapon::m128() {
    return _d90;
}

bool Weapon::m176(const sead::Vector3f& target, const sead::Vector3f& pos, bool a3, bool a4,
                  void* a5, bool a6) {
    x_4(target, false, false, a5, false);
    return WeaponBase::m176(target, pos, a3, a4, a5, a6);
}

bool Weapon::m137() {
    return m138();
}

bool Weapon::m138() {
    return hasParentActor_() && _920 == 0xff && !_921;
}

bool Weapon::m142() {
    return ksys::act::isEnemyProfile(&_938);
}

bool Weapon::m204() {
    return isActiveEventDemo000Or001Or002();
}

bool Weapon::m205() {
    return _d90 && _d90->m2();
}

void Weapon::m215() {
    _fb0 = 1;
}

void* Weapon::m221() {
    return _fd0;
}

// NON_MATCHING: the linear-velocity scaling loads and stores are scheduled differently.
void Weapon::updateMtxFromPhysics() {
    if (!_fd0 || !_fd0->isAddedToWorld()) {
        Actor::updateMtxFromPhysics();
        return;
    }

    sead::Vector3f velocity;
    _fd0->getRigidBodyAccessor()->getLinearVelocity(&velocity);
    velocity *= 1.0f / 30.0f;
    sead::Vector3f angular_velocity;
    _fd0->getRigidBodyAccessor()->getAngularVelocity(&angular_velocity);
    angular_velocity *= 1.0f / 30.0f;
    mVelocity = velocity;
    mAngVelocity = angular_velocity;
    mMtx = _fd0->getTransform();
    nullsub_4648();
}

void Weapon::masterSwordReturnToForest() {
    uking::ui::showInfoOverlayWithString(33, sead::SafeString(getName().cstr()));
    xlinkSearchAndEmit(this, "Return", 2, nullptr);
    deleteLater(DeleteReason::_0);
}

// NON_MATCHING: the compiler combines the request-type tests differently.
bool Weapon::m222() {
    if (_af8._0 == 6 || _af8._0 == 7)
        return false;
    auto* actor = sead::DynamicCast<ksys::act::Actor>(getConnectedCalcChild());
    if (!actor)
        return false;
    const auto* actor_link = actor->getParam()->getRes().mActorLink;
    return actor_link && actor_link->hasTag(0x19f6c13a);
}

bool Weapon::m194() {
    if (m188())
        return true;
    if (!isParentPlayer())
        return false;
    auto* parent = getParentActor();
    if (!parent)
        return false;
    auto* as = parent->getASList();
    return as && as->x(63, nullptr, 2, 0, &ksys::as::ASList::Unk2::sub_71011637EC, true);
}

bool Weapon::m227() {
    return (_e52 & 1) != 0;
}

void Weapon::m228(ksys::act::BaseProc* proc) {
    if (_938.hasProcById(proc))
        _f73 = true;
}

void Weapon::m229(ksys::act::BaseProc* proc) {
    updateLifeMaybe(proc);
    if (const auto* life = getLife(); life && *life <= 0)
        _e50 |= 0x200;
}

void Weapon::m249(sead::Matrix34f* matrix, ksys::act::Actor* actor) {
    dropActorFromPorchCalculateMtx(matrix, actor);
}

bool Weapon::m250(ksys::act::Actor* actor) {
    if (!actor)
        return false;
    auto* bullet = sead::DynamicCast<ksys::act::Bullet>(actor);
    return bullet && (bullet->_cf4 & 0x10);
}

bool Weapon::m239() {
    if (!isParentPlayer())
        return false;
    auto* parent = sead::DynamicCast<ksys::act::PlayerBase>(getParentActor());
    return parent && parent->m271() == 1 && parent->getWeapons()->mWeapons[0]._10;
}

void Weapon::invokedEmitBlinkEffect() {
    ksys::act::ActorConstDataAccess accessor(this);
    auto* object = getMapObject();
    if (!object || !object->getForSaleLink())
        emitItemKirakira_Plus(accessor.getPreviousPos2(), true);
}

bool Weapon::m197(sead::SafeString* out) {
    if (!out)
        return false;
    auto* parent = getParentActor();
    if (parent && ksys::act::hasTag(parent, 0xBCD4994C)) {
        auto* resource = getParam()->getRes().mGParamList->getGuardianMiniWeapon();
        if (resource) {
            *out = resource->mBindMyNodeName.ref();
            return !out->isEmpty();
        }
    }
    *out = sead::SafeString::cEmptyString;
    return false;
}

bool Weapon::m218() {
    return _f58;
}

bool Weapon::m225() {
    return _fd8;
}

bool Weapon::m226() {
    if (!isParentPlayer())
        return false;
    auto* player = sead::DynamicCast<ksys::act::PlayerBase>(getParentActor());
    return player && player->m206();
}

bool Weapon::m155() {
    if (!isParentPlayer())
        return false;
    auto* player = sead::DynamicCast<ksys::act::PlayerBase>(getParentActor());
    if (!player || player->m203())
        return false;
    return player->_d11 != 0 || player->m194();
}

bool Weapon::m156() {
    if (!isParentPlayer())
        return false;
    auto* player = sead::DynamicCast<ksys::act::PlayerBase>(getParentActor());
    return player && (player->m199() || player->_cec.isOnBit(4));
}

void Weapon::m206(bool play_sound) {
    callGetDemoHandler(this, getName());
    ui::openPickUpScreen(this);
    if (play_sound)
        emitActorGetDemoSound(getName());
    m182();
    emitDeadUpLifeZeroAndSetRevival();
    unlinkPlacementObj();
    resetMubinBymlIter();
    ksys::act::disableAllAttClients(this);
}

// NON_MATCHING: the invalid-slot result joins the shared return path earlier.
bool Weapon::m153() {
    if (m189())
        return (_e50 & 4) != 0;
    if (!getParentActor())
        return false;
    auto* weapons = getParentActorWeapons();
    if (!weapons || _9f0 < 0 || _9f0 > 5)
        return false;
    return weapons->mWeapons[_9f0]._10;
}

bool Weapon::m216() {
    return isWeaponType4() && isParentPlayer() && !m153();
}

bool Weapon::isParentPlayer() {
    return ksys::act::isPlayerProfile(&_938);
}

bool Weapon::isParentNpc() {
    return ksys::act::isNPCProfile(&_938);
}

ksys::act::ActorWeapons* Weapon::getParentActorWeapons() {
    if (auto* parent = sead::DynamicCast<ksys::act::PlayerOrEnemy>(getParentActor()))
        return parent->getWeapons();
    if (auto* parent = sead::DynamicCast<NPC>(getParentActor()))
        return parent->getWeapons();
    return nullptr;
}

bool Weapon::m183() {
    return (_e50 & 8) != 0;
}

bool Weapon::m184() {
    return _c20._0 == 1;
}

f32 Weapon::m139() {
    if ((isParentPlayer() || m142()) && _4f0 < 1.0f)
        return _4f0;
    return ksys::act::Actor::m139();
}

bool Weapon::m195() {
    auto* parent = getParentActor();
    return parent && ksys::act::hasTag(parent, 0xbcd4994c);
}

bool Weapon::x_0() {
    return getParam()->getRes().mGParamList->getBow()->mIsLongRange.ref() ||
           _f98.flags.isOn(WeaponModifier::AddZoomRapid);
}

bool Weapon::isThrowingBreakWeapon() {
    const auto* param = getParam()->getRes().mGParamList->getWeaponCommon();
    return param && param->mIsThrowingBreakWeapon.ref();
}

// NON_MATCHING: empty-name result branches and load scheduling differ.
bool Weapon::bowHasArrowName() {
    const auto* param = getParam()->getRes().mGParamList->getBow();
    return param && !param->mArrowName.ref().isEmpty();
}

bool Weapon::hasCanPullGiantObjectTag() {
    return getParam()->getRes().mActorLink->hasTag(0x2b533845);
}

// NON_MATCHING: the owned tag-query body is naturally inlined here.
s32 Weapon::getMaxHp() {
    const bool can_pull = hasCanPullGiantObjectTag();
    const s32 life = ksys::act::Actor::getMaxLife();
    if (can_pull)
        return life;
    return (life + (_f98.flags.isOn(WeaponModifier::AddLife) ? _f98.value : 0)) * 100;
}

bool Weapon::m173(s32 index, ksys::act::Actor* actor, const char* name, const char* other_name,
                  bool a5, bool a6) {
    if (!ksys::act::WeaponBase::m173(index, actor, name, other_name, a5, a6))
        return false;
    if (auto* lod = getLodState())
        lod->mFlags26.set(1);
    _f60.reset();
    return true;
}

bool Weapon::m174() {
    if (!ksys::act::WeaponBase::m174())
        return false;
    if (auto* lod = getLodState())
        lod->mFlags26.set(1);
    _f60.reset();
    return true;
}

bool Weapon::m177(const sead::Vector3f& target, void* a2) {
    if (auto* lod = getLodState())
        lod->mFlags26.set(1);
    return ksys::act::WeaponBase::m177(target, a2);
}

bool Weapon::m178(const sead::Vector3f& pos) {
    if (auto* lod = getLodState())
        lod->mFlags26.set(1);
    return ksys::act::WeaponBase::m178(pos);
}

// NON_MATCHING: failed parent lookups use a separate return-false block.
bool Weapon::bowGetArrowName(sead::BufferedSafeString* name) {
    const auto* bow = getParam()->getRes().mGParamList->getBow();
    if (!bow)
        return false;
    if (bow->mArrowName.ref().isEmpty()) {
        auto* parent = sead::DynamicCast<ksys::act::PlayerOrEnemy>(getParentActor());
        return parent && parent->m165(name);
    }
    name->copy(bow->mArrowName.ref());
    return true;
}

bool Weapon::m211() {
    return isBgGroundHit(this, false) || isLandedMaybe(this, false) ||
           sub_71007A4178(this, false);
}

bool Weapon::m212() {
    return isBgGroundHit(this, false);
}

bool Weapon::m213() {
    return getActorFlags2().isOn(ActorFlag2::_200);
}

bool Weapon::m231() const {
    return _cf0 == 0;
}

bool Weapon::m232() const {
    return _cf0 == 1;
}

bool Weapon::m233() const {
    return _cf0 == 2;
}

bool Weapon::isMasterSword() {
    const auto* param = getParam()->getRes().mGParamList->getMasterSword();
    return param && param->mIsMasterSword.ref();
}

bool Weapon::isBoomerang() {
    const auto* param = getParam()->getRes().mGParamList->getWeaponCommon();
    return param && param->mIsBoomerang.ref();
}

bool Weapon::isWeaponType0Or1Or2() const {
    return m231() || m232() || m233();
}

bool Weapon::isWeaponType4() const {
    return _cf0 == 4;
}

bool Weapon::isWeaponType3() const {
    return _cf0 == 3;
}

bool Weapon::isTrueFormMasterSword() {
    if (isMasterSword()) {
        auto* manager = dmg::DamageInfoMgr::instance();
        if (manager && manager->isTrueFormMasterSword())
            return true;
    }
    return false;
}

f32 Weapon::getShieldSurfingFriction() {
    f32 friction = getParam()->getRes().mGParamList->getShield()->mSurfingFriction.ref();
    if (_f98.flags.isOn(WeaponModifier::AddSurfMaster))
        friction *= _f98.value / 1000.0f;
    return friction;
}

// NON_MATCHING: fallback branches and resource loads are merged differently.
s32 Weapon::getAttackPower() {
    s32 power;
    if (isMasterSword()) {
        power = isTrueFormMasterSword()
                    ? getParam()->getRes().mGParamList->getMasterSword()->mTrueFormAttackPower.ref()
                    : -1;
        if (power <= 0) {
            power = getParam()->getRes().mGParamList->getAttack()->mPower.ref();
            power += ksys::gdt::getFlag_MasterSword_Add_Power(false);
        }
    } else {
        power = getParam()->getRes().mGParamList->getAttack()->mPower.ref();
    }
    return power + (_f98.flags.isOn(WeaponModifier::AddAtk) ? _f98.value : 0);
}

s32 Weapon::getShieldGuardPower() {
    const auto* param = getParam()->getRes().mGParamList->getWeaponCommon();
    return param->mGuardPower.ref() +
           (_f98.flags.isOn(WeaponModifier::AddGuard) ? _f98.value : 0);
}

f32 Unk_71002ef75c::sub_71002EF74C() {
    return _8->_2a8;
}

const sead::Vector3f* Weapon::getAttackPosMaybe() const {
    return &_af8._8;
}

bool Weapon::m214() {
    auto* state = _d38;
    if (!state)
        return true;
    if (state->_18 & 1)
        return false;
    const f32 charge = state->_14;
    if (state->_0 && state->_0->m233() && (state->_0->_c20._14 & 8)) {
        f32 threshold = 0.0f;
        if (state->_0->_d38)
            threshold = s32(f32(state->_0->_d38->_8->_2a8)) / 13;
        if (s32(state->_14 / threshold) == 1)
            threshold = state->_14;
        return charge >= threshold;
    }
    return charge >= f32(state->_8->_2c8);
}

void Unk_71002ef75c::sub_71002EF850() {
    _14 -= _8->_2a8;
    if (_14 <= 0) {
        _14 = 0;
        _18 |= 1;
    }
}

void Unk_71002ef75c::sub_71002EF75C() {
    f32 decrease;
    if (_0 && _0->m233() && (_0->_c20._14 & 8)) {
        f32 max_charge = 0;
        if (_0->_d38)
            max_charge = s32(f32(_0->_d38->_8->_2a8)) / 13;
        decrease = s32(_14 / max_charge) == 1 ? _14 : max_charge;
    } else {
        decrease = _8->_2c8;
    }
    _14 -= decrease;
    if (_14 <= 0) {
        _14 = 0;
        _18 |= 1;
    }
}

WeaponModifierInfo::WeaponModifierInfo(const ui::PouchItem& item) {
    fromItem(item);
}

void WeaponModifierInfo::fromItem(const ui::PouchItem& item) {
    if (item.getType() <= ui::PouchItemType::Shield) {
        set(item.getWeaponData().mModifier, item.getWeaponData().mModifierValue);
    } else {
        flags.setDirect(0);
        value = 0;
    }
}

int WeaponModifierInfo::getAddLife() const {
    if (flags.isOff(WeaponModifier::AddLife))
        return 0;
    return getLifeMultiplier() * value;
}

int WeaponModifierInfo::getLifeMultiplier() {
    return 100;
}

void WeaponModifierInfo::loadPorchSwordFlag(int idx) {
    set(ksys::gdt::getFlag_PorchSword_FlagSp(idx), ksys::gdt::getFlag_PorchSword_ValueSp(idx));
}

void WeaponModifierInfo::loadPorchShieldFlag(int idx) {
    set(ksys::gdt::getFlag_PorchShield_FlagSp(idx), ksys::gdt::getFlag_PorchShield_ValueSp(idx));
}

void WeaponModifierInfo::loadPorchBowFlag(int idx) {
    set(ksys::gdt::getFlag_PorchBow_FlagSp(idx), ksys::gdt::getFlag_PorchBow_ValueSp(idx));
}

void WeaponModifierInfo::savePorchSwordFlag(int idx) const {
    ksys::gdt::setFlag_PorchSword_FlagSp(flags.getDirect(), idx);
    ksys::gdt::setFlag_PorchSword_ValueSp(value, idx);
}

void WeaponModifierInfo::savePorchShieldFlag(int idx) const {
    ksys::gdt::setFlag_PorchShield_FlagSp(flags.getDirect(), idx);
    ksys::gdt::setFlag_PorchShield_ValueSp(value, idx);
}

void WeaponModifierInfo::savePorchBowFlag(int idx) const {
    ksys::gdt::setFlag_PorchBow_FlagSp(flags.getDirect(), idx);
    ksys::gdt::setFlag_PorchBow_ValueSp(value, idx);
}

void WeaponModifierInfo::loadEquipStandSwordFlag(int idx) {
    set(ksys::gdt::getFlag_EquipStandSword_FlagSp(idx),
        ksys::gdt::getFlag_EquipStandSword_ValueSp(idx));
}

void WeaponModifierInfo::loadEquipStandShieldFlag(int idx) {
    set(ksys::gdt::getFlag_EquipStandShield_FlagSp(idx),
        ksys::gdt::getFlag_EquipStandShield_ValueSp(idx));
}

void WeaponModifierInfo::loadEquipStandBowFlag(int idx) {
    set(ksys::gdt::getFlag_EquipStandBow_FlagSp(idx),
        ksys::gdt::getFlag_EquipStandBow_ValueSp(idx));
}

void WeaponModifierInfo::saveEquipStandSwordFlag(int idx) const {
    ksys::gdt::setFlag_EquipStandSword_FlagSp(flags.getDirect(), idx);
    ksys::gdt::setFlag_EquipStandSword_ValueSp(value, idx);
}

void WeaponModifierInfo::saveEquipStandShieldFlag(int idx) const {
    ksys::gdt::setFlag_EquipStandShield_FlagSp(flags.getDirect(), idx);
    ksys::gdt::setFlag_EquipStandShield_ValueSp(value, idx);
}

void WeaponModifierInfo::saveEquipStandBowFlag(int idx) const {
    ksys::gdt::setFlag_EquipStandBow_FlagSp(flags.getDirect(), idx);
    ksys::gdt::setFlag_EquipStandBow_ValueSp(value, idx);
}

void WeaponModifierInfo::addModifierParams(ksys::act::InstParamPack& params) const {
    params->add(value, "AddParam");
    params->add(int(flags.getDirect()), "AddSpecialFlag");
}

void WeaponModifierInfo::set(u32 type_, u32 value_) {
    flags.setDirect(type_);
    value = value_;
}

bool WeaponModifierRanges::loadTierBlue(const sead::SafeString& actor) {
    auto* info = ksys::act::InfoData::instance();
    if (!info)
        return false;

    al::ByamlIter iter;
    if (!info->getActorIter(&iter, actor.cstr()))
        return false;

    addAtkMin = ksys::act::getWeaponCommonSharpWeaponAddAtkMin(iter);
    addAtkMax = ksys::act::getWeaponCommonSharpWeaponAddAtkMax(iter);

    addLifeMin = ksys::act::getWeaponCommonSharpWeaponAddLifeMin(iter);
    addLifeMax = ksys::act::getWeaponCommonSharpWeaponAddLifeMax(iter);

    addCrit = ksys::act::getWeaponCommonSharpWeaponAddCrit(iter);

    addGuardMin = ksys::act::getWeaponCommonSharpWeaponAddGuardMin(iter);
    addGuardMax = ksys::act::getWeaponCommonSharpWeaponAddGuardMax(iter);

    return true;
}

bool WeaponModifierRanges::loadTierYellow(const sead::SafeString& actor) {
    auto* info = ksys::act::InfoData::instance();
    if (!info)
        return false;

    al::ByamlIter iter;
    if (!info->getActorIter(&iter, actor.cstr()))
        return false;

    isTierYellow = true;

    addAtkMin = ksys::act::getWeaponCommonPoweredSharpAddAtkMin(iter);
    addAtkMax = ksys::act::getWeaponCommonPoweredSharpAddAtkMax(iter);

    addLifeMin = ksys::act::getWeaponCommonPoweredSharpAddLifeMin(iter);
    addLifeMax = ksys::act::getWeaponCommonPoweredSharpAddLifeMax(iter);

    addGuardMin = ksys::act::getWeaponCommonPoweredSharpWeaponAddGuardMin(iter);
    addGuardMax = ksys::act::getWeaponCommonPoweredSharpWeaponAddGuardMax(iter);

    addThrowMin = ksys::act::getWeaponCommonPoweredSharpAddThrowMin(iter);
    addThrowMax = ksys::act::getWeaponCommonPoweredSharpAddThrowMax(iter);

    addSpreadFire = ksys::act::getWeaponCommonPoweredSharpAddSpreadFire(iter);
    addZoomRapid = ksys::act::getWeaponCommonPoweredSharpAddZoomRapid(iter);

    addRapidFireMin = ksys::act::getWeaponCommonPoweredSharpAddRapidFireMin(iter);
    addRapidFireMax = ksys::act::getWeaponCommonPoweredSharpAddRapidFireMax(iter);

    addSurfMaster = ksys::act::getWeaponCommonPoweredSharpAddSurfMaster(iter);

    return true;
}

WeaponModifier WeaponModifierRanges::getRandomModifier() const {
    u32 max = 1;
    WeaponModifier modifier = WeaponModifier::None;

    if (addAtkMin > 0) {
        modifier = WeaponModifier::AddAtk;
        ++max;
    }

    if (addLifeMin > 0) {
        const u32 x = sead::GlobalRandom::instance()->getU32(max);
        if (x == 0) {
            modifier = WeaponModifier::AddLife;
            ++max;
        }
    }

    if (addCrit && sead::GlobalRandom::instance()->getU32(max) == 0) {
        modifier = WeaponModifier::AddCrit;
        ++max;
    }

    if (addGuardMin > 0 && sead::GlobalRandom::instance()->getU32(max) == 0) {
        modifier = WeaponModifier::AddGuard;
        ++max;
    }

    if ((addThrowMin != 1.0 || addThrowMax != 1.0) &&
        sead::GlobalRandom::instance()->getU32(max) == 0) {
        modifier = WeaponModifier::AddThrow;
        ++max;
    }

    if (addSpreadFire && sead::GlobalRandom::instance()->getU32(max) == 0) {
        modifier = WeaponModifier::AddSpreadFire;
        ++max;
    }

    if (addZoomRapid && sead::GlobalRandom::instance()->getU32(max) == 0) {
        modifier = WeaponModifier::AddZoomRapid;
        ++max;
    }

    if ((addRapidFireMin != 1.0 || addRapidFireMax != 1.0) &&
        sead::GlobalRandom::instance()->getU32(max) == 0) {
        modifier = WeaponModifier::AddRapidFire;
        ++max;
    }

    if (addSurfMaster && sead::GlobalRandom::instance()->getU32(max) == 0) {
        modifier = WeaponModifier::AddSurfMaster;
        ++max;
    }

    return modifier;
}

bool WeaponModifierRanges::isConfigValid() const {
    if (addAtkMin <= 0 && addLifeMin <= 0 && !addCrit && addGuardMin <= 0 && addThrowMin == 1.0 &&
        addThrowMax == 1.0 && !addSpreadFire && !addZoomRapid && addRapidFireMin == 1.0 &&
        addRapidFireMax == 1.0 && !addSurfMaster) {
        return false;
    }

    if (addAtkMin < 0 || (addAtkMin > 0 && addAtkMin > addAtkMax))
        return false;

    if (addLifeMin < 0 || (addLifeMin > 0 && addLifeMin > addLifeMax))
        return false;

    if (addThrowMin < 0.0 || (addThrowMin > 0.0 && addThrowMin > addThrowMax))
        return false;

    if (addRapidFireMin < 0.0 || (addRapidFireMin > 0.0 && addRapidFireMin > addRapidFireMax))
        return false;

    return true;
}

bool WeaponModifierInfo::pickRandomBlueModifierAmiibo(const sead::SafeString& actor) {
    if (!ksys::act::InfoData::instance())
        return false;

    WeaponModifierRanges ranges;
    if (!ranges.loadTierBlue(actor))
        return false;

    return pickRandomModifierAmiibo(ranges);
}

bool WeaponModifierInfo::pickRandomModifierAmiibo(const WeaponModifierRanges& ranges) {
    const auto modifier = ranges.getRandomModifier();
    switch (modifier) {
    case WeaponModifier::None:
        return false;
    case WeaponModifier::AddAtk:
        if (ranges.addAtkMax > 0)
            setModifier(WeaponModifier::AddAtk, ranges.addAtkMax);
        return true;
    case WeaponModifier::AddLife:
        if (ranges.addLifeMax > 0)
            setModifier(WeaponModifier::AddLife, ranges.addLifeMax);
        return true;
    case WeaponModifier::AddThrow:
        if (ranges.addThrowMax > 0.0)
            setModifierFloat(WeaponModifier::AddThrow, ranges.addThrowMax);
        return true;
    case WeaponModifier::AddSpreadFire:
        setModifier(WeaponModifier::AddSpreadFire, 5);
        return true;
    case WeaponModifier::AddRapidFire:
        if (ranges.addRapidFireMin > 0.0)
            setModifierFloat(WeaponModifier::AddRapidFire, ranges.addRapidFireMin);
        return true;
    case WeaponModifier::AddSurfMaster: {
        if (!ksys::act::GlobalParameter::instance())
            return true;
        auto* param = ksys::act::GlobalParameter::instance()->getGlobalParam();
        if (param && param->mShieldSurfMasterFrictionRatio.ref() > 0.0) {
            setModifierFloat(WeaponModifier::AddSurfMaster,
                             param->mShieldSurfMasterFrictionRatio.ref());
        }
        return true;
    }
    case WeaponModifier::AddGuard:
        if (ranges.addGuardMax > 0) {
            /// @bug This is supposed to be WeaponModifier::AddGuard.
            setModifier(WeaponModifier::AddLife, ranges.addGuardMax);
        }
        return true;
    default:
        flags = modifier;
        value = 0;
        return true;
    }
}

bool WeaponModifierInfo::pickRandomYellowModifierAmiibo(const sead::SafeString& actor) {
    if (!ksys::act::InfoData::instance())
        return false;

    WeaponModifierRanges ranges;
    if (!ranges.loadTierYellow(actor))
        return false;

    return pickRandomModifierAmiibo(ranges);
}

// NON_MATCHING: isConfigValid() somehow does not match when inlined (but matches the Wii U version)
bool WeaponModifierInfo::pickRandomBlueModifierTbox(const sead::SafeString& actor) {
    auto* info = ksys::act::InfoData::instance();
    if (!info)
        return false;

    al::ByamlIter iter;
    if (!info->getActorIter(&iter, actor.cstr()))
        return false;

    WeaponModifierRanges ranges;
    if (!ranges.loadTierBlue(actor))
        return false;

    if (!ranges.isConfigValid())
        return false;

    return pickRandomModifier(ranges);
}

bool WeaponModifierInfo::pickRandomModifier(const WeaponModifierRanges& ranges) {
    const auto modifier = ranges.getRandomModifier();
    if (modifier == WeaponModifier::None)
        return false;

    if (ranges.isTierYellow)
        flags.set(WeaponModifier::IsYellow);

    switch (modifier) {
    case WeaponModifier::AddAtk: {
        const auto min = ranges.addAtkMin;
        const auto max = ranges.addAtkMax;
        const auto val = sead::GlobalRandom::instance()->getS32Range(min, max + 1);
        if (val > 0)
            setModifier(WeaponModifier::AddAtk, val);
        return true;
    }
    case WeaponModifier::AddLife: {
        const auto min = ranges.addLifeMin;
        const auto max = ranges.addLifeMax;
        const auto val = sead::GlobalRandom::instance()->getS32Range(min, max + 1);
        if (val > 0)
            setModifier(WeaponModifier::AddLife, val);
        return true;
    }
    case WeaponModifier::AddThrow: {
        const auto val =
            sead::GlobalRandom::instance()->getF32Range(ranges.addThrowMin, ranges.addThrowMax);
        if (val > 0)
            setModifierFloat(WeaponModifier::AddThrow, val);
        return true;
    }
    case WeaponModifier::AddSpreadFire:
        setModifier(WeaponModifier::AddSpreadFire, 5);
        return true;
    case WeaponModifier::AddRapidFire: {
        const auto val = sead::GlobalRandom::instance()->getF32Range(ranges.addRapidFireMin,
                                                                     ranges.addRapidFireMax);
        if (val > 0)
            setModifierFloat(WeaponModifier::AddRapidFire, val);
        return true;
    }
    case WeaponModifier::AddSurfMaster: {
        if (!ksys::act::GlobalParameter::instance())
            return true;
        auto* param = ksys::act::GlobalParameter::instance()->getGlobalParam();
        if (param && param->mShieldSurfMasterFrictionRatio.ref() > 0.0) {
            setModifierFloat(WeaponModifier::AddSurfMaster,
                             param->mShieldSurfMasterFrictionRatio.ref());
        }
        return true;
    }
    case WeaponModifier::AddGuard: {
        const auto min = ranges.addGuardMin;
        const auto max = ranges.addGuardMax;
        const auto val = sead::GlobalRandom::instance()->getS32Range(min, max + 1);
        if (val > 0)
            setModifier(WeaponModifier::AddGuard, val);
        return true;
    }
    default:
        flags = modifier;
        value = 0;
        return true;
    }
}

bool WeaponModifierRanges::loadTierBlue(const ksys::res::GParamList& gparamlist) {
    const auto* param = gparamlist.getWeaponCommon();
    addAtkMin = param->mSharpWeaponAddAtkMin.ref();
    addAtkMax = param->mSharpWeaponAddAtkMax.ref();
    addLifeMin = param->mSharpWeaponAddLifeMin.ref();
    addLifeMax = param->mSharpWeaponAddLifeMax.ref();
    addCrit = param->mSharpWeaponAddCrit.ref();
    addGuardMin = param->mSharpWeaponAddGuardMin.ref();
    addGuardMax = param->mSharpWeaponAddGuardMax.ref();
    return true;
}

// NON_MATCHING: isConfigValid() somehow does not match when inlined (but matches the Wii U version)
bool WeaponModifierInfo::pickRandomBlueModifierActor(const ksys::act::ActorConstDataAccess& acc) {
    WeaponModifierRanges ranges;
    const auto& gparamlist = *acc.getGParamList();
    if (ranges.loadTierBlue(gparamlist)) {
        static_cast<void>(acc.getName());
        if (ranges.isConfigValid())
            return pickRandomModifier(ranges);
    }
    return false;
}

// NON_MATCHING: isConfigValid() somehow does not match when inlined (but matches the Wii U version)
bool WeaponModifierInfo::pickRandomYellowModifierTbox(const sead::SafeString& actor) {
    auto* info = ksys::act::InfoData::instance();
    if (!info)
        return false;

    al::ByamlIter iter;
    if (!info->getActorIter(&iter, actor.cstr()))
        return false;

    WeaponModifierRanges ranges;
    if (!ranges.loadTierYellow(actor))
        return false;

    if (!ranges.isConfigValid())
        return false;

    return pickRandomModifier(ranges);
}

bool WeaponModifierRanges::loadTierYellow(const ksys::res::GParamList& gparamlist) {
    const auto* param = gparamlist.getWeaponCommon();
    isTierYellow = true;
    addAtkMin = param->mPoweredSharpAddAtkMin.ref();
    addAtkMax = param->mPoweredSharpAddAtkMax.ref();
    addLifeMin = param->mPoweredSharpAddLifeMin.ref();
    addLifeMax = param->mPoweredSharpAddLifeMax.ref();
    addGuardMin = param->mPoweredSharpWeaponAddGuardMin.ref();
    addGuardMax = param->mPoweredSharpWeaponAddGuardMax.ref();
    addThrowMin = param->mPoweredSharpAddThrowMin.ref();
    addThrowMax = param->mPoweredSharpAddThrowMax.ref();
    addSpreadFire = param->mPoweredSharpAddSpreadFire.ref();
    addZoomRapid = param->mPoweredSharpAddZoomRapid.ref();
    addRapidFireMin = param->mPoweredSharpAddRapidFireMin.ref();
    addRapidFireMax = param->mPoweredSharpAddRapidFireMax.ref();
    addSurfMaster = param->mPoweredSharpAddSurfMaster.ref();
    return true;
}

// NON_MATCHING: isConfigValid() somehow does not match when inlined (but matches the Wii U version)
bool WeaponModifierInfo::pickRandomYellowModifierActor(const ksys::act::ActorConstDataAccess& acc) {
    WeaponModifierRanges ranges;
    const auto& gparamlist = *acc.getGParamList();
    if (ranges.loadTierYellow(gparamlist)) {
        static_cast<void>(acc.getName());
        if (ranges.isConfigValid())
            return pickRandomModifier(ranges);
    }
    return false;
}

// NON_MATCHING: the two address computations for the BaseProcLink assignment are swapped
bool Weapon::m175(const sead::Vector3f& pos, bool a2, bool a3, void* a4, bool a5) {
    x_4(pos, false, false, a4, false);
    return WeaponBase::m175(pos, a2, a3, a4, a5);
}

bool Weapon::x_6() {
    return hasAttackInfo(this);
}

bool Weapon::sub_71002E9A50() {
    auto* chemical = getChemicalStuff();
    return chemical && chemical->_c0 == 2;
}

void Weapon::sub_71002EDA38(const Unk_71002eda38& arg) {
    auto lock = sead::makeScopedLock(_ab8);
    _af8._0 = arg._0;
    _af8._4 = arg._4;
    _af8._30 = arg._30;
    _af8._34 = arg._34;
    _af8._38 = arg._38;
    _af8._8 = arg._8;
    _af8._14 = arg._14;
    _af8._20 = arg._20;
    _af8._3c = arg._3c;
    _af8._40 = arg._40;
    _b40 = true;
}

void Weapon::sub_71002EDAEC(const Unk_71002edaec& arg) {
    auto lock = sead::makeScopedLock(_be0);
    _c20 = arg;
    _c4c = true;
}

void Weapon::sub_71002EDB3C(const Unk3& value) {
    auto lock = sead::makeScopedLock(_b48);
    _b88 = value;
    _b8c = true;
}

}  // namespace uking::act

namespace ksys::act::acc {

static BaseProc* getProcIfActor(BaseProc* proc) {
    if (proc && sead::IsDerivedFrom<Actor>(proc))
        return proc;
    return nullptr;
}

inline uking::act::Weapon* Weapon::getWeapon() const {
    auto* actor = static_cast<Actor*>(getProcIfActor(mProc));
    return sead::DynamicCast<uking::act::Weapon>(actor);
}

bool Weapon::isShield() const {
    auto* weapon = getWeapon();
    return weapon && weapon->_cf0 == 4;
}

s32 Weapon::getAttackPower() const {
    auto* weapon = getWeapon();
    return weapon ? weapon->getAttackPower() : 0;
}

bool Weapon::isHitEnemy() const {
    auto* actor = static_cast<Actor*>(getProcIfActor(mProc));
    if (!actor || !hasAttackInfo(actor))
        return false;
    const s32 count = getNumAttackInfoMaybe(actor);
    for (s32 i = 0; i < count; ++i) {
        if (ksys::act::isEnemyProfile(&getAttackInfo(actor, i)->_50))
            return true;
    }
    return false;
}

bool Weapon::sub_71002EF980() const {
    auto* weapon = getWeapon();
    if (!weapon)
        return false;
    return weapon->hasParentActor();
}

bool Weapon::sub_71002F1228() const {
    auto* weapon = getWeapon();
    if (!weapon)
        return false;
    return weapon->checkForbidAttentionSignal();
}

}  // namespace ksys::act::acc

// inline-only in the original; name is a guess (same cast as acc::Weapon::getWeapon, on a const accessor).
static inline uking::act::Weapon* getWeaponOfAccessor(const ksys::act::ActorConstDataAccess& accessor) {
    auto* actor = static_cast<ksys::act::Actor*>(ksys::act::acc::getProcIfActor(accessor.getProc()));
    return sead::DynamicCast<uking::act::Weapon>(actor);
}

namespace ksys::act {

bool getWeaponCommonIsPikohan(const ActorConstDataAccess& accessor) {
    auto* actor = static_cast<ksys::act::Actor*>(ksys::act::acc::getProcIfActor(accessor.getProc()));
    if (!actor)
        return false;
    const auto* param = actor->getParam()->getRes().mGParamList->getWeaponCommon();
    return param && param->mIsPikohan.ref();
}

s32 getShieldMirrorLevel(const ActorConstDataAccess& accessor) {
    auto* weapon = getWeaponOfAccessor(accessor);
    if (!weapon)
        return 0;
    const auto* param = weapon->getParam()->getRes().mGParamList->getShield();
    return param ? param->mMirrorLevel.ref() : 0;
}

}  // namespace ksys::act

bool sub_71002EFC98(const ksys::act::ActorConstDataAccess& accessor) {
    auto* actor = static_cast<ksys::act::Actor*>(ksys::act::acc::getProcIfActor(accessor.getProc()));
    if (!actor)
        return false;
    const auto* param = actor->getParam()->getRes().mGParamList->getWeaponCommon();
    return param && param->mIsBlunt.ref();
}

bool sub_71002EFE08(const ksys::act::ActorConstDataAccess& accessor) {
    auto* actor = static_cast<ksys::act::Actor*>(ksys::act::acc::getProcIfActor(accessor.getProc()));
    if (!actor)
        return false;
    const auto* param = actor->getParam()->getRes().mGParamList->getWeaponCommon();
    return param && param->mIsWeakBreaker.ref();
}

bool sub_71002F0154(const ksys::act::ActorConstDataAccess& accessor) {
    auto* weapon = getWeaponOfAccessor(accessor);
    return weapon ? weapon->m153() : false;
}

s32 sub_71002F0258(const ksys::act::ActorConstDataAccess& accessor) {
    auto* weapon = getWeaponOfAccessor(accessor);
    return weapon ? weapon->_cf0 : -1;
}

bool sub_71002F0DE0(const ksys::act::ActorConstDataAccess& accessor) {
    auto* weapon = getWeaponOfAccessor(accessor);
    return weapon ? weapon->_1014 < 5 : false;
}

void sub_71002F1400(const ksys::act::ActorConstDataAccess& accessor, s32 value) {
    if (auto* weapon = getWeaponOfAccessor(accessor))
        weapon->_cec = value;
}

bool sub_71002F1000(const ksys::act::ActorConstDataAccess& accessor) {
    auto* weapon = getWeaponOfAccessor(accessor);
    return weapon ? weapon->m214() : false;
}

bool sub_71002F0EE0(const ksys::act::ActorConstDataAccess& accessor) {
    auto* weapon = getWeaponOfAccessor(accessor);
    return weapon ? weapon->isTrueFormMasterSword() : false;
}

s32 sub_71002F0CB4(const ksys::act::ActorConstDataAccess& accessor) {
    auto* weapon = getWeaponOfAccessor(accessor);
    return weapon ? weapon->getShieldGuardPower() : 0;
}

f32 sub_71002F0490(const ksys::act::ActorConstDataAccess& accessor) {
    f32 result = 1.0f;
    if (auto* weapon = getWeaponOfAccessor(accessor)) {
        const f32 rate = weapon->getParam()->getRes().mGParamList->getBow()->mArrowReloadRate.ref();
        f32 multiplier = 1.0f;
        if (weapon->_f98.flags.isOn(uking::act::WeaponModifier::AddRapidFire))
            multiplier = weapon->_f98.value / 1000.0f;
        result = rate * (1.0f / multiplier);
    }
    return result;
}

// NON_MATCHING: the original selects `weapon + 0xf98` / null directly on the RTTI result (one csel), as in
// acc::WeaponBase::getBindInfo; ours keeps the null test of the cast result
uking::act::WeaponModifierInfo* sub_71002F05D8(const ksys::act::ActorConstDataAccess& accessor) {
    auto* weapon = getWeaponOfAccessor(accessor);
    return weapon ? &weapon->_f98 : nullptr;
}

bool sub_71002EFEC0(const ksys::act::ActorConstDataAccess& accessor) {
    auto* weapon = getWeaponOfAccessor(accessor);
    if (!weapon || !weapon->isMasterSword())
        return false;
    ksys::act::ActorConstDataAccess parent;
    ksys::act::acquireActor(&weapon->getParentLink(), &parent);
    return parent.getLife() >= parent.getMaxLife();
}

f32 sub_71002F000C(const ksys::act::ActorConstDataAccess& accessor) {
    f32 result = 0.0f;
    if (auto* weapon = getWeaponOfAccessor(accessor)) {
        if (weapon->isMasterSword()) {
            ksys::act::ActorConstDataAccess parent;
            ksys::act::acquireActor(&weapon->getParentLink(), &parent);
            result = std::max(f32(parent.getLife()), 4.0f);
        }
    }
    return result;
}

f32 sub_71002F034C(const ksys::act::ActorConstDataAccess& accessor) {
    f32 result = 1.0f;
    if (auto* weapon = getWeaponOfAccessor(accessor)) {
        const f32 rate = weapon->getParam()->getRes().mGParamList->getBow()->mArrowChargeRate.ref();
        f32 multiplier = 1.0f;
        if (weapon->_f98.flags.isOn(uking::act::WeaponModifier::AddRapidFire))
            multiplier = weapon->_f98.value / 1000.0f;
        result = rate * multiplier;
    }
    return result;
}

bool sub_71002F0924(const ksys::act::ActorConstDataAccess& accessor) {
    auto* weapon = getWeaponOfAccessor(accessor);
    if (!weapon)
        return false;
    return weapon->get920() != 0xff || weapon->get921();
}

bool actorCheckIsGuard(ksys::act::Actor* actor) {
    if (hasAttackInfo(actor))
        return getAttackInfo(actor, 0)->_18 & 1;
    return false;
}

bool actorCheckIsGuardJust(ksys::act::Actor* actor) {
    if (hasAttackInfo(actor))
        return getAttackInfo(actor, 0)->_18 & 2;
    return false;
}

namespace uking::act {

bool Weapon::sub_71002E4374() {
    if (_e50 & 0x80)
        return true;
    return isWeaponType3() && getConnectedCalcChild();
}

}  // namespace uking::act
