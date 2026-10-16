#include "Game/Actor/actCameraUtil.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"
#include <algorithm>
#include <gsys/gsysModel.h>
#include <gsys/gsysModelUnit.h>
#include <basis/seadNew.h>
#include "Game/Actor/aiUnk_71007377D4.h"
#include "Game/Actor/aiUnk_710072BA90.h"
#include "Game/Actor/Damage/dmgDamageManager.h"
#include "Game/Actor/Damage/dmgDamageMgrPlayer.h"
#include "Game/Actor/Damage/dmgInfoManager.h"
#include "Game/Actor/aiUnk_7100FFDFDC.h"
#include "Game/gameRoot4.h"
#include "KingSystem/ActorSystem/aiRootAi.h"
#include "Game/Actor/aiUnk_7100736460.h"
#include "Game/Actor/actHorseRideInfo.h"
#include "Game/Actor/actMotorcycle.h"
#include "Game/Actor/actRideable.h"
#include "Game/Actor/actWeapon.h"
#include "Game/Actor/Damage/dmgDamageManagerBase.h"
#include "Game/E3Mgr.h"
#include "Game/Actor/actArmorBase.h"
#include "Game/gameResidentActorMgr.h"
#include "Game/gameSceneSubsys14.h"
#include "Game/gameUnk_710246d058.h"
#include "Game/gameMaskController.h"
#include "Game/UI/uiPauseMenuDataMgr.h"
#include "KingSystem/Map/mapObject.h"
#include "Game/UI/uiUtils.h"
#include "KingSystem/Graphics/gfxUnk_710260af28.h"
#include "Game/gameUnk_71024739d0.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/Attention/actAttentionSingleton.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/Sound/sndBgmMgr.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/ActorSystem/actChemical.h"
#include "KingSystem/Ecosystem/ecoSystem.h"
#include "KingSystem/Physics/RigidBody/physRigidBodySphere.h"
#include "KingSystem/Physics/RigidBody/physRigidBodyCylinder.h"
#include "KingSystem/Physics/RigidBody/physRigidBodySet.h"
#include "KingSystem/Physics/System/physInstanceSet.h"
#include "Game/Actor/Player/actPlayerInfo.h"
#include "KingSystem/Resource/Actor/resResourceGParamList.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectPlayer.h"
#include "KingSystem/Event/evtEventSystem.h"
#include "KingSystem/GameData/gdtCommonFlagsUtils.h"
#include "KingSystem/GameData/gdtSpecialFlags.h"
#include "KingSystem/XLink/xlinkActorUtil.h"
#include "KingSystem/ActorSystem/actActorHeapUtil.h"
#include "KingSystem/System/StageInfo.h"
#include "Game/gameHeroSoul.h"
#include "Game/Actor/aiUnk_7101e7c5d0.h"
#include "Game/Actor/aiUnk_7101E7C2B4.h"
#include "Game/Actor/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/actActorWeapons.h"
#include "KingSystem/Sound/sndUnk_7102502138.h"
#include "KingSystem/ActorSystem/actActorWeapons.h"
#include "KingSystem/Sound/sndUnk_7102502138.h"
#include "Game/gameRuneMgr.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/Physics/System/physShapeCastWithInfo.h"
#include "KingSystem/Physics/System/physQueryContactPointInfo.h"
#include "KingSystem/Physics/System/physContactMgr.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"

void sub_7100D2D424(uking::act::DamageManagerBase* manager);
bool sub_71002EFEC0(const ksys::act::ActorLinkConstDataAccess& accessor);
f32 sub_71002F000C(const ksys::act::ActorLinkConstDataAccess& accessor);
f32 sub_71002F034C(const ksys::act::ActorLinkConstDataAccess& accessor);
s32 sub_7100A95214();
bool sub_710084BD40(ksys::act::Actor* actor);
ksys::act::ActorAtk::Unk_710079e64c::Unk1* sub_710084BE2C(ksys::act::Actor* actor);

namespace uking::ui {
bool sub_7100A991C0();
}

// 0x71008739a0 (in Player's TU): bit 1 of the attack info flags.
bool playerIsGuardJust(ksys::act::Actor* actor) {
    auto* info = getAttackInfo0(actor);
    return (info->_18 >> 1) & 1;
}

namespace ksys::act {

// Placeholder name: Urbosa's Fury strike. Counts down the remaining uses (_1ccc); when they run out, starts the
// recharge (_1e0c / _1e10 = ElectricSupportReuseTime * 30, _1e14 = -1) and resets the count to
// SupportElectricNum. Emits Kago_Lightning and sends message 0x8000028 to the Gerudo HeroSoul actor.
void Player::sub_71008739BC() {
    if (--_1ccc <= 0) {
        const f32 reuse_time =
            getParam()->getRes().mGParamList->getPlayer()->mElectricSupportReuseTime.ref() * 30.0f;
        _1e14 = -1.0f;
        _1e0c = reuse_time;
        _1e10 = reuse_time;
        _1ccc = getParam()->getRes().mGParamList->getPlayer()->mSupportElectricNum.ref();
    }
    eft::searchAndEmitELink(this, "Kago_Lightning");
    eft::searchAndEmitSLink(this, "Kago_Lightning", false);
    ActorLinkConstDataAccess accessor;
    acquireActor(&mResidentActors[3], &accessor);
    sendMessage(*accessor.getMessageTransceiverId(), MessageType(0x8000028), nullptr, true);
}

}  // namespace ksys::act

// Source namespace unknown (0x710084ca64); declaration only.
bool isPlayingBeastGanonDeadEventFlow();

bool sub_71002C802C(const ksys::act::ActorLinkConstDataAccess& accessor);

// 0x7100e9cf30 (declared only).
void sub_7100E9CF30(void* obj);

// Defined in actPlayerBase.cpp (0x710084beec).
bool j_eventMgrHasActiveEventMaybe(ksys::act::Actor* actor);

namespace ksys::act {

s32 Player::m378() {
    return sub_7100A95214();
}

bool Player::x_49() {
    if (uking::ui::sub_7100A991C0())
        return false;
    if (_17d0->isHold((1 << sead::Controller::cPadIdx_Up) |
                     (1 << sead::Controller::cPadIdx_Left) |
                     (1 << sead::Controller::cPadIdx_Right)))
        return false;
    return _17d0->controllerCheckPressedMaybe(28);
}

bool Player::m157(sead::Heap* heap) {
    auto* manager = new (heap, 8) uking::act::DamageMgrPlayer(this);
    mDamageMgr = manager;
    if (!manager)
        return false;
    const s32 num_callbacks = manager->getNumCallbacks();
    if (num_callbacks != 0) {
        manager->mCallbacks.tryAllocBuffer(num_callbacks, heap);
        manager->mCallbacks.fill(nullptr);
        if (!manager->mCallbacks.getBufferPtr())
            return false;
    }
    if (!manager->allocStruct20(heap))
        return false;
    return manager->initCallbacks(heap);
}

void Player::m158() {
    if (auto* manager = mDamageMgr) {
        sub_7100D2D424(manager);
        manager->preDelete1();
        manager->preDelete2();
        delete mDamageMgr;
        mDamageMgr = nullptr;
    }
}

void Player::x_6(s32 slot, const char* name, bool flag) {
    auto* mgr = uking::ResidentActorMgr::instance();
    if (!mgr)
        return;
    auto* armor = sead::DynamicCast<uking::act::ArmorBase>(mgr->getActorByName(name));
    if (!armor)
        return;
    _23e0.x_31(slot, armor, flag);
    sead::Vector3f pos;
    mMtx.getTranslation(pos);
    armor->mMtx.setTranslation(pos);
    armor->setMtx(armor->mMtx, true, true);
    armor->nullsub_4648();
}

BaseProc* Player::construct(const CreateArg& arg, sead::Heap* heap) {
    return new (heap, std::nothrow) Player(arg);
}

// NON_MATCHING: members are not declared yet
Player::~Player() = default;

Player::PreDeletePrepareResult Player::prepareForPreDelete_() {
    sub_71011DA868(&_2d68);
    sub_71011DA868(&_2e10);
    Actor::prepareForPreDelete_();
    _23e0.sub_7100E2D70C();
    return PreDeletePrepareResult::Done;
}

void Player::updateChampionAbilitiesAndMasterSwordRecoverFlags() {
    if (isPlayingBeastGanonDeadEventFlow())
        return;
    gdt::setFlag_WaterSupportReuseTimeInCastle(_1e18);
    gdt::setFlag_WindSupportReuseTimeInCastle(_1df4);
    gdt::setFlag_FireSupportReuseTimeInCastle(_1e00);
    gdt::setFlag_ElectricSupportReuseTimeInCastle(_1e0c);
    gdt::setFlag_WindSupportUseNum(_1cc8);
    gdt::setFlag_ElectricSupportUseNum(_1ccc);
    gdt::setFlag_FireSupportUseNum(_1cd0);
    gdt::setFlag_MasterSwordRecoverTime(_1e24);
}

// The names of the weapons held in the right hand / left hand / bow slots (the default ones without a weapon).
void Player::m379(sead::BufferedSafeString* out) {
    if (auto* weapon = getWeaponActor(playerWeapons_return0()))
        out->copy(weapon->getName());
    else
        out->copy("Weapon_Default_Right");
}

void Player::m380(sead::BufferedSafeString* out) {
    if (auto* weapon = getWeaponActor(playerWeapons_return1()))
        out->copy(weapon->getName());
    else
        out->copy("Weapon_Default_Left");
}

void Player::m381(sead::BufferedSafeString* out) {
    if (auto* weapon = getWeaponActor(playerWeapons_return2()))
        out->copy(weapon->getName());
    else
        out->copy("Weapon_Default_Bow");
}

bool Player::sub_710087F168(const sead::Vector3f& start, const sead::Vector3f& end,
                            phys::WallCode wall, sead::Vector3f* hit_pos,
                            sead::Vector3f* hit_normal) {
    uking::Unk_71024739d0 ray(phys::GroundHit::HitAll);
    ray.sub_710090D73C();
    ray.setStart(start);
    ray.setEnd(end);
    ray.worldRayCast();
    if (!ray.hasHit())
        return false;

    const auto& mask = ray.mQuery.getMaterialMask();
    if (wall == phys::WallCode::NoClimb) {
        if (int(mask.getWallCode()) == phys::WallCode::NoClimb ||
            int(mask.getWallCode()) == phys::WallCode::NoDashUpAndNoClimb) {
            return false;
        }
    } else if (wall == phys::WallCode::NoDashUpAndNoClimb) {
        if (int(mask.getWallCode()) == phys::WallCode::NoDashUpAndNoClimb)
            return false;
    } else if (int(mask.getWallCode()) != int(wall)) {
        return false;
    }

    if (hit_pos)
        ray.getHitPosition(hit_pos);
    if (hit_normal)
        ray.getHitNormal(hit_normal);
    return true;
}

bool Player::m269() {
    return sub_7100888294();
}

bool Player::m243() {
    return playerIsReloadingBow(this) || playerIsChargingBow(this);
}

bool Player::sub_710086CA68() {
    if (uking::E3Mgr::instance() && uking::E3Mgr::instance()->isRidDemo() &&
        uking::E3Mgr::instance()->isRidDemoAnd28IsOne_())
        return true;
    return gdt::getFlag_IsGet_PlayerStole2(false);
}

// Placeholder name; static (no `this`), the second half of 0x710086c928 inlines the same code.
bool Player::sub_710086C9E0() {
    auto* attention = Attention::instance();
    ActorLinkConstDataAccess accessor;
    bool result = false;
    if (!attention->sub_7100D742E8(1)) {
        if (attention->x_0(1, 0, &accessor) && accessor.getEnemyRank() != 0)
            result = true;
        else
            result = false;
    }
    return result;
}

void Player::sub_710086C84C(s32 a, const BaseProcLink* link, bool b, bool c) {
    m267(a, sead::DynamicCast<Actor>(link->getProc(nullptr, nullptr)), b, c);
}

// Placeholder name; static (no `this`).
// NON_MATCHING: the early `return true` shares the result register with the inlined sub_710086C9E0 (w19 instead of w0)
bool Player::sub_710086C928() {
    if (auto* mgr = uking::act::DamageInfoMgr::instance()) {
        if (snd::sub_7100FFED80() || mgr->_11eb[3] > 0)
            return true;
    }
    return sub_710086C9E0();
}

void Player::updateMtxFromPhysics() {
    if (!m359())
        Actor::updateMtxFromPhysics();
}

bool Player::isDarukProtectionEnabled() {
    return canUseDarukProtection() && _17d0->playerCheckController(13) && _cec.isOnBit(28);
}

uking::act::Weapon* Player::m273() {
    const int idx = playerWeapons_return0();
    return sead::DynamicCast<uking::act::Weapon>(getWeapons()->getEquippedWeapon(idx));
}

uking::act::Weapon* Player::m274() {
    const int idx = playerWeapons_return1();
    return sead::DynamicCast<uking::act::Weapon>(getWeapons()->getEquippedWeapon(idx));
}

uking::act::Weapon* Player::m275() {
    const int idx = playerWeapons_return2();
    return sead::DynamicCast<uking::act::Weapon>(getWeapons()->getEquippedWeapon(idx));
}

Actor* Player::m276(int idx) {
    return sead::DynamicCast<Actor>(_23e0.getPartsLink(idx).getProc(nullptr, nullptr));
}

void Player::m277(ActorLinkConstDataAccess* accessor, int idx) {
    acquireActor(&_23e0.getPartsLink(idx), accessor);
}

Actor* Player::m382() {
    return sead::DynamicCast<Actor>(
        uking::act::PlayerInfo::instance()->getHorseLink().getProc(nullptr, nullptr));
}

f32 Player::getAtkMultiplier() {
    f32 multiplier = _208c;
    if (isMasterSwordEquipped_())
        multiplier *= _2090;
    return multiplier;
}

const sead::Vector3f* Player::getPosCopyMagnesis() {
    auto lock = sead::makeScopedLock(_2208.mLock);
    return &_2208.mPos;
}

const sead::Vector3f* Player::m244() {
    auto lock = sead::makeScopedLock(_2258.mLock);
    if (runeMgrCheckCanUseMagnesis() && !m179())
        return &_22c0;
    return &_2258.mPos;
}

const sead::Vector3f* Player::m245() {
    auto lock = sead::makeScopedLock(_21b8.mLock);
    if (runeMgrCheckCanUseMagnesis() && !m179())
        return &_22b4;
    return &_21b8.mPos;
}

bool Player::isRevivalFairyActive(ActorLinkConstDataAccess* accessor) {
    if (acquireActor(&mResidentActors[2], accessor) && accessor->isStateCalc())
        return true;
    return false;
}

bool Player::isZoraHeroActive(ActorLinkConstDataAccess* accessor) {
    if (acquireActor(&mResidentActors[6], accessor) && accessor->isStateCalc())
        return true;
    return false;
}

f32 Player::getNoDeathDamage() {
    const auto* param = getParam()->getRes().mGParamList->getPlayer();
    const s32 base = param->mNoDeathDamageBase.ref();
    const s32 add = param->mNoDeathDamageAdd.ref();
    return base + uking::act::PlayerInfo::instance()->getMaxLifeFromPlayerActor() * add / 4;
}

bool Player::m373() {
    return uking::act::PlayerInfo::instance()->getStaminaCurrentMax() + _2000 <
           getParam()->getRes().mGParamList->getPlayer()->mEnergyTiredValue.ref();
}

void Player::m372() {
    if (_c44.isOnBit(20)) {
        if (uking::act::PlayerInfo::instance()->getStaminaCurrentMax() !=
            uking::act::PlayerInfo::instance()->getMaxStaminaFromPlayerActor())
            return;
    }
    const f32 value = getParam()->getRes().mGParamList->getPlayer()->mEnergyAutoRecoverInvalidTime1.ref();
    _1d34 = value;
    _1d38 = value;
    _1d3c = -1.0f;
}

bool Player::m183() {
    return mASList->x_1(1, 1) == "HorseBowEndUpper";
}

void Player::getArmorSeriesType(sead::BufferedSafeString* out) {
    out->copy(_23e0._138);
}

bool Player::m225() {
    return mASList->x_1(2, 0) == "WeaponEquipOn" || mASList->x_1(2, 0) == "WeaponEquipOff" ||
           mASList->x_1(2, 0) == "WeaponEquipNG";
}

bool Player::m226() {
    return mASList->x_1(2, 0) == "ItemEquipBoth" || mASList->x_1(2, 0) == "ItemEquipLeftOn" ||
           mASList->x_1(2, 0) == "ItemEquipLeftOff" || mASList->x_1(2, 0) == "ItemEquipRight" ||
           mASList->x_1(1, 1) == "ItemBombReady";
}

bool Player::isASItemBombReadyOrStart() {
    return mASList->x_1(1, 1) == "ItemBombReady" || mASList->x_1(1, 1) == "ItemBombStart";
}

bool Player::m181() {
    return mASList->x_1(1, 1) == "WeaponThrowCharge" || mASList->x_1(1, 1) == "WeaponThrow" ||
           mASList->x_1(0, 0) == "WeaponThrow";
}

bool Player::m182() {
    return mASList->x_1(1, 1) == "WeaponThrow" || mASList->x_1(0, 0) == "WeaponThrow";
}

void Player::sub_7100888278() {
    if (_c40.isOnBit(4)) {
        _c40.resetBit(4);
        x_18(true);
    }
}

void Player::m77(VFR::ScopedDeltaSetter* setter) {
    setter->set(0x42, 1);
}

PlayerLink* Player::m129() {
    return this;
}

PlayerArmors* Player::getArmors() {
    return &_23e0;
}

s32 Player::m234() {
    return _23e0.sub_7100E2F490();
}

s32 Player::getArmorDyeStuff() {
    return _23e0.sub_7100E2F000();
}

bool Player::m280() {
    return _23e0.sub_7100E2F18C();
}

bool Player::ArmorSeriesTypeStuff() {
    return _23e0.sub_7100E30DA8();
}

void Player::getMaskType(sead::BufferedSafeString* out) {
    _23e0.sub_7100E313FC(0, out);
}

void Player::getArmorPartName(u8 idx, sead::BufferedSafeString* out) {
    _23e0.sub_7100E2EDF8(idx, out);
}

s32 Player::m278(u8 idx) {
    return _23e0.sub_7100E2ED78(idx);
}

bool Player::armorSeriesStuff(u8 idx, const sead::SafeString& series) {
    return _23e0.sub_7100E30C78(idx, series);
}

void Player::m41(sead::Matrix34f* mtx) {
    *mtx = _1870->mMtx;
}

void Player::m42(const sead::Matrix34f& mtx) {
    _1870->sub_7100EB57F0(mtx);
}

bool Player::m47() {
    if (_1870)
        _1870->sub_7100EB2448();
    return false;
}

uking::act::HorseRideInfo* Player::getPlayerRideInfo() {
    return &_26b0;
}

uking::act::Unk_71025ae680* Player::m159() {
    return &_2550;
}

Unk_71024ef4e8* Player::getAttachedTargetActor2() {
    return _1870;
}

Unk_71024ef4e8* Player::getAttachedTargetActor() {
    return _1870;
}

gsys::BoneAccessKey Player::m312(int idx) {
    return _19f0[idx];
}

// NON_MATCHING: the original loads mModel before the m312 call (we reload it after the call)
void Player::m318(sead::Matrix34f* out) {
    const auto key = m312(45);
    mModel->getUnits()(key.model_unit_index)->mModelUnit->getBoneWorldMatrix(out, key.bone_index);
}

f32 Player::x_39() {
    sead::Vector3f dir;
    _1b18.getBase(dir, 2);
    dir.normalize();
    return std::atan2(dir.x, dir.z) * (180.0f / sead::Mathf::pi());
}

bool Player::m218() {
    if (auto* chemical = getChemicalStuff()) {
        if ((chemical->_bc & 0x30) == 0x10 || (chemical->_b8 & 4))
            return true;
    }
    return _2550._8.isOnBit(2) || _2550._8.isOnBit(10);
}

bool Player::m353() {
    if (getChemicalStuff())
        return getChemicalStuff()->_10c > 0.0f;
    return false;
}

void Player::m323() {
    syncStatusEffectFlags(false);
}

bool Player::m50() {
    return PlayerOrEnemy::m50();
}

bool Player::m180() {
    return playerIsReloadingOrChargingOrShootingBow(this);
}

void Player::m366() {
    uking::ui::showRuntimeTip(11);
}

void Player::showCannotGoAnyFarther() {
    uking::ui::showInfoOverlay(41);
}

void Player::showCannotGoAnyFarther2() {
    uking::ui::showInfoOverlay(46);
}

bool Player::isSurfingOnGround() const {
    return _cfc.isOnBit(0);
}

bool Player::sub_710087F0B4() {
    sead::Vector3f start = _22f4;
    start.y = _1770.y + 0.35f;
    util::sub_71011EEEE0(&start, _1c84, 0.55f);
    sead::Vector3f end = start;
    end.y += uking::sUnk_7101e7c5d0 * 4.0f;
    return !sub_710087F654(start, end, phys::GroundHit::Player, nullptr, false, false, 0.3f);
}

void Player::sub_71008838FC(sead::Vector3f* out) {
    sead::Vector3f pos = _21b8.mPos;
    pos.y += uking::sUnk_7101e7c2d8;
    sead::Vector3f dir;
    _1b18.getBase(dir, 0);
    dir.normalize();
    *out = pos + dir * uking::sUnk_7101e7c2dc;
}

bool Player::sub_7100888618() {
    return _d30 == getEquipmentTypeName(5);
}

void Player::sub_7100893130(sead::Vector3f* vec) {
    sead::Vector3f dir = *vec;
    dir.normalize();
    dir.y = 0.0f;
    *vec += dir * 0.0f;
}

void Player::sub_710084AD5C(f32 value, bool a2) {
    f32 delta = value * (1.0f / 30.0f);
    if (!a2 && VFR::instance()->getTimeSpeedMultiplierValue(0) < 1.0f)
        delta *= uking::sUnk_7101e7c1d8;
    _e7c[sead::CoreInfo::getCurrentCoreId()] += delta;
}

void Player::m310(f32 target) {
    f32 value = m139();
    const f32 rate = value < target ? uking::sUnk_7101e7c268 : uking::sUnk_7101e7c26c;
    const f32 step = rate * _20ec * VFR::instance()->getDeltaFrame();
    sead::Mathf::chase(&value, target, step);
    m309(value);
}

f32 Player::sub_71008901D0() {
    if ((_17d0->playerCheckController(13) && !m202() && !_c44.isOnBit(13) && !m178()) || m224() ||
        playerIsReloadingOrChargingOrShootingBow(this) || m202()) {
        if (_d10)
            return uking::sUnk_7101e7c184;
        return uking::sUnk_7101e7c1a4;
    }

    if (_c40.isOnBit(1))
        return uking::sUnk_7101e7c2e0 * uking::sUnk_7101e7c5bc;
    return uking::sUnk_7101e7c2e0;
}

void Player::x_38(u32 type) {
    _d68 = getEquipmentTypeName(type);
    sub_710088D654();
}

bool Player::sub_7100888C40() {
    return _d30 == getEquipmentTypeName(1);
}

// NON_MATCHING: the inlined sub_71008569B8 swaps the x / z float registers (same issue as that function).
bool Player::sub_7100856A7C() {
    if (!_d10)
        return false;
    if (_cec.isOnBit(0) && !sub_7100856B74())
        return false;

    Unk1 angle = sub_71008569B8();
    sub_7100857014(-1.0f, &angle, -1, -1);
    return true;
}

bool Player::sub_710087F37C(const sead::Vector3f& start, const sead::Vector3f& end,
                            sead::Vector3f* hit_pos, sead::Vector3f* hit_normal,
                            bool check_normal) {
    uking::Unk_71024739d0 ray(phys::GroundHit::HitAll);
    ray.sub_710090D73C();
    if (!check_normal)
        ray.mQuery.setNormalCheckingMode(phys::RayCast::NormalCheckingMode::_0);
    ray.setStart(start);
    ray.setEnd(end);
    ray.worldRayCast();
    if (!ray.hasHit())
        return false;

    if (hit_pos)
        ray.getHitPosition(hit_pos);
    if (hit_normal)
        ray.getHitNormal(hit_normal);
    return true;
}

// NON_MATCHING: block order in the contact loop (the accepted-actor exit is placed after the loop).
bool Player::sub_710087F654(const sead::Vector3f& start, const sead::Vector3f& end,
                            phys::GroundHit ground_hit, phys::SystemGroupHandler* group_handler,
                            bool water, bool check_actor, f32 radius) {
    phys::SphereCast cast{phys::ContactLayer::EntityPlayer,
                          ground_hit,
                          group_handler,
                          0x80,
                          phys::ShapeCast::Mode::_0,
                          sead::Vector3f::zero,
                          radius,
                          sead::SafeString::cEmptyString,
                          phys::LowPriority::No};
    auto* info = cast.getContactPointInfo();
    info->subscribeLayer(phys::ContactLayer::EntityGround);
    info->subscribeLayer(phys::ContactLayer::EntityGroundSmooth);
    info->subscribeLayer(phys::ContactLayer::EntityGroundRough);
    info->subscribeLayer(phys::ContactLayer::EntityGroundObject);
    info->subscribeLayer(phys::ContactLayer::EntityTree);
    info->subscribeLayer(phys::ContactLayer::EntityObject);
    info->subscribeLayer(phys::ContactLayer::EntityAirWall);
    if (water)
        info->subscribeLayer(phys::ContactLayer::EntityWater);

    cast.setStartAndEnd(start, end);
    // called through a pointer in the original (not devirtualised)
    (&cast)->executeQuery(phys::ShapeCast::WeldClosestPoints::Yes);
    const bool hit = cast.get40();
    if (!hit)
        return false;
    if (!check_actor)
        return true;

    for (auto it = cast.getContactPointInfo()->begin(), it_end = cast.getContactPointInfo()->end();
         it != it_end; ++it) {
        ActorLinkConstDataAccess accessor;
        getCollidedActorMaybe(&accessor, it.getPoint()->body_b);
        if (sub_71002C802C(accessor))
            return true;
    }
    return false;
}

bool Player::sub_7100881B14(f32 depth) {
    sead::Vector3f start = _1770;
    start.y += 1.0f;
    sead::Vector3f end = _1770;
    end.y -= depth + 0.1f;
    return !sub_710087F654(start, end, phys::GroundHit::Player, sub_710072E804(this, 0), false, true,
                           0.1f);
}

bool Player::sub_7100881BAC(f32 depth) {
    auto* controller = getCharacterController();
    if (controller && controller->isBit2Of116())
        return false;

    sead::Vector3f start = _1770;
    start.y += 1.0f;
    sead::Vector3f end = _1770;
    const f32 distance = depth + 0.1f;
    end.y -= distance;

    sead::Vector3f dir;
    _1b18.getBase(dir, 2);
    dir.normalize();
    end += dir * _20bc.value * 5.0f;

    auto* group_handler = sub_710072E804(this, 0);
    if (!sub_710087F654(start, end, phys::GroundHit::Player, group_handler, true, false,
                        uking::sUnk_7101e7c5c4)) {
        return true;
    }

    end = _1770;
    end.y -= distance;
    return !sub_710087F654(start, end, phys::GroundHit::Player, group_handler, true, false,
                           uking::sUnk_7101e7c5c4);
}

bool Player::sub_7100881D8C() {
    const sead::Vector3f start = _1770;
    sead::Vector3f end = _1770;
    end.y += -1.0f;
    return sub_710087F654(start, end, phys::GroundHit::Player, nullptr, false, false, 0.1f);
}

// NON_MATCHING: the original converts the limit after the first call and ends with a branch instead of cset.
bool Player::sub_7100892098() {
    const u32 limit = u32(s64(uking::sUnk_7101e7c2f8 * (0x80000000u / 180.0f)));
    return util::sub_71011EE4C0(_1c90) > limit && util::sub_71011EE4C0(_1c94) > limit;
}

// NON_MATCHING: the original loads the angle mask after both angle fields (scheduling only).
bool Player::sub_71008902B4() {
    if (!(_209c > 0.05f))
        return false;
    const s64 stick = util::sub_71011EE4C0(util::sUnk_7101EC6BA0 & (_1c70 - _1c7c));
    const s64 dir = util::sub_71011EE4C0(util::sUnk_7101EC6BA0 & (_1c74 - _1c68.value));
    const auto* params = getParam()->getRes().mGParamList->getPlayer();
    if (stick <= u32(s64(params->mTurnEnableStickSub.ref() * (0x80000000u / 180.0f))))
        return false;
    const u32 limit = u32(s64(params->mTurnEnableDirSub.ref() * (0x80000000u / 180.0f)));
    if (dir <= limit)
        return false;
    return std::abs(_1f98) < limit;
}

// NON_MATCHING: as sub_71008902B4 (inlined here): the angle mask is loaded after both angle fields in the original.
// Placeholder name: turn-brake start: when the turn checks of sub_71008902B4 pass and the speed exceeds
// TurnEnableSpeed, takes the stick angle as the turn target and plays Brake.
bool Player::sub_7100891F64() {
    if (!sub_71008902B4())
        return false;
    if (!(_20bc.value > getParam()->getRes().mGParamList->getPlayer()->mTurnEnableSpeed.ref()))
        return false;
    _1c7c = _1c70;
    switchToAnimSequenceMaybe("Brake", true, -1.0f);
    if (!sub_7100890394())
        x_18(true);
    return true;
}

// NON_MATCHING: the original keeps the bone position in registers across the ray constructor and gives it its own
// stack slot (ours reuses the matrix slot); one multiply is scheduled differently.
void Player::sub_7100893F1C() {
    if (_d24 != 2)
        return;
    const auto& key = _19f0[47];
    sead::Matrix34f mtx;
    mModel->getUnits().unsafeAt(key.model_unit_index)->mModelUnit->getBoneWorldMatrix(&mtx, key.bone_index);
    sead::Vector3f bone;
    mtx.getTranslation(bone);
    uking::Unk_71024739d0 ray(phys::GroundHit::HitAll);
    sead::Vector3f start = _1770;
    start.y = bone.y;
    sead::Vector3f hit;
    if (!sub_710087F360(start, bone, &hit, nullptr))
        return;
    f32 distance = sead::Vector2f(hit.x - bone.x, hit.z - bone.z).length();
    const f32 min_distance =
        getParam()->getRes().mGParamList->getPlayer()->mCutKnockBackNoCrrDist.ref();
    if (distance < min_distance) {
        distance = 0.0f;
    } else {
        distance = (distance - min_distance) * 30.0f;
        _cf4.setBit(27);
    }
    _1fe8 = distance;
    if (distance > uking::sUnk_7101e7c25c)
        _1fe8 = uking::sUnk_7101e7c25c;
}

void Player::sub_710085AA70(f32 value) {
    Unk_710260af28::instance()->sub_7100F1EAF8(mModel, value);
}

f32 Player::sub_710086DB94(f32 value) {
    return uking::sUnk_7101e7c1dc * value;
}

// Placeholder name: false while slow time is active, else the App_Slowtimer_OnOff flag.
bool Player::sub_710086DBA8() {
    if (isSlowTime())
        return false;
    return gdt::getFlag_App_Slowtimer_OnOff(false);
}

void Player::sub_710086DCF8(f32 value) {
    _1fd4 = value;
}

// Placeholder name: sub_71008822EC, then sets _c44 bit 12, clears the weapon slot 2 flag and calls the sound
// helper with true; with m178() and controller check 18 also clears _c40 bit 1.
void Player::sub_71008821BC() {
    sub_71008822EC();
    _c44.setBit(12);
    getWeapons()->mWeapons[2]._10 = false;
    snd::Unk_7102502138::instance()->sub_710103B444(true);
    if (m178() && _17d0->playerCheckController(18)) {
        _c40.resetBit(1);
        _c44.setBit(12);
    }
}

// Placeholder name: resets _1d4c / _1d50 / _1d54 / _1f88 and the _c40 / _c44 / _c50 bits, then sends request 3 to
// weapon slot 2.
void Player::sub_71008822EC() {
    _1d54 = -1.0f;
    _c50.resetBit(15);
    _c44.resetBit(9);
    _c40.setBit(30);
    _1d4c = 0;
    _1d50 = 0;
    _1f88 = 0;
    sub_71005D787C(this, 2, uking::act::Unk_71002eda38(3));
}

// Placeholder name: clears _c40 bit 10, flags weapon slot 2, then sends request 5 to slot 2 if sub_71005D8514 allows.
void Player::sub_71008823AC() {
    _c40.resetBit(10);
    getWeapons()->mWeapons[2]._10 = true;
    snd::Unk_7102502138::instance()->sub_710103B444(false);
    if (sub_71005D8514(this, 2))
        sub_71005D787C(this, 2, uking::act::Unk_71002eda38(5));
}

// Placeholder name: x_18(true), sets _c50 bit 23 and clears _1f88.
void Player::sub_7100882478() {
    x_18(true);
    _1f88 = 0;
    _c50.setBit(23);
}

// Placeholder name: clears the damage manager's _22c.
void Player::sub_7100884618() {
    if (auto* damage_mgr = sead::DynamicCast<uking::act::DamageMgrPlayer>(getDamageMgr()))
        damage_mgr->_22c = 0;
}

bool Player::sub_710087F43C(const sead::Vector3f& start, const sead::Vector3f& end,
                            sead::Vector3f* hit_pos, sead::Vector3f* hit_normal) {
    uking::Unk_71024739d0 ray(phys::GroundHit::HitAll);
    ray.sub_710090D73C();
    ray.sub_710090D784();
    ray.setStart(start);
    ray.setEnd(end);
    ray.worldRayCast();
    if (!ray.hasHit())
        return false;

    if (hit_pos)
        ray.getHitPosition(hit_pos);
    if (hit_normal)
        ray.getHitNormal(hit_normal);
    return true;
}

bool Player::sub_710087F4F8(const sead::Vector3f& start, const sead::Vector3f& end,
                            sead::Vector3f* hit_pos, sead::Vector3f* hit_normal) {
    uking::Unk_71024739d0 ray(phys::GroundHit::HitAll);
    ray.sub_710090D784();
    ray.setStart(start);
    ray.setEnd(end);
    ray.worldRayCast();
    if (!ray.hasHit())
        return false;

    const auto& mask = ray.mQuery.getMaterialMask();
    if (int(mask.getMaterial()) != phys::Material::Water)
        return false;
    const sead::SafeString sub_material = mask.getSubMaterialName();
    if (sub_material == "Water_Ice" || sub_material == "Water_Poison")
        return false;

    if (hit_pos)
        ray.getHitPosition(hit_pos);
    if (hit_normal)
        ray.getHitNormal(hit_normal);
    return true;
}

}  // namespace ksys::act

namespace ksys::act {

void Player::sub_710087F29C() {
    auto* target = _1870->_c8;
    if (!target)
        return;
    sead::Vector3f position;
    if (!target->sub_7100EAB818(&position))
        return;
    const sead::Vector2f direction(_1770.x - position.x, _1770.z - position.z);
    u32 angle;
    if (direction.length() < sead::Mathf::epsilon()) {
        angle = x_5().value ^ 0x80000000;
        angle = util::sUnk_7101EC6BA0 & angle;
    } else {
        angle = sead::Mathf::atan2Idx(direction.x, direction.y);
    }
    _1c84 = angle;
}

// NON_MATCHING: the original selects the stored speed with an integer csel
void Player::sub_7100877BD8() {
    const sead::Vector3f& translation = getASList()->sub_710115D2D4();
    f32 speed = translation.length();
    if (speed < 0.001f)
        speed = 0.0f;
    f32 value = speed;
    if (_cf4.isOnBit(27))
        value = 0.0f;
    _20bc.value = value;
    _20bc.prev_value = value;
    if (speed == 0.0f)
        return;
    const u32 angle = sead::Mathf::atan2Idx(translation.x, translation.z);
    _1c68.value = (x_5().value + angle) & util::sUnk_7101EC6BA0;
}

void Player::sub_71008697E4() {
    _20bc.value = 0;
    _20bc.prev_value = 0;
    if (auto* controller = getCharacterController())
        controller->sub_7100F5F6FC(sead::Vector3f::zero);
}

// NON_MATCHING: load order / register allocation of the velocity components
void Player::sub_7100892100(const sead::Vector3f& pos) {
    auto* controller = getCharacterController();
    if (!controller)
        return;
    const f32 factor = 1.0f / _20f0;
    const sead::Vector3f velocity = (pos - _1770) * 30.0f * factor;
    controller->sub_7100F5F6FC(velocity);
    controller->sub_7100F5FC8C(_1b18);
}

f32 Player::m235() {
    if (auto* chemical = getChemicalStuff())
        return chemical->sub_7100D91958();
    return 0.0f;
}

void Player::sub_710084BA90(f32 value) {
    auto lock = sead::makeScopedLock(_1610);
    _1650 = true;
    _1654 = value;
}

bool Player::startPreparingForPreDelete_() {
    bool result;
    if (_1878.sub_7100D78960()) {
        if (_548)
            _548->sub_7100D78444(&_1878);
        result = false;
    } else if (_1930.sub_7100D78960()) {
        if (_548)
            _548->sub_7100D78444(&_1930);
        result = false;
    } else if ((_1878._8 && _1878._8->isAddedToWorld()) ||
               (_1930._8 && _1930._8->isAddedToWorld())) {
        result = false;
    } else {
        result = PlayerOrEnemy::startPreparingForPreDelete_();
    }
    if (auto* info = uking::act::PlayerInfo::instance())
        info->resetPlayer(this);
    return result;
}

// NON_MATCHING: register allocation / load scheduling of the two dot products only
bool Player::m258(f32* out) {
    if (!_cec.isOnBit(7))
        return false;
    if (mASList->x_1(0, 0) == "ClimbEd")
        return false;
    if (mVelocity.length() < 0.01f)
        return false;
    const f32 x = _1b18(0, 0) * mVelocity.x + _1b18(1, 0) * mVelocity.y + _1b18(2, 0) * mVelocity.z;
    const f32 y = _1b18(0, 1) * mVelocity.x + _1b18(1, 1) * mVelocity.y + _1b18(2, 1) * mVelocity.z;
    *out = sead::Mathf::atan2(x, y);
    return true;
}

bool Player::m261(f32* out) {
    if (!_cf0.isOnBit(21))
        return false;
    if (mASList->x_1(0, 0) == "LadderUp") {
        *out = 0.0f;
        return true;
    }
    if (mASList->x_1(0, 0) == "LadderDown") {
        *out = sead::Mathf::pi();
        return true;
    }
    return false;
}

bool Player::isMasterSwordEquipped_() {
    ActorLinkConstDataAccess accessor;
    const s32 slot = playerWeapons_return0();
    auto& link = getWeapons()->mWeapons[slot].link;
    if (!link.hasProc())
        return false;
    acquireActor(&link, &accessor);
    if (accessor.hasProc())
        return accessor.getName() == "Weapon_Sword_070";
    return false;
}

bool Player::m227() {
    if (_d24 != 1)
        return false;
    ActorLinkConstDataAccess accessor;
    const s32 slot = playerWeapons_return0();
    auto& link = getWeapons()->mWeapons[slot].link;
    if (link.hasProc())
        acquireActor(&link, &accessor);
    return sub_71002EF884(accessor) == "Katana";
}

bool Player::sub_71008736E4() {
    ActorLinkConstDataAccess accessor;
    const s32 slot = playerWeapons_return0();
    auto& link = getWeapons()->mWeapons[slot].link;
    if (link.hasProc())
        acquireActor(&link, &accessor);
    return sub_71002EF884(accessor) == "Fan";
}

void Player::sub_710089290C() {
    if (_d24 != 1 || m227() || sub_71008736E4()) {
        if (mASList->x_1(0, 0) == "CutChargeWait")
            return;
        mASList->sub_710115EECC(43, _1f8c, 0);
        switchToAnimSequenceMaybe("CutChargeWait", true, -1.0f);
    } else {
        if (mASList->x_1(0, 0) == "CutChargeLswordSpin")
            return;
        switchToAnimSequenceMaybe("CutChargeLswordSpin", true, -1.0f);
    }
}

void Player::sub_7100892A98() {
    if (mASList->x_1(0, 0) != "CutChargeMove")
        switchToAnimSequenceMaybe("CutChargeMove", true, -1.0f);
    if (mASList->x_1(0, 1) != "MoveAttention")
        sub_7100855BB4("CutChargeMoveLower", false, -1.0f);
}

// The epsilon test form is the one in aiUnk_7102433970.cpp / aiMessage3DText.cpp.
void Player::sub_7100881418() {
    auto* controller = getCharacterController();
    if (!controller || !controller->sub_7100F63210() || _cf0.isOnBit(25))
        return;
    if (_1fb0 > getParam()->getRes().mGParamList->getPlayer()->mRoofCrashVel.ref() ||
        !(_1ec0.value <= sead::Mathf::epsilon())) {
        if (mASList->x_1(0, 0) != "JumpStagger")
            switchToAnimSequenceMaybe("JumpStagger", true, -1.0f);
        _1ec0 = Timer(0.0f, 0.0f, -1.0f);
    }
    sead::Vector3f velocity;
    controller->sub_7100F5F598(&velocity);
    if (velocity.y > 0.0f) {
        controller->sub_7100F62B88(sead::Vector3f::zero);
        velocity.y = 0.0f;
        controller->sub_7100F5F6FC(velocity);
    }
}

f32 Player::getSwimMoveSpeed() {
    if (m188() && mASList->x_1(0, 0) == "SwimMove") {
        if (_c44.isOnBit(5))
            return getParam()->getRes().mGParamList->getPlayer()->mArmorCompNakedSwimAnimeRate.ref();
        const f32 level = _2054 + _1ff4;
        return getStatusEffectSwimingAnimRate(level);
    }
    return getStatusEffectSpeed();
}

// Placeholder name (CSV Player::m69_x_2): with _c98 bit 8 set, runs slot 13 of _2550 for indices 0-11;
// then sets _2550._139 bits 2-4 while the damage manager's _22c is positive, an event is active or
// _14c0 is set, and clears them otherwise.
void Player::m69_x_2() {
    if (_c98.isOnBit(8)) {
        for (int i = 0; i < 12; ++i) {
            // called through a pointer in the original (not devirtualised)
            (&_2550)->m13(i);
        }
    }
    auto* damage_mgr = sead::DynamicCast<uking::act::DamageMgrPlayer>(getDamageMgr());
    if (!damage_mgr)
        return;
    if (damage_mgr->_22c > 0 || j_eventMgrHasActiveEventMaybe(this) || _14c0)
        _2550._139.set(0x1c);
    else
        _2550._139.reset(0x1c);
}

// Placeholder name: true while the player is in one of the states checked below (controller check 13
// outside m202 / _c44 bit 13 / m178, m202, _c44 bit 8 without _d11, m224, using the bow, Cryonis), else
// whether _d30 names the equipment of type 5.
bool Player::sub_7100863534() {
    if ((_17d0->playerCheckController(13) && !m202() && !_c44.isOnBit(13) && !m178()) || m202() ||
        (_c44.isOnBit(8) && !_d11) || m224() || playerIsReloadingOrChargingOrShootingBow(this) ||
        (runeMgrCheckCanUseCryonis() && sub_71008494B8())) {
        return true;
    }
    return _d30 == getEquipmentTypeName(5);
}

// NON_MATCHING: the original copies the controller velocity through a second stack vector before the y check
// and loads the 5.0 global first.
// Placeholder name (CSV Player::m69_x_6): sets the character controller's velocity (twice the actor velocity
// times 30 with _c50 bit 35; the knock-back _1fe8 against the _1b18 z axis; zero while blocked, which resets
// _1e78; else after _1e78 runs out, half of _216c pushed down by 5), then above y = 1700 clamps the upward speed.
void Player::m69_x_6() {
    if (x_2())
        return;
    auto* controller = getCharacterController();
    if (!controller)
        return;

    sead::Vector3f velocity;
    if (_c50.isOnBit(35)) {
        velocity = (mVelocity + mVelocity) * 30.0f;
        controller->sub_7100F5F060(velocity);
    } else if (_1fe8 != 0.0f) {
        sead::Vector3f dir;
        _1b18.getBase(dir, 2);
        dir.normalize();
        velocity = -(dir * _1fe8);
        controller->sub_7100F5F060(velocity);
        _1fe8 = 0.0f;
    } else if (!_c98.isOnBit(16) || _cec.isOnBit(1) || _cf0.isOnBit(11) ||
               j_eventMgrHasActiveEventMaybe(this) || _14c0) {
        _1e78.value = _1e78.previous_value = 1.0f;
        controller->sub_7100F5F060(sead::Vector3f::zero);
    } else if (_1e78.value <= sead::Mathf::epsilon()) {
        velocity = uking::sUnk_7101e7c248 * _216c + sead::Vector3f(0.0f, -uking::sUnk_7101e7c244, 0.0f);
        controller->sub_7100F5F060(velocity);
    } else {
        _1e78.update();
    }

    if (_1770.y > 1700.0f) {
        controller->sub_7100F5F598(&velocity);
        if (velocity.y > 0.0f) {
            velocity.y = 0.0f;
            controller->sub_7100F5F6FC(velocity);
        }
    }
}

// Placeholder name (CSV Player::m71_x): resizes the Tgt cylinder by _cec bit 2 and moves the AreaCheck sensor to
// _1770.
void Player::sub_71008655AC() {
    if (_cec.isOnBit(2))
        sub_7100873094();
    else
        sub_710087317C();
    if (auto* physics = mPhysics) {
        if (auto* set = physics->findBodyByName("AreaCheck")) {
            if (auto* body = set->findBodyByHavokName("SensorForArea"))
                body->changePosition(_1770, phys::KeepAngularVelocity{false});
        }
    }
}

// Placeholder name: sets _c40 bit 25 and shortens the Tgt cylinder body (height 1.2).
void Player::sub_7100873094() {
    if (_c40.isOnBit(25))
        return;
    _c40.setBit(25);
    if (auto* set = mPhysics->findBodyByName(*sub_71007A24D0())) {
        if (auto* body = sead::DynamicCast<phys::CylinderRigidBody>(set->getRigidBody(0)))
            body->setVertices(sead::Vector3f::zero, {0.0f, 1.2f, 0.0f});
    }
}

// Placeholder name: clears _c40 bit 25 and restores the Tgt cylinder body (height 1.6).
void Player::sub_710087317C() {
    if (_c40.isOffBit(25))
        return;
    _c40.resetBit(25);
    if (auto* set = mPhysics->findBodyByName(*sub_71007A24D0())) {
        if (auto* body = sead::DynamicCast<phys::CylinderRigidBody>(set->getRigidBody(0)))
            body->setVertices(sead::Vector3f::zero, {0.0f, 1.6f, 0.0f});
    }
}

void Player::nullsub_2601() {}

void Player::m88() {
    mPreviousPos = _17a0;
}

bool Player::m217() {
    return _2550._8.isOn(0x108);
}

bool Player::m151(u16 bit) {
    return _2550._8.isOnBit(bit);
}

bool Player::m83() {
    return !m359();
}

bool Player::isGuardJust() {
    if (_c40.isOnBit(5))
        return true;
    return isDarukProtectionEnabled();
}

bool Player::m374() {
    auto* life = getLife();
    return life && *life < 1;
}

bool Player::m328() {
    if (auto* chemical = getChemicalStuff()) {
        if ((chemical->_bc & 0x30) == 0x10)
            return true;
    }
    return false;
}

bool Player::m376() {
    if (auto* chemical = getChemicalStuff()) {
        if (chemical->_b8 & 4)
            return true;
    }
    return false;
}

void* Player::m119() {
    return _1b90;
}

bool Player::m256() {
    return x_32() || isASItemBombReadyOrStart();
}

bool Player::m257() {
    return x_32();
}

bool Player::m268() {
    return sub_71008921A8();
}

bool Player::m270() {
    return sub_7100881EDC();
}

bool Player::m287() {
    return sub_710088873C();
}

s32 Player::m288() {
    auto* info = getPlayerRideInfo();
    if (info->_18.isAccessingSpecifiedProcUnsafe(info->mActor))
        return 0;
    auto* actor = sead::DynamicCast<Actor>(info->_18.getProc(nullptr, info->mActor));
    if (!actor)
        return 0;
    auto* rideable = actor->getHorseOptionsMaybe();
    if (!rideable)
        return 0;
    return int(uking::act::Rideable::Gear(rideable->_18._b == 0 ? rideable->_18._9 :
                                                             rideable->_18._b));
}

s32 Player::m289() {
    auto* info = getPlayerRideInfo();
    if (info->_18.isAccessingSpecifiedProcUnsafe(info->mActor))
        return 0;
    auto* actor = sead::DynamicCast<Actor>(info->_18.getProc(nullptr, info->mActor));
    if (!actor)
        return 0;
    auto* rideable = actor->getHorseOptionsMaybe();
    if (!rideable)
        return 0;
    return int(rideable->m23());
}

bool Player::m290() {
    auto* info = getPlayerRideInfo();
    Actor* actor = nullptr;
    if (!info->_18.isAccessingSpecifiedProcUnsafe(info->mActor))
        actor = sead::DynamicCast<Actor>(info->_18.getProc(nullptr, info->mActor));
    if (auto* motorcycle = sead::DynamicCast<uking::act::Motorcycle>(actor))
        return motorcycle->sub_710007A478();
    return m288() > 0;
}

bool Player::m295() {
    return sub_7100892724();
}

s32 Player::m296() {
    return sub_7100892824();
}

s32 Player::m298(int a1) {
    return sub_71008923B0(a1);
}

s32 Player::m291() {
    ActorLinkConstDataAccess accessor;
    s32 result = 0;
    if (acquireActor(&getPlayerRideInfo()->_18, &accessor))
        result = s32(accessor.sub_7100D14598());
    return result;
}

f32 Player::getStatusEffectMovingSpeed(s32 level) {
    eco::StatusEffectInfo info;
    eco::Ecosystem::instance()->getStatusEffectInfo(eco::StatusEffect_MovingSpeed, level, &info);
    return info.val._f32;
}

f32 Player::getStatusEffectSwimingSpeed(s32 level) {
    eco::StatusEffectInfo info;
    eco::Ecosystem::instance()->getStatusEffectInfo(eco::StatusEffect_SwimingSpeed, level, &info);
    return info.val._f32;
}

f32 Player::getStatusEffectClimbingSpeed(s32 level) {
    eco::StatusEffectInfo info;
    eco::Ecosystem::instance()->getStatusEffectInfo(eco::StatusEffect_ClimbingSpeed, level, &info);
    return info.val._f32;
}

s32 Player::getStatusEffectDefenseUp(s32 level) {
    eco::StatusEffectInfo info;
    eco::Ecosystem::instance()->getStatusEffectInfo(eco::StatusEffect_DefenseUp, level, &info);
    return static_cast<s32>(info.val._f32);
}

f32 Player::getStatusEffectQuietness(s32 level) {
    eco::StatusEffectInfo info;
    eco::Ecosystem::instance()->getStatusEffectInfo(eco::StatusEffect_Quietness, level, &info);
    return info.val._f32;
}

f32 Player::getStatusEffectDesertMovingSpeed(s32 level) {
    eco::StatusEffectInfo info;
    eco::Ecosystem::instance()->getStatusEffectInfo(eco::StatusEffect_DesertMovingSpeed, level, &info);
    return info.val._f32;
}

f32 Player::getStatusEffectSnowMovingSpeed(s32 level) {
    eco::StatusEffectInfo info;
    eco::Ecosystem::instance()->getStatusEffectInfo(eco::StatusEffect_SnowMovingSpeed, level, &info);
    return info.val._f32;
}

f32 Player::getStatusEffectThrowingPower(s32 level) {
    eco::StatusEffectInfo info;
    eco::Ecosystem::instance()->getStatusEffectInfo(eco::StatusEffect_ThrowingPower, level, &info);
    return info.val._f32;
}

f32 Player::getStatusEffectReduceAncientEnemyDamage(s32 level) {
    eco::StatusEffectInfo info;
    eco::Ecosystem::instance()->getStatusEffectInfo(eco::StatusEffect_ReduceAncientEnemyDamge, level, &info);
    return info.val._f32;
}

// NON_MATCHING: the singleton load is scheduled before the status-level member read.
void Player::updateStatusEffectMasterSwordAttackUp() {
    eco::StatusEffectInfo info;
    eco::Ecosystem::instance()->getStatusEffectInfo(eco::StatusEffect_MaterSwordAttackUp, _2048, &info);
    _2090 = info.val._f32;
}

// NON_MATCHING: stack layout only: the original reuses one temporary slot and keeps x_5()'s result at sp
// (frame 0x40, ours 0x50).
void Player::sub_7100884FCC() {
    const sead::Vector3f dir = sub_710087386C();
    const u32 angle = sead::Mathf::atan2Idx(dir.x, dir.z);
    const Unk1 current = x_5();
    _d1c = sub_7100869814(util::angleDiff(angle, current),
                          Unk1(util::sUnk_7101EC6BA0 & 0x20000000));
    _1c68 = Unk1(angle);
    getASList()->x_6(9, 0,
                     util::sub_71011EE4B8(util::angleDiff(angle, current)) * util::sUnk_7101EC6BA4);
}

// NON_MATCHING: the original copies the velocity onto its own stack slot after each sub_7100F5F598 call
// (a by-value temporary, source form unknown).
void Player::sub_7100881DFC(f32 y, bool a2) {
    auto* controller = getCharacterController();
    if (!controller)
        return;
    if (controller->sub_7100F609CC().getFloorCode() == phys::FloorCode::Attach) {
        sead::Vector3f velocity;
        controller->sub_7100F5F598(&velocity);
        if (velocity.y > 0.0f) {
            velocity.y = 0.0f;
            controller->sub_7100F5F6FC(velocity);
        }
    } else {
        sead::Vector3f velocity;
        controller->sub_7100F5F598(&velocity);
        if ((velocity.y > 0.0f && a2) || (y < 0.9f && velocity.y > 0.0f && velocity.y < 10.0f)) {
            velocity.y = 0.0f;
            controller->sub_7100F5F6FC(velocity);
        }
    }
}

// Placeholder name: unless _c4c bit 9 is set, sends message 0x8000036 to the four HeroSoul actors and the
// revival fairy (mResidentActors[3..6], [2]), then sets the bit.
void Player::sub_7100861858() {
    if (_c4c.isOnBit(9))
        return;
    {
        ActorLinkConstDataAccess accessor;
        acquireActor(&mResidentActors[3], &accessor);
        sendMessage(*accessor.getMessageTransceiverId(), MessageType(0x8000036), nullptr, true);
    }
    {
        ActorLinkConstDataAccess accessor;
        acquireActor(&mResidentActors[4], &accessor);
        sendMessage(*accessor.getMessageTransceiverId(), MessageType(0x8000036), nullptr, true);
    }
    {
        ActorLinkConstDataAccess accessor;
        acquireActor(&mResidentActors[5], &accessor);
        sendMessage(*accessor.getMessageTransceiverId(), MessageType(0x8000036), nullptr, true);
    }
    {
        ActorLinkConstDataAccess accessor;
        acquireActor(&mResidentActors[6], &accessor);
        sendMessage(*accessor.getMessageTransceiverId(), MessageType(0x8000036), nullptr, true);
    }
    ActorLinkConstDataAccess accessor;
    acquireActor(&mResidentActors[2], &accessor);
    sendMessage(*accessor.getMessageTransceiverId(), MessageType(0x8000036), nullptr, true);
    _c4c.setBit(9);
}

// NON_MATCHING: block order of the midpoint selection and the _1cbc checks, register allocation of the last part.
// Placeholder name: from three ladder points, _22f4 = the midpoint of the two closest in height (y replaced by the
// lowest / highest point for _1cbc 4 / 5, else _1770.y) and _2100 = the highest y (lowered for _1cbc 5).
void Player::sub_7100883F48(const sead::Vector3f& a, const sead::Vector3f& b, const sead::Vector3f& c) {
    const f32 ab = sead::Mathf::abs(a.y - b.y);
    const f32 bc = sead::Mathf::abs(b.y - c.y);
    const f32 ca = sead::Mathf::abs(c.y - a.y);
    const sead::Vector3f* p;
    const sead::Vector3f* q;
    if (ab < bc && ab < ca) {
        p = &a;
        q = &b;
    } else if (bc < ca) {
        p = &b;
        q = &c;
    } else {
        p = &c;
        q = &a;
    }
    _22f4 = (*p + *q) * 0.5f;

    f32 y;
    if (_1cbc == 4) {
        if (a.y <= b.y && a.y <= c.y) {
            y = a.y;
        } else {
            const f32 by = b.y;
            const f32 cy = c.y;
            y = by <= cy ? by : cy;
        }
    } else if (_1cbc == 5) {
        if (a.y >= b.y && a.y >= c.y) {
            y = a.y;
        } else {
            const f32 by = b.y;
            const f32 cy = c.y;
            y = by >= cy ? by : cy;
        }
    } else {
        y = _1770.y;
    }
    _22f4.y = y;

    const sead::Vector3f* top = b.y >= c.y ? &b : &c;
    if (a.y >= c.y && a.y >= b.y)
        top = &a;
    const f32 top_y = top->y;
    _2100 = top_y;
    if (_1cbc == 5)
        _2100 = top_y - uking::sUnk_7101e7c5d0;
}

bool Player::sub_71008840C4() {
    return _c40.isOffBit(18);
}

bool Player::sub_71008840D4() {
    return _c50.isOnBit(3);
}

f32 Player::sub_71008902A8() {
    return 0.3f;
}

f32 Player::sub_7100885818(s32) {
    return 1.0f;
}

// The f32 argument is unused (sub_710088D654 passes -1).
void Player::sub_7100887B68(f32) {
    x_23("GrabWait", false, -1.0f);
}

bool Player::sub_71008927D8() {
    return getASList()->sub_710115ED5C(0x42, 0x24) && getASList()->sub_710115ED5C(0x42, 0x26);
}

bool Player::sub_71008494AC() {
    return _17d0->playerCheckController(35);
}

u8 Player::sub_710087ACC8() {
    return _d10;
}

bool Player::sub_710086CAB8() {
    return !x_44();
}

bool Player::sub_71008697C0() {
    return sead::Mathf::abs(_20bc.value) < 0.01f;
}

// NON_MATCHING: the singleton load is scheduled before the status-level member reads, whose load
// order also differs from the original.
void Player::updateResistHotVal() {
    eco::StatusEffectInfo info;
    eco::Ecosystem::instance()->getStatusEffectInfo(eco::StatusEffect_ResistHot, _200c + _2028, &info);
    _2084 = info.val._f32;
}

// NON_MATCHING: the singleton load is scheduled before the status-level member reads, whose load
// order also differs from the original.
void Player::updateResistColdVal() {
    eco::StatusEffectInfo info;
    eco::Ecosystem::instance()->getStatusEffectInfo(eco::StatusEffect_ResistCold, _2010 + _202c, &info);
    _2088 = info.val._f32;
}

// NON_MATCHING: the singleton load is scheduled before the status-level member reads, whose load
// order also differs from the original.
// Restores the food status effects from the game data flags (Item_*), then applies them.
void Player::updateFoodStatusEffectFlagsFromGameData() {
    x_12(false);
    setItemVel(gdt::getS32ByKey("Item_VelRate"), gdt::getF32ByKey("Item_VelTime"));
    setItemSwimVel(gdt::getS32ByKey("Item_SwimVelRate"), gdt::getF32ByKey("Item_SwimVelTime"));
    sub_710084B6D4(gdt::getS32ByKey("Item_ClimbVelRate"), gdt::getF32ByKey("Item_ClimbVelTime"));
    setExtraLife(gdt::getS32ByKey("Item_LifeMaxAdd"), gdt::getF32ByKey("Item_LifeMaxAddTime"));
    addExtraStamina(gdt::getF32ByKey("Item_EnergyMaxAdd"), gdt::getF32ByKey("Item_EnergyMaxAddTime"));
    sub_710084B7C0(gdt::getS32ByKey("Item_AttackRate"), gdt::getF32ByKey("Item_AttackTime"));
    sub_710084B810(gdt::getS32ByKey("Item_DefenceRate"), gdt::getF32ByKey("Item_DefenceTime"));
    sub_710084B860(gdt::getS32ByKey("Item_HotLevelAdd"), gdt::getF32ByKey("Item_HotLevelAddTime"));
    sub_710084B8B0(gdt::getS32ByKey("Item_ColdResistLevelAdd"), gdt::getF32ByKey("Item_ColdLevelAddTime"));
    sub_710084B900(gdt::getS32ByKey("Item_BurnLevelAdd"), gdt::getF32ByKey("Item_BurnLevelAddTime"));
    sub_710084B950(gdt::getS32ByKey("Item_FreezeLevelAdd"), gdt::getF32ByKey("Item_FreezeLevelAddTime"));
    sub_710084B9A0(gdt::getS32ByKey("Item_ElectricLevelAdd"), gdt::getF32ByKey("Item_ElectricLevelAddTime"));
    sub_710084B9F0(gdt::getS32ByKey("Item_LightningLevelAdd"), gdt::getF32ByKey("Item_LightningLevelAddTime"));
    sub_710084BA40(gdt::getS32ByKey("Item_NoiseRate"), gdt::getF32ByKey("Item_NoiseTime"));
    _1ffc = 0;
    _2000 = 0;
    syncStatusEffectFlags(true);
}

// NON_MATCHING: the original sinks each level / timer store into one block per effect (selecting the values);
// ours stores in both arms. Same logic.
// Copies the pending status effects (_1180 .. _11ec, written by the PlayerBase setters) into the levels _1ff0 ..
// _2024 and their duration timers. Effects that are not pending are cleared when `force` is set or any other
// effect is pending.
void Player::syncStatusEffectFlags(bool force) {
    bool clear = true;
    if (!force && _1184 == 0.0f && _118c == 0.0f && _1194 == 0.0f && _119c == 0.0f && _11a4 == 0.0f &&
        _11a8[0].value == 0.0f && _11a8[1].value == 0.0f && _11a8[2].value == 0.0f &&
        _11a8[3].value == 0.0f && _11a8[4].value == 0.0f && _11a8[5].value == 0.0f &&
        _11a8[6].value == 0.0f && _11a8[7].value == 0.0f && _11a8[8].value == 0.0f) {
        clear = false;
    }

    if (_1180 != 0.0f) {
        _1ff0 = s32(_1180);
        _1ed8[0] = ksys::Timer(_1184, _1184);
    } else if (clear) {
        _1ff0 = 0;
        _1ed8[0] = ksys::Timer(0, 0);
    }
    if (_1188 != 0.0f) {
        _1ff4 = s32(_1188);
        _1ed8[1] = ksys::Timer(_118c, _118c);
    } else if (clear) {
        _1ff4 = 0;
        _1ed8[1] = ksys::Timer(0, 0);
    }
    if (_1190 != 0.0f) {
        _1ff8 = s32(_1190);
        _1ed8[2] = ksys::Timer(_1194, _1194);
    } else if (clear) {
        _1ff8 = 0;
        _1ed8[2] = ksys::Timer(0, 0);
    }

    auto* info = uking::act::PlayerInfo::instance();
    if (_1198 != 0) {
        const s32 max_heart = info->getMaxHeartValue();
        if (_1ffc < _1198) {
            _1ffc = _1198;
            _1ed8[3] = ksys::Timer(0, 0);
            uking::act::PlayerInfo::instance()->setMaxLifeForPlayerActor(_1198 + max_heart);
            sub_710084AC68();
        }
    } else if (force) {
        _1ffc = 0;
        _1ed8[3] = ksys::Timer(0, 0);
        info->setMaxLifeForPlayerActor(info->getMaxHeartValue());
    }

    if (_11a0 != 0.0f) {
        const f32 value = _11a0;
        const f32 prev = _2000;
        sub_710084AE78();
        if (value - prev > 0.0f) {
            _2000 = _11a0;
            _1ed8[4] = ksys::Timer(0, 0);
        }
    } else if (force) {
        _2000 = 0;
        _1ed8[4] = ksys::Timer(0, 0);
    }

    if (_11a8[0].type != 0) {
        _2004 = _11a8[0].type;
        _1ed8[5] = ksys::Timer(_11a8[0].value, _11a8[0].value);
    } else if (clear) {
        _2004 = 1;
        _1ed8[5] = ksys::Timer(0, 0);
    }
    updateStatusEffectAttackUp();
    if (_11a8[1].type != 0) {
        _2008 = _11a8[1].type;
        _1ed8[6] = ksys::Timer(_11a8[1].value, _11a8[1].value);
    } else if (clear) {
        _2008 = 1;
        _1ed8[6] = ksys::Timer(0, 0);
    }
    if (_11a8[2].type != 0) {
        _200c = _11a8[2].type;
        _1ed8[7] = ksys::Timer(_11a8[2].value, _11a8[2].value);
    } else if (clear) {
        _200c = 0;
        _1ed8[7] = ksys::Timer(0, 0);
    }
    updateResistHotVal();
    if (_11a8[3].type != 0) {
        _2010 = _11a8[3].type;
        _1ed8[8] = ksys::Timer(_11a8[3].value, _11a8[3].value);
    } else if (clear) {
        _2010 = 0;
        _1ed8[8] = ksys::Timer(0, 0);
    }
    updateResistColdVal();
    if (_11a8[4].type != 0) {
        _2014 = _11a8[4].type;
        _1ed8[9] = ksys::Timer(_11a8[4].value, _11a8[4].value);
    } else if (clear) {
        _2014 = 0;
        _1ed8[9] = ksys::Timer(0, 0);
    }
    if (_11a8[5].type != 0) {
        _2018 = _11a8[5].type;
        _1ed8[10] = ksys::Timer(_11a8[5].value, _11a8[5].value);
    } else if (clear) {
        _2018 = 0;
        _1ed8[10] = ksys::Timer(0, 0);
    }
    if (_11a8[6].type != 0) {
        _201c = _11a8[6].type;
        _1ed8[11] = ksys::Timer(_11a8[6].value, _11a8[6].value);
    } else if (clear) {
        _201c = 0;
        _1ed8[11] = ksys::Timer(0, 0);
    }
    if (_11a8[7].type != 0) {
        _2020 = _11a8[7].type;
        _1ed8[12] = ksys::Timer(_11a8[7].value, _11a8[7].value);
    } else if (clear) {
        _2020 = 0;
        _1ed8[12] = ksys::Timer(0, 0);
    }
    if (_11a8[8].type != 0) {
        _2024 = _11a8[8].type;
        _1ed8[13] = ksys::Timer(_11a8[8].value, _11a8[8].value);
    } else if (clear) {
        _2024 = 1;
        _1ed8[13] = ksys::Timer(0, 0);
    }
    sub_710086DD00();
    x_12(false);
}

void Player::updateStatusEffectAttackUp() {
    eco::StatusEffectInfo info;
    eco::Ecosystem::instance()->getStatusEffectInfo(eco::StatusEffect_AttackUp, _2004 + _2040, &info);
    _208c = info.val._f32;
}

void Player::showRuntimeTipForColdHotStatusEffects() {
    if (m151(1)) {
        eco::StatusEffectInfo info;
        eco::Ecosystem::instance()->getStatusEffectInfo(eco::StatusEffect_ResistCold, 1, &info);
        auto* chemical = getChemicalStuff();
        const f32 temperature = chemical ? chemical->sub_7100D91958() : 0.0f;
        if (info.val._f32 > temperature)
            uking::ui::showRuntimeTip(18);
        else
            uking::ui::showRuntimeTip(5);
    }
    if (m151(0)) {
        eco::StatusEffectInfo info;
        eco::Ecosystem::instance()->getStatusEffectInfo(eco::StatusEffect_ResistHot, 1, &info);
        auto* chemical = getChemicalStuff();
        const f32 temperature = chemical ? chemical->sub_7100D91958() : 0.0f;
        if (info.val._f32 < temperature)
            uking::ui::showRuntimeTip(19);
        else
            uking::ui::showRuntimeTip(6);
    }
    if (auto* chemical = getChemicalStuff()) {
        if ((chemical->_bc & 0x30) == 0x10) {
            if (chemical->sub_7100D914C0() >= 2)
                uking::ui::showRuntimeTip(20);
            else
                uking::ui::showRuntimeTip(10);
        }
    }
}

void Player::m69_x_1() {
    if (uking::act::PlayerInfo::instance()->getStaminaCurrentMax() == 0.0f && _2000 == 0.0f) {
        _c44.setBit(20);
        uking::ui::showRuntimeTip(4);
    }
}

// NON_MATCHING: the original branches from each test straight to one shared "return true" block (we emit one
// `orr w0, wzr, #1; b` per test and return the last bit with ubfx)
bool Player::m365() {
    return x_44() || _17d0->controllerCheckPressedMaybe(14) ||
           GameSceneSubsys14::instance()->sub_7100904F04() ||
           (!_17d0->playerCheckController(2) && _c44.isOnBit(25));
}

void Player::sub_710085ECF4() {
    if (auto* controller = getCharacterController())
        controller->sub_7100F5EECC(60.0f);
}

f32 Player::x_67() {
    if (_23e0.sub_7100E2F61C()->isOnBit(0))
        return getParam()->getRes().mGParamList->getPlayer()->mArmorCompSwimEnergyRate.ref();
    return 1.0f;
}

f32 Player::m231() {
    if (_23e0.sub_7100E2F61C()->isOnBit(9))
        return getParam()->getRes().mGParamList->getPlayer()->mArmorCompPlusDropRate.ref();
    return 1.0f;
}

f32 Player::getBoneAttackRate() {
    if (_23e0.sub_7100E2F61C()->isOnBit(7))
        return getParam()->getRes().mGParamList->getPlayer()->mArmorCompBoneAttackRate.ref();
    return 1.0f;
}

// NON_MATCHING: parameter-object value addressing is scheduled differently.
f32 Player::getAncientAttackRate() {
    if (_23e0.sub_7100E2F61C()->isOnBit(10))
        return getParam()->getRes().mGParamList->getPlayer()->mArmorCompAncientAttackRate.ref();
    if (_23e0.hasAncientPowUpEffect())
        return getParam()->getRes().mGParamList->getPlayer()->mArmorAncientAttackRate.ref();
    return 1.0f;
}

f32 Player::m364() {
    if (_23e0.sub_7100E2F61C()->isOnBit(8))
        return getParam()->getRes().mGParamList->getPlayer()->mArmorCompClimbJumpEnergyRate.ref();
    return 1.0f;
}

f32 Player::getGuardableAngle() {
    if (isDarukProtectionEnabled())
        return sead::Mathf::pi();
    return sead::Mathf::deg2rad(getParam()->getRes().mGParamList->getPlayer()->mGuardableAngle.ref());
}

// NON_MATCHING: block layout (the original loads _1cec and epsilon before testing isRidingHorse() and keeps the
// "return true" block last)
bool Player::m230() {
    return (isRidingHorse() && !(_1cec <= sead::Mathf::epsilon())) ||
           !(_1cf8 <= sead::Mathf::epsilon());
}

bool Player::x_35() {
    return m225() || m226();
}

bool Player::canUseRevaliGale() {
    if (StageInfo::sIsCDungeon | StageInfo::sIsAocField)
        return false;
    if (gdt::getFlag_HeroSoulProhibition())
        return false;
    if (playerIsReloadingOrChargingOrShootingBow(this))
        return false;
    if (_c44.isOnBit(8) && !_d11)
        return false;
    if (!hasRitoSoul())
        return false;
    return _1df4 <= sead::Mathf::epsilon();
}

bool Player::canUseDarukProtection() {
    if (StageInfo::sIsCDungeon | StageInfo::sIsAocField)
        return false;
    if (gdt::getFlag_HeroSoulProhibition())
        return false;
    if (!hasDarukProtection())
        return false;
    return _1e00 <= sead::Mathf::epsilon();
}

bool Player::canUseUrbosaFury() {
    if (StageInfo::sIsCDungeon | StageInfo::sIsAocField)
        return false;
    if (gdt::getFlag_HeroSoulProhibition())
        return false;
    if (!hasMiphaSoul())
        return false;
    return _1e0c <= sead::Mathf::epsilon();
}

// NON_MATCHING: the original loads _c48 as a word (`ldr w8` + tbnz) after `mov w0, wzr`; we narrow it to a byte load
// NON_MATCHING: the original assigns x / z to the other float registers. The signed-64 rad2idx
// conversion is also present in aal::SoundParam::setAngle (0x7100b763d8) and this consumer (0x71008569b8).
Player::Unk1 Player::sub_71008569B8() {
    Unk1 result(0);
    f32 x = sead::Vector3f::zero.x;
    f32 z = sead::Vector3f::zero.z;
    if (!Attention::instance()->sub_7100D742E8(1)) {
        ActorLinkConstDataAccess accessor;
        Attention::instance()->x_0(1, 0, &accessor);
        const auto& pos = accessor.getPreviousPos2();
        x = pos.x;
        z = pos.z;
    }
    result.value = sead::Mathf::rad2idx(sead::Mathf::atan2(x - _1770.x, z - _1770.z));
    return result;
}

// NON_MATCHING: the original keeps the translation in registers and builds both water-check vectors on the
// stack inside the m188() branch.
void Player::setMtx(const sead::Matrix34f& mtx, bool a2, bool a3) {
    if (x_2())
        getAttachedTargetActor2()->sub_7100EB51E0();
    if (_1a0 || (mMapObject && mMapObject->getFlags0().isOn(map::Object::Flag0::_20000)))
        _c4c.setBit(13);
    setC98Locked(0x800000);
    Actor::setMtx(mtx, a2, a3);
    if (a3)
        getWeapons()->x();

    const u32 angle = sead::Mathf::atan2Idx(mtx(0, 2), mtx(2, 2));
    x_53(Unk1(angle));
    _1c68.value = angle;

    const sead::Vector3f pos = mtx.getTranslation();
    _20d0 = pos.y;
    _1770 = pos;
    sub_7100E9CF30(_1b90);
    if (m188()) {
        sead::Vector3f start = pos;
        start.y += 1.8f;
        if (!sub_710087F4F8(start, pos, nullptr, nullptr))
            _cec.resetBit(10);
    }
    _cec.resetBit(7);
    if (auto* controller = getCharacterController())
        controller->sub_7100F6059C();
    if (m203()) {
        if (auto* pause_menu = uking::ui::PauseMenuDataMgr::instance())
            pause_menu->unholdGrabbedItems();
    }
}

f32 Player::sub_7100867D68() {
    sead::Vector3f dir;
    _1b18.getBase(dir, 2);
    dir.normalize();
    return sead::Mathf::atan2(dir.x, dir.z);
}

// NON_MATCHING: same arithmetic; the original keeps the quaternion and the 3x3 rotation in registers (ours
// goes through the stack) and schedules the product differently.
// Turns the up axis of _1b18 towards `target_up`, at most `rate * _20f0` per frame.
void Player::someFloatCalc(f32 rate, const sead::Vector3f& target_up) {
    sead::Vector3f up;
    _1b18.getBase(up, 1);
    up.normalize();
    const f32 max_step = _20f0 * rate * VFR::instance()->getDeltaFrame();
    sead::Vector3f diff = target_up - up;
    const f32 distance = diff.length();
    sead::Vector3f new_up;
    if (distance <= max_step)
        new_up = target_up;
    else
        new_up = up + diff * max_step * (1.0f / distance);

    sead::Quatf rotation;
    rotation.makeVectorRotation(up, new_up);
    sead::Matrix33f rotation_mtx;
    rotation_mtx.fromQuat(rotation);
    _1b18.setMul(rotation_mtx, _1b18);
}

// NON_MATCHING: the Matrix33 multiplication is outlined instead of inlined.
void Player::sub_7100867DEC(const sead::Vector3<u32>& rotation) {
    const u32 factor = static_cast<u32>(_20f0);
    sead::Matrix33f delta;
    delta.makeRIdx(rotation.x * factor, rotation.y * factor, rotation.z * factor);
    const sead::Vector3f translation = _1b18.getTranslation();
    _1b18.setMul(delta, _1b18);
    _1b18.setTranslation(translation);
}

void Player::sub_7100867FE0(const Unk1& angle) {
    const sead::Vector3<u32> rotation(0, angle.value, 0);
    sub_7100867DEC(rotation);
}

// NON_MATCHING: the movement temporary shares the output stack slot, reducing the frame by 16 bytes.
void Player::sub_7100877F00(const sead::Vector3f& dir) {
    auto* controller = getCharacterController();
    if (!controller)
        return;

    sead::Vector3f forward;
    _1b18.getBase(forward, 2);
    forward.normalize();
    const f32 angle = sead::Mathf::atan2(forward.x, forward.z);
    sead::Vector3f movement = mASList->sub_710115D2D4();
    util::sub_71011EF010(&movement, angle);
    movement += dir;
    movement *= 30.0f;
    controller->sub_7100F5F6FC(movement);
    sub_710086800C(mASList->sub_710115D3B8().y);
    controller->sub_7100F5FC8C(_1b18);
}

void Player::sub_7100857390() {
    Unk1 target = ::sub_710092DBA4();
    sub_7100857014(-1.0f, &target, -1, -1);
}

// NON_MATCHING: ours merges the two paths ending in an atan2Idx call into one block with a computed output index
// (`str w0, [x19, x21, lsl #2]`); the original keeps both tails
void Player::sub_7100869258(const sead::Matrix33f& mtx, u32* out) {
    const f32 len = sead::Mathf::sqrt(mtx(0, 2) * mtx(0, 2) + mtx(2, 2) * mtx(2, 2));
    const u32 pitch = sead::MathCalcCommon<f32>::atan2Idx(-mtx(1, 2), len);
    out[0] = pitch;
    if ((pitch | 0x80000000) == 0xc0000000) {
        out[2] = 0;
        out[1] = sead::MathCalcCommon<f32>::atan2Idx(-mtx(2, 0), mtx(0, 0));
    } else {
        out[1] = sead::MathCalcCommon<f32>::atan2Idx(mtx(0, 2), mtx(2, 2));
        out[2] = sead::MathCalcCommon<f32>::atan2Idx(mtx(1, 0), mtx(1, 1));
    }
}

void Player::sub_71008928CC() {
    x_18(true);
    if (_cec.isOnBit(0))
        sub_710089290C();
    else
        sub_7100892A98();
}

// NON_MATCHING: the original keeps the range test as a branch (`b.lt` to a `mov w0, wzr` block); ours selects with csel
s32 Player::sub_7100892F1C() {
    if (_d24 != 0)
        return 0;
    const s64 value = _1f98;
    const s64 magnitude = value < 0 ? -value : value;
    if (magnitude >= 0xf8000001LL)
        return value < 0 ? 2 : 1;
    return 0;
}

bool Player::canUseMiphaGrace() {
    bool result = false;
    if (!_c48.isOnBit(0)) {
        if (!(StageInfo::sIsCDungeon | StageInfo::sIsAocField)) {
            if (!gdt::getFlag_HeroSoulProhibition()) {
                if (hasMiphaGraceCharges())
                    result = _1e18 <= sead::Mathf::epsilon();
            }
        }
    }
    return result;
}

bool Player::m352(sead::Vector3f* out) {
    if (!_c48.isOnBit(15))
        return false;
    *out = _2184;
    return true;
}

bool Player::isNoShieldDamageFloor() {
    switch (_1ca8) {
    case 1:
    case 3:
    case 9:
    case 13:
    case 22:
        return true;
    default:
        return false;
    }
}

// NON_MATCHING: same operations, but the original interleaves the four flag read-modify-writes
// differently (c40's store comes before c4c's, c48's last); no source order reproduces it
void Player::sub_7100881104() {
    _c44.reset(0x4001a);
    _c40.reset(0x400000);
    _c4c.reset(0x1000);
    _c48.reset(0x800);
    _1e9c = 0;
    _1ea0 = 0;
    _1ea4 = -1.0f;
    _20b4 = 0;
}

bool Player::sub_710086843C(f32 speed, Unk1* target, int limit_a, int limit_b) {
    return sub_7100857014(speed, target, limit_a, limit_b);
}

bool Player::sub_7100887AC4() {
    return getASList()->x_1(1, 1) == "GrabThrow";
}

void Player::sub_710086FAAC() {}
bool Player::hasFairy() {
    if (_c48.isOnBit(0) || dlc::isPlayingOneHitObliteratorQuest())
        return false;
    return uking::ui::PauseMenuDataMgr::instance()->hasItem("Animal_Insect_F");
}

s32 Player::sub_71008859EC() {
    const f32 base = _2038 + _201c;
    f32 value = base;
    if (_23e0.sub_7100E2F61C()->isOnBit(1))
        value = base + 2.0f;
    return std::min(value, 3.0f);
}

// NON_MATCHING: the original reads the armor effect flags with a 32-bit load (ldr w8, [x0]); ours is ldrh.
void Player::sub_710088588C() {
    getChemicalStuff();  // discarded: the call is in the original
    const f32 level = _2034 + _2018;
    f32 value = static_cast<s32>(level) == 0 ? 1.0f : 0.0f;
    if (_23e0.sub_7100E2F61C()->isOnBit(3))
        value = 0.0f;
    const f32 inverse = 1.0f - value;
    if (value == 0.0f)
        _2550._138 |= 2;
    else
        _2550._138 &= ~2;
    _2550._d0 = 1.0f - inverse;
}

// NON_MATCHING: the 32-bit flag load as in sub_710088588C, and the second 1.0f - x is scheduled after the flag update.
void Player::sub_710088592C() {
    getChemicalStuff();  // discarded: the call is in the original
    const s32 level = sub_71008859EC();
    eco::StatusEffectInfo info;
    eco::Ecosystem::instance()->getStatusEffectInfo(eco::StatusEffect_ResistElectric, level,
                                                    &info);
    const f32 value = info.val._f32;
    const f32 inverse = 1.0f - value;
    if (value == 0.0f)
        _2550._138 |= 4;
    else
        _2550._138 &= ~4;
    _2550._d4 = 1.0f - inverse;
}

// NON_MATCHING: the original returns the constant from a shared exit block (no result register)
bool Player::isEquipedDyedArmor() {
    return m278(0) > 0 || m278(1) >= 1 || m278(2) > 0;
}


f32 Player::getArmorChargeAttackAddLevel() {
    return sub_7100885630(_2044);
}

bool Player::m303() {
    if (!sub_710084BD40(this))
        return false;
    auto* info = sub_710084BE2C(this);
    return info && info->sub_71007A1F78(0x40) && _cf0.isOnBit(1);
}

// NON_MATCHING: the first bone-key address is formed after the slot-buffer loads.
void Player::sub_71008550E4() {
    auto* list = mASList;
    list->sub_710115C9E0(1);
    list->mSlots[1].sub_7101165008(_19f0[0], 3, true);
    list->mSlots[1].sub_7101165008(_19f0[2], 0, true);
    list->mSlots[1].sub_7101165008(_19f0[50], 3, true);
    list->mSlots[1].sub_7101164E38(false);
    list = mASList;
    list->sub_710115C9E0(2);
    list->mSlots[2].sub_7101165008(_19f0[0], 3, true);
    list->mSlots[2].sub_7101164E38(true);
}

// NON_MATCHING: the first bone-key address is formed after the slot-buffer loads.
void Player::x_25() {
    _c40.setBit(7);
    auto* list = mASList;
    list->sub_710115C9E0(1);
    list->mSlots[1].sub_7101165008(_19f0[0], 3, true);
    list->mSlots[1].sub_7101164E38(false);
    list = mASList;
    list->sub_710115C9E0(2);
    list->mSlots[2].sub_7101165008(_19f0[0], 3, true);
    list->mSlots[2].sub_7101165008(_19f0[2], 0, true);
    list->mSlots[2].sub_7101165008(_19f0[50], 3, true);
    list->mSlots[2].sub_7101164E38(false);
}

void Player::x_26(const char* animation, f32 value) {
    mASList->startAnimationMaybe(value, -1.0f, animation, 2, 0, true);
    mASList->sub_710115F2EC(2, 0, 1.0f);
}

void Player::x_0(const char* animation) {
    mASList->startAnimationMaybe(-1.0f, -1.0f, animation, 4, 0, true);
    mASList->sub_710115F2EC(4, 0, 1.0f);
}








void Player::x_19(f32) {
    if (!mASList->x_7(0, 1, &as::ASList::Unk2::sub_710002E82C))
        return;
    mASList->sub_710115B01C(0, 1, true);
    mASList->sub_710115F2EC(0, 0, 1.0f);
    mASList->sub_710115F2EC(0, 1, 0.0f);
}

// NON_MATCHING: the final callback setup and resource float load are scheduled differently.
void Player::x_24(f32) {
    if (!mASList->x_7(2, 0, &as::ASList::Unk2::sub_710002E82C))
        return;
    mASList->sub_710115B01C(2, 0, true);
    if (_d30 == getEquipmentTypeName(3) && _c40.isOnBit(13))
        mASList->x_3(2, 0, &as::ASList::Unk2::sub_71011631BC,
                    getParam()->getRes().mGParamList->getPlayer()->mBowSlowRateDiam.ref());
}

f32 Player::m248() {
    if (auto* weapon = sead::DynamicCast<uking::act::Weapon>(getWeapons()->getEquippedWeapon(2)))
        return weapon->sub_71002ED434();
    return 0.0f;
}

f32 Player::m301() {
    ActorLinkConstDataAccess accessor;
    auto& link = getWeapons()->mWeapons[2].link;
    if (link.hasProc())
        acquireActor(&link, &accessor);
    if (isSlowTime()) {
        f32 rate = 1.0f;
        if (isSlowTime() && _cf4.isOnBit(17))
            rate = getParam()->getRes().mGParamList->getPlayer()->mBowSlowRateDiam.ref();
        return rate * sub_71002F034C(accessor);
    }
    return sub_71002F034C(accessor);
}

bool Player::m304() {
    ActorLinkConstDataAccess accessor;
    const s32 slot = playerWeapons_return0();
    auto& link = getWeapons()->mWeapons[slot].link;
    if (!link.hasProc())
        return false;
    acquireActor(&link, &accessor);
    if (accessor.hasProc())
        return sub_71002EFEC0(accessor);
    return false;
}

f32 Player::m305() {
    ActorLinkConstDataAccess accessor;
    const s32 slot = playerWeapons_return0();
    auto& link = getWeapons()->mWeapons[slot].link;
    if (!link.hasProc())
        return 0.0f;
    acquireActor(&link, &accessor);
    if (accessor.hasProc())
        return sub_71002F000C(accessor);
    return 0.0f;
}

}  // namespace ksys::act

namespace ksys::act {

bool Player::m165(sead::BufferedSafeString* out) {
    if (sub_7100A95270(out))
        return true;
    out->copy("Empty");
    return false;
}

}  // namespace ksys::act

namespace ksys::act {

// lane4 s46: unnamed Player helpers (placeholder names).
bool Player::sub_7100849470() {
    if (uking::ui::sub_7100A991C0())
        return false;
    return _17d0->playerCheckController(28);
}

void Player::sub_7100855824() {
    mASList->sub_710115C1D0(0, 1, 0, 1);
}

void Player::sub_710085583C() {
    mASList->sub_710115F158(mASList, 1, 1, 0, 1);
    mASList->sub_710115F158(mASList, 0, 1, 0, 1);
}

void Player::sub_7100855A1C(f32 value) {
    mASList->sub_710115F2EC(1, 0, 1.0f - value);
    mASList->sub_710115F2EC(1, 1, value);
}

void Player::sub_7100855B98() {
    mASList->sub_710115F158(mASList, 1, 0, 1, 0);
}

// NON_MATCHING: the original moves the float argument back into s0 before setting the slot register of the last call.
void Player::sub_7100855CF0(f32 value) {
    mASList->sub_710115F2EC(0, 0, 1.0f - value);
    mASList->sub_710115F2EC(0, 1, value);
}

void Player::sub_7100855F80(const char* animation) {
    mASList->startAnimationMaybe(-1.0f, -1.0f, animation, 3, 0, true);
    if (!mASList->x_7(3, 2, &as::ASList::Unk2::sub_710002E82C)) {
        mASList->sub_710115F2EC(3, 0, 1.0f);
        mASList->sub_710115F2EC(3, 1, 0.0f);
        mASList->sub_710115F4A0(false, 3, 1, &as::ASList::Unk2::sub_7100507A64);
    }
}

// Placeholder name: plays FaceDefault on AS slot 3 bank 0 (clearing _c48 bit 30) and, unless bank 2 is busy,
// blends to bank 1 while it plays another face.
void Player::sub_710085603C() {
    mASList->startAnimationMaybe(-1.0f, -1.0f, "FaceDefault", 3, 0, true);
    if (_c48.isOnBit(30))
        _c48.resetBit(30);
    if (mASList->x_7(3, 2, &as::ASList::Unk2::sub_710002E82C))
        return;
    if (mASList->x_7(3, 1, &as::ASList::Unk2::sub_710002E82C) && mASList->x_1(3, 1) != "FaceDefault") {
        mASList->sub_710115F2EC(3, 0, 0.0f);
        mASList->sub_710115F2EC(3, 1, 1.0f);
        mASList->sub_710115F4A0(false, 3, 0, &as::ASList::Unk2::sub_7100507A64);
        mASList->sub_710115F4A0(true, 3, 1, &as::ASList::Unk2::sub_7100507A64);
    } else {
        mASList->sub_710115F2EC(3, 0, 1.0f);
        mASList->sub_710115F2EC(3, 1, 0.0f);
        mASList->sub_710115F4A0(false, 3, 1, &as::ASList::Unk2::sub_7100507A64);
    }
}

void Player::sub_7100856210(const char* animation) {
    mASList->startAnimationMaybe(-1.0f, -1.0f, animation, 3, 1, true);
    if (!mASList->x_7(3, 2, &as::ASList::Unk2::sub_710002E82C)) {
        mASList->sub_710115F2EC(3, 0, 0.0f);
        mASList->sub_710115F2EC(3, 1, 1.0f);
        mASList->sub_710115F4A0(false, 3, 0, &as::ASList::Unk2::sub_7100507A64);
    }
}

// Placeholder name: plays FaceDefault on AS slot 3 (also bank 0 when _c48 bit 30 was set) and resets the slot 3
// blend weights unless bank 2 is busy.
void Player::sub_71008562CC() {
    auto* list = mASList;
    list->startAnimationMaybe(-1.0f, -1.0f, "FaceDefault", 3, 1, true);
    if (_c48.isOnBit(30)) {
        _c48.resetBit(30);
        list->startAnimationMaybe(-1.0f, -1.0f, "FaceDefault", 3, 0, true);
    }
    if (!mASList->x_7(3, 2, &as::ASList::Unk2::sub_710002E82C)) {
        mASList->sub_710115F2EC(3, 0, 1.0f);
        mASList->sub_710115F2EC(3, 1, 0.0f);
        mASList->sub_710115F4A0(true, 3, 0, &as::ASList::Unk2::sub_7100507A64);
        mASList->sub_710115F4A0(false, 3, 1, &as::ASList::Unk2::sub_7100507A64);
    }
}

void Player::sub_71008563F0(const char* animation) {
    mASList->startAnimationMaybe(-1.0f, -1.0f, animation, 3, 2, true);
    mASList->sub_710115F2EC(3, 0, 0.0f);
    mASList->sub_710115F2EC(3, 1, 0.0f);
    mASList->sub_710115F2EC(3, 2, 1.0f);
    mASList->sub_710115F4A0(false, 3, 0, &as::ASList::Unk2::sub_7100507A64);
    mASList->sub_710115F4A0(false, 3, 1, &as::ASList::Unk2::sub_7100507A64);
}

// Placeholder name: stops AS slot 3 bank 2 if it is busy, then blends slot 3 to bank 1 while it plays another face
// than FaceDefault, else back to bank 0.
void Player::sub_71008564CC() {
    if (mASList->x_7(3, 2, &as::ASList::Unk2::sub_710002E82C)) {
        mASList->sub_710115B01C(3, 2, true);
        mASList->sub_710115F2EC(3, 2, 0.0f);
    }
    if (mASList->x_7(3, 1, &as::ASList::Unk2::sub_710002E82C) && mASList->x_1(3, 1) != "FaceDefault") {
        mASList->sub_710115F2EC(3, 0, 0.0f);
        mASList->sub_710115F2EC(3, 1, 1.0f);
        mASList->sub_710115F4A0(false, 3, 0, &as::ASList::Unk2::sub_7100507A64);
        mASList->sub_710115F4A0(true, 3, 1, &as::ASList::Unk2::sub_7100507A64);
    } else {
        mASList->sub_710115F2EC(3, 0, 1.0f);
        mASList->sub_710115F2EC(3, 1, 0.0f);
        mASList->sub_710115F4A0(true, 3, 0, &as::ASList::Unk2::sub_7100507A64);
        mASList->sub_710115F4A0(false, 3, 1, &as::ASList::Unk2::sub_7100507A64);
    }
}

bool Player::sub_710086D168() {
    if (getChemicalStuff())
        return getChemicalStuff()->_10c > 0.0f;
    return false;
}

bool Player::sub_71008737E4(u32 a, u32 b) {
    if (!sub_71008921A8()) {
        if (mASList->x(0x31, nullptr, a, b, &as::ASList::Unk2::sub_71011638DC, true))
            return true;
        if (mASList->x_4(a, b))
            return true;
    }
    return false;
}

f32 Player::sub_7100883698() {
    ActorLinkConstDataAccess accessor;
    auto& link = getWeapons()->mWeapons[2].link;
    if (link.hasProc())
        acquireActor(&link, &accessor);
    const bool slow = isSlowTime();
    f32 time = getParam()->getRes().mGParamList->getPlayer()->mInvalidReloadTime.ref() *
               sub_71002F0490(accessor);
    if (slow) {
        f32 divisor = 1.0f;
        if (isSlowTime() && _cf4.isOnBit(17))
            divisor = getParam()->getRes().mGParamList->getPlayer()->mBowSlowRateDiam.ref();
        time /= divisor;
    }
    return time;
}

bool Player::sub_710086CB30() {
    if (_c44.isOnBit(4))
        return false;
    if (auto* controller = getCharacterController()) {
        if (controller->_116 & 0x10)
            return false;
    }
    if (GameSceneSubsys14::instance()->sub_7100904F04())
        return false;
    if (_d11)
        return false;
    if (playerIsReloadingOrChargingOrShootingBow(this))
        return false;
    if (_c44.isOnBit(8) && !_d11)
        return false;
    if (getRootAi()->isCurrentAction("落下"))
        return true;
    return !x_44();
}

bool Player::sub_7100881078() {
    if (_cfc.isOnBit(0))
        return true;
    sead::Vector3f from = _1770;
    from.y += 0.5f;
    sead::Vector3f to = _1770;
    to.y -= 0.5f;
    return sub_710072E928(from, to, nullptr, nullptr, nullptr, 0.0f);
}

void Player::sub_7100881A90() {
    auto* controller = getCharacterController();
    if (!controller)
        return;
    f32 height = -10000.0f;
    if (m186() || x_2()) {
        if (_68f)
            height = _6f0;
    } else if (controller->_116 & 0x404) {
        height = _1770.y + controller->_210;
    }
    _20d4 = height;
}

void Player::sub_7100885820() {
    auto* chemical = getChemicalStuff();
    if (_23e0.sub_7100E2F61C()->isOnBit(4))
        chemical->_180 = 3;
    else
        chemical->_180 = s32(f32(std::min(_2030 + _2014, 2)));
}

f32 Player::sub_710086D138() {
    return _23e0.sub_7100E2F61C()->_2 & 4 ? 0.5f : 1.0f;
}

// NON_MATCHING: the original keeps the result in w19 across the checkFlag call (set to 1 after the null check, cleared if
// the flag is on); we fold it into an eor.
bool Player::sub_71008744D4() {
    auto* root = uking::Root4::instance();
    return root && !root->checkFlag(uking::Root4::FlagIdx::_1);
}

namespace {
// Indexed like Player::mResidentActors.
const char* sResidentActorNames[] = {
    "PlayerStole2",
    "WakeBoardRope",
    "Dm_Npc_RevivalFairy",
    "Dm_Npc_Gerudo_HeroSoul_Kago",
    "Dm_Npc_Goron_HeroSoul_Kago",
    "Dm_Npc_Rito_HeroSoul_Kago",
    "Dm_Npc_Zora_HeroSoul_Kago",
};
}  // namespace

void Player::initResidentActors() {
    for (s32 i = 0; i < 7; ++i) {
        auto* mgr = uking::ResidentActorMgr::instance();
        if (!mgr || mResidentActors[i].hasProc())
            continue;
        auto* actor = mgr->getActorByName(sResidentActorNames[i]);
        if (!actor)
            continue;
        mResidentActors[i].acquire(actor, false);
        // The wake board rope stays awake.
        if (i != 1)
            actor->sleep(BaseProc::SleepWakeReason::_0);
    }

    _23e0.setActor(this, ActorHeapUtil::instance()->getMemoryResidentActorHeap());

    const bool no_portable_unit = !gdt::getBoolByKey("IsGet_PortableUnit");
    x_6(3, "Armor_Default_Extra_00", no_portable_unit);
    x_6(4, "Armor_Default_Extra_01", no_portable_unit);
    x_6(5, "Item_Conductor", no_portable_unit);
}

bool Player::sub_71008738BC() {
    return getDamageMgr()->getField54() == 0x15;
}

bool Player::sub_71008738EC() {
    return getDamageMgr()->getField54() == 0x11;
}

bool Player::sub_710087391C() {
    return getDamageMgr()->getField54() == 0x14;
}

bool Player::sub_710087394C() {
    switch (getDamageMgr()->getField54()) {
    case 0:
    case 16:
    case 18:
    case 19:
    case 20:
    case 32:
    case 33:
        return true;
    default:
        return false;
    }
}

// Placeholder name: whether AS slot 0 plays a death / slip / land damage / freeze animation, or a damage one.
bool Player::sub_710087AE60() {
    return mASList->x_1(0, 0) == "Dead" || mASList->x_1(0, 0) == "MasterSwordDead" ||
           mASList->x_1(0, 0) == "SlippingDown" || mASList->x_1(0, 0) == "LandDamage" ||
           mASList->x_1(0, 0) == "Freeze" || sub_710087ACD0();
}

// Placeholder name: whether AS slot 0 plays DamageS / DamageM / DamageL.
bool Player::sub_710087ACD0() {
    return mASList->x_1(0, 0) == "DamageS" || mASList->x_1(0, 0) == "DamageM" ||
           mASList->x_1(0, 0) == "DamageL";
}

// Placeholder name: whether AS slot 0 plays Push or PushRoll.
bool Player::sub_710087B0CC() {
    return mASList->x_1(0, 0) == "Push" || mASList->x_1(0, 0) == "PushRoll";
}

// Placeholder name: whether AS slot 1 plays a horse call (HorseCall / CallComeon / CallStay).
bool Player::sub_710087B500() {
    return mASList->x_1(1, 1) == "HorseCall" || mASList->x_1(1, 1) == "CallComeon" ||
           mASList->x_1(1, 1) == "CallStay";
}

void Player::sub_710087B6A8() {
    if (gdt::getFlag_Fire_Relic_YunboStopGo(false)) {
        if (gdt::getFlag_Fire_Relic_NPC020_Follow(false))
            x_23("CallStay", false, -1.0f);
        else
            x_23("CallComeon", false, -1.0f);
    } else {
        x_23("HorseCall", false, -1.0f);
    }
}

bool Player::sub_710088D484() {
    if (_17d0->controllerCheckPressedMaybe(9))
        return true;
    if (!(_209c > 0.05f))
        return false;
    if (!_17d0->playerCheckController(9))
        return false;
    if (_c44.isOnBit(12))
        return false;
    if (isRidingHorse())
        return false;
    return !_cfc.isOnBit(5);
}

bool Player::sub_710088D50C() {
    if (!sub_7100848F40() && _17d0->controllerCheckPressedMaybe(9))
        return true;
    return _c40.isOnBit(1) && _20bc.value != 0.0f;
}

// NON_MATCHING: the original emits the `false` result block before the attention test (block layout only).
// NON_MATCHING: argument copy order in the prologue, the angle's stack slot and the scheduling of the gravity
// z scale.
void Player::sub_7100894384(f32 height, const sead::Vector3f& target, f32 a3, f32 a4) {
    f32 speed;
    f32 time;
    sead::Vector3f velocity = sead::Vector3f::zero;
    if (auto* controller = getCharacterController())
        controller->sub_7100F62640(height, &velocity);

    sead::Vector3f attention_pos = sead::Vector3f::zero;
    if (!Attention::instance()->sub_7100D742E8(1)) {
        ActorLinkConstDataAccess accessor;
        if (Attention::instance()->x_0(1, 0, &accessor))
            accessor.getActorMtx().getTranslation(attention_pos);
    }

    const f32 dx = attention_pos.x - target.x;
    const f32 dz = attention_pos.z - target.z;
    const u32 angle = sead::Mathf::atan2Idx(dx, dz);
    const f32 dist = sead::Mathf::min(sead::Mathf::sqrt(dx * dx + dz * dz), a4);
    util::sub_71011EEEE0(&attention_pos, angle, -dist);

    sead::Vector3f gravity = getGravity(this);
    gravity *= 1.0f / 900.0f;
    sub_710072CF4C(velocity.y / 30.0f, &speed, &time, &target, &attention_pos, &gravity);
    if (speed > a3)
        speed = a3;
    _20bc.value = speed;
    _20bc.prev_value = speed;
}

bool Player::sub_7100894540() {
    return sub_71008921A8() && m224() && !Attention::instance()->sub_7100D742E8(3);
}

void Player::sub_710087CF54() {
    auto* controller = getCharacterController();
    if (!controller)
        return;

    auto* unk = _1870->_c8;
    if (!unk)
        return;
    if ((unk->_1f0 & 0x1002) != 2)
        return;
    if (controller->isBit2Of116())
        return;

    _1cbc = 10;
    _2160 = unk->_1a8;
    _1c88 = x_5();
}

// NON_MATCHING: the constant 0x19f4 is built in w8 instead of w9 (register allocation only).
void Player::sub_71008695A8(const sead::Vector3f& offset) {
    sead::Matrix34f mtx;
    mASList->_b0->sub_7100D68464(&mtx, &_19f0[1]);
    sead::Vector3f translation;
    mtx.getTranslation(translation);
    translation += offset;
    mtx.setTranslation(translation);
    mASList->_b0->sub_7100D68544(&mtx, &_19f0[1]);
}

}  // namespace ksys::act

namespace ksys::act {

void Player::initControllerMaybe() {
    _17d0 = sead::DynamicCast<uking::Unk_710246d058>(
        uking::MaskController::instance()->getController(uking::MaskController::ControllerIdx::_1));
}

void Player::sub_710087B444() {
    if (mASList->x_7(0, 1, &as::ASList::Unk2::sub_710002E82C))
        return;

    if (m199() && ((!m359() && m179() && !_c40.isOnBit(30)) || (_c44.isOnBit(8) && _d11 == 0)))
        sub_7100855BB4("SquatBowTurn", false, -1.0f);
    else
        sub_7100855BB4("TurnAttention", false, -1.0f);
}

// NON_MATCHING: the original computes the sin/cos table entry address once; ours recomputes it for the sine.
void Player::sub_710086989C(const Unk1& angle, u8* out) {
    const f32 c = sead::Mathf::cosIdx(angle.value);
    if (c >= 0.866f) {
        *out = 0;
    } else if (c < -0.866f) {
        *out = 1;
    } else {
        const f32 s = sead::Mathf::sinIdx(angle.value);
        if (s > 0.0f)
            *out = 2;
        else if (s < 0.0f)
            *out = 3;
    }
}

Player::Unk1 Player::sub_710087CEEC(const Unk1& angle) {
    const Unk1 diff = util::angleDiff(_1c8c, angle);
    const f32 c = sead::Mathf::cosIdx(diff.value);
    return Unk1(util::sUnk_7101EC6BA0 & s64(-(static_cast<f32>(_1c90) * c)));
}

// Whether the current slot 1 animation is a rune item start (Magnesis or the common one) that has not ended.
// NON_MATCHING: the original sets the result to 1 before the x_4 call and branches on it; ours uses eor.
bool Player::x_32() {
    if (mASList->x_1(1, 1) == "ItemMagneCatchStart" || mASList->x_1(1, 1) == "ItemCommonStart")
        return !mASList->x_4(1, 1);
    return false;
}

void Player::sub_71008573CC() {
    const auto& key = _19f0[47];
    sead::Matrix34f mtx;
    mModel->getUnits().unsafeAt(key.model_unit_index)->mModelUnit->getBoneWorldMatrix(&mtx, key.bone_index);
    mtx.getTranslation(_1794);
    if (m186()) {
        sead::Vector3f dir;
        _1b18.getBase(dir, 2);
        dir.normalize();
        _1794 -= dir * 0.3f;
    }
}

void Player::x_36() {
    if (x_32() || m225() || m226())
        return;
    auto* rune_mgr = uking::RuneMgr::instance();
    if (!rune_mgr)
        return;
    if (!rune_mgr->isSelectedRune(2) && !rune_mgr->isSelectedRune(3) && !rune_mgr->isSelectedRune(4) &&
        !rune_mgr->isSelectedRune(6) && !rune_mgr->isSelectedRune(7)) {
        return;
    }
    if (mASList->x_1(1, 1) == "ItemCommonReady")
        return;
    x_23("ItemCommonReady", false, -1.0f);
    _c44.setBit(12);
}

bool Player::x_52() {
    return mASList->x_1(1, 1) == "GrabWait" || mASList->x_1(1, 1) == "GrabPouchUpper" ||
           mASList->x_1(1, 1) == "GrabThrowCharge";
}

void Player::sub_7100892F5C(as::ASList::Unk4* query) {
    s32 direction;
    if (query->name == "Upper")
        direction = 0;
    else if (query->name == "Lower")
        direction = 1;
    else if (query->name == "Left")
        direction = 2;
    else if (query->name == "Right")
        direction = 3;
    else
        direction = -1;
    _d20 = direction;
}

void Player::x_7() {
    if (_d30 != getEquipmentTypeName(1) && (_d30 != getEquipmentTypeName(0) || _c40.isOnBit(3)))
        x_8(false, false);
    getWeapons()->mWeapons[1]._10 = false;
    _c40.setBit(3);
    _c44.resetBit(10);
    snd::Unk_7102502138::instance()->sub_710103B430(true);
}

// NON_MATCHING: the matrix product is scheduled / allocated differently (same operations).
void Player::sub_7100868220(f32 angle) {
    sead::Vector3f dir;
    _1b18.getBase(dir, 2);
    dir.normalize();
    sead::Matrix34f rot;
    rot.makeR({0.0f, angle - std::atan2(dir.x, dir.z), 0.0f});
    _1b18.setMul(rot, _1b18);
}

// NON_MATCHING: register allocation (the original keeps &_23e0 and &_23e0._138 in separate registers).
void Player::getEnemyTeam(sead::BufferedSafeString* out) {
    out->copy(_23e0._138);
    if (*out == "Stalfos" || *out == "PhantomGanon") {
        if (!_23e0.hasSeriesCompBonus())
            out->clear();
    }
}

bool Player::x_17() {
    if (isRidingHorse())
        return mASList->x_1(1, 1) == "CutChargeWaitHorseRide";
    return mASList->x_1(0, 0) == "CutChargeWait" || mASList->x_1(0, 0) == "CutChargeMove" ||
           mASList->x_1(0, 0) == "CutChargeLswordSpin";
}

// NON_MATCHING: the original loads each GParam rate unconditionally and selects with fcsel / csel (no branches).
void Player::updateSupportTimerRates() {
    const bool in_castle = gdt::getFlag_IsInHyruleCastleArea();
    const bool revali_plus = hasRevaliGalePlus();
    const bool daruk_plus = hasDarukProtectionPlus();
    const bool urbosa_plus = hasUrbosaFuryPlus();
    const bool mipha_plus = hasMiphaGracePlus();

    const f32 wind_plus = in_castle ? uking::sUnk_7101e7c280 : uking::sUnk_7101e7c290;
    const f32 fire_plus = in_castle ? uking::sUnk_7101e7c284 : uking::sUnk_7101e7c294;
    const f32 electric_plus = in_castle ? uking::sUnk_7101e7c288 : uking::sUnk_7101e7c298;
    const f32 water_plus = in_castle ? uking::sUnk_7101e7c28c : uking::sUnk_7101e7c29c;

    f32 rate = in_castle ? -getParam()->getRes().mGParamList->getPlayer()->mWindSupportTimerRate.ref() : -1.0f;
    _1dfc = revali_plus ? -wind_plus : rate;
    rate = in_castle ? -getParam()->getRes().mGParamList->getPlayer()->mFireSupportTimerRate.ref() : -1.0f;
    _1e08 = daruk_plus ? -fire_plus : rate;
    rate = in_castle ? -getParam()->getRes().mGParamList->getPlayer()->mElectricSupportTimerRate.ref() : -1.0f;
    _1e14 = urbosa_plus ? -electric_plus : rate;
    rate = in_castle ? -getParam()->getRes().mGParamList->getPlayer()->mWaterSupportTimerRate.ref() : -1.0f;
    _1e20 = mipha_plus ? -water_plus : rate;
}

void Player::sub_7100887554() {}

}  // namespace ksys::act
