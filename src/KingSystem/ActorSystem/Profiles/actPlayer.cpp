#include "KingSystem/ActorSystem/Profiles/actPlayer.h"
#include <basis/seadNew.h>
#include "Game/AI/aiUnk_71007377D4.h"
#include "Game/Actor/actWeapon.h"
#include "Game/E3Mgr.h"
#include "Game/gameUnk_710246d058.h"
#include "Game/UI/uiUtils.h"
#include "Game/gameUnk_71024739d0.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/ActorSystem/actChemical.h"
#include "KingSystem/Physics/RigidBody/Shape/Sphere/physSphereRigidBody.h"
#include "KingSystem/ActorSystem/actPlayerInfo.h"
#include "KingSystem/Resource/Actor/resResourceGParamList.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectPlayer.h"
#include "KingSystem/GameData/gdtCommonFlagsUtils.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"

namespace ksys::act {

BaseProc* Player::construct(const CreateArg& arg, sead::Heap* heap) {
    return new (heap, std::nothrow) Player(arg);
}

// NON_MATCHING: members are not declared yet
Player::~Player() = default;

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

void Player::m277(ActorConstDataAccess* accessor, int idx) {
    acquireActor(&_23e0.getPartsLink(idx), accessor);
}

Actor* Player::m382() {
    return sead::DynamicCast<Actor>(
        PlayerInfo::instance()->getHorseLink().getProc(nullptr, nullptr));
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

bool Player::isRevivalFairyActive(ActorConstDataAccess* accessor) {
    if (acquireActor(&_2c48, accessor) && accessor->isStateCalc())
        return true;
    return false;
}

bool Player::isZoraHeroActive(ActorConstDataAccess* accessor) {
    if (acquireActor(&_2c88, accessor) && accessor->isStateCalc())
        return true;
    return false;
}

f32 Player::getNoDeathDamage() {
    const auto* param = getParam()->getRes().mGParamList->getPlayer();
    const s32 base = param->mNoDeathDamageBase.ref();
    const s32 add = param->mNoDeathDamageAdd.ref();
    return base + PlayerInfo::instance()->getMaxLifeFromPlayerActor() * add / 4;
}

bool Player::m373() {
    return PlayerInfo::instance()->getStaminaCurrentMax() + _2000 <
           getParam()->getRes().mGParamList->getPlayer()->mEnergyTiredValue.ref();
}

void Player::m372() {
    if (_c44.isOnBit(20)) {
        if (PlayerInfo::instance()->getStaminaCurrentMax() !=
            PlayerInfo::instance()->getMaxStaminaFromPlayerActor())
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

bool Player::m225() {
    return mASList->x_1(2, 0) == "WeaponEquipOn" || mASList->x_1(2, 0) == "WeaponEquipOff" ||
           mASList->x_1(2, 0) == "WeaponEquipNG";
}

bool Player::m226() {
    return mASList->x_1(2, 0) == "ItemEquipBoth" || mASList->x_1(2, 0) == "ItemEquipLeftOn" ||
           mASList->x_1(2, 0) == "ItemEquipLeftOff" || mASList->x_1(2, 0) == "ItemEquipRight" ||
           mASList->x_1(1, 1) == "ItemBombReady";
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

bool Player::m234() {
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

Actor* Player::getAttachedTargetActor2() {
    return _1870;
}

Actor* Player::getAttachedTargetActor() {
    return _1870;
}

s32 Player::m312(int idx) {
    return _19f0[idx];
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

bool Player::sub_710087F360(const sead::Vector3f& start, const sead::Vector3f& end,
                            sead::Vector3f* hit_pos, sead::Vector3f* hit_normal) {
    return sub_710072E928(start, end, hit_pos, hit_normal, nullptr, 0.0f);
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

// NON_MATCHING: operand order of the XZ length addition (z*z + x*x in the original)
Player::Unk1 Player::x_5() {
    sead::Vector3f dir;
    _1b18.getBase(dir, 2);
    dir.normalize();
    if (sead::Vector2f(dir.x, dir.z).length() == 0.0f) {
        _1b18.getBase(dir, 1);
        dir.normalize();
    }
    return Unk1(sead::Mathf::atan2Idx(dir.x, dir.z));
}

}  // namespace ksys::act

namespace ksys::act {

// NON_MATCHING: x_5() gets inlined here (it is defined in this file; the original calls it), and the
// original selects the stored speed with an integer csel
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
    if (auto* info = PlayerInfo::instance())
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
    ActorConstDataAccess accessor;
    const s32 slot = playerWeapons_return0();
    auto& link = getWeapons()->mWeapons[slot].link;
    if (!link.hasProc())
        return false;
    acquireActor(&link, &accessor);
    if (accessor.hasProc())
        return accessor.getName() == "Weapon_Sword_070";
    return false;
}

void Player::x_40() {
    _1d6c = 1.0f;
    _c40.reset(0x1200000);
    _1d64 = 0.0f;
    _1d68 = 0.0f;
    _1f8c = 0;
    _1f84 = 0;
    if (_c44.isOnBit(8)) {
        if (mASList->x_1(1, 1) != "WeaponThrow") {
            _c44.resetBit(8);
            x_18(true);
        }
    }
}

// NON_MATCHING: the inlined copy of x_40 has its stores scheduled differently (the original keeps the order of the
// out-of-line x_40)
void Player::x_16() {
    _c40.resetBit(24);
    if (x_17())
        x_18(true);
    x_40();
    x_19(-1.0f);
}

void Player::nullsub_2601() {}

void Player::m88() {
    mPreviousPos = _17a0;
}

bool Player::m217() {
    return _2558.isOn(0x108);
}

bool Player::m151(u16 bit) {
    return _2558.isOnBit(bit);
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

bool Player::m295() {
    return sub_7100892724();
}

bool Player::m296() {
    return sub_7100892824();
}

bool Player::m298(int a1) {
    return sub_71008923B0(a1);
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

}  // namespace ksys::act
