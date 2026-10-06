#include "KingSystem/ActorSystem/Profiles/actPlayerBase.h"
#include "KingSystem/ActorSystem/Awareness/actAwarenessInstance.h"
#include <gsys/gsysModel.h>
#include "Game/Actor/actHorseRideInfo.h"
#include "Game/Actor/actWeapon.h"
#include "Game/Damage/dmgDamageManagerBase.h"
#include "KingSystem/ActorSystem/actChemical.h"
#include "Game/gameRuneMgr.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "Game/gameSceneSubsysMisc.h"
#include "Game/gameUnk_710246d058.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "KingSystem/ActorSystem/actBaseProcMgr.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/ActorSystem/actAiRoot.h"
#include "KingSystem/ActorSystem/actPlayerInfo.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/System/VFR.h"
#include <cstring>
#include <mc/seadCoreInfo.h>
#include "KingSystem/ActorSystem/actUnk_71024ef4e8.h"
#include "KingSystem/Resource/Actor/resResourceGParamList.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectPlayer.h"

bool eventMgrHasActiveEvent();

// Declared only: Motorcycle queries through the actor accessor.
bool sub_71002C802C(const ksys::act::ActorConstDataAccess& accessor);
bool sub_71002C8330(const ksys::act::ActorConstDataAccess& accessor, sead::Vector3f* out);

namespace ksys::act {

void PlayerBase::x_1(bool on) {
    if (_548)
        _548->_18._50 = on;
}

s32 PlayerBase::getX() {
    if (auto* chemical = getChemicalStuff())
        return chemical->_180;
    return 0;
}

bool PlayerBase::m223(sead::Vector3f* out) {
    ActorConstDataAccess accessor;
    return acquireActor(&PlayerInfo::instance()->getHorseLink(), &accessor) &&
           sub_71002C802C(accessor) && sub_71002C8330(accessor, out);
}

bool PlayerBase::checkCanUseCamera() {
    if (m200() || _cec.isOnBit(31) || _cf0.isOn(0x02020000) || isRidingHorse() || m193() ||
        m188() || m186() || m187() || _cec.isOnBit(19) || m194() || _cf0.isOnBit(23) ||
        eventMgrHasActiveEvent() || m226() || _cf4.isOnBit(2) || _c44.isOnBit(21) ||
        _cec.isOnBit(5))
        return false;
    return !m199() || !_c50.isOnBit(9);
}

namespace {
const sead::SafeString sEquipmentTypeNames[8] = {
    "None", "Sword", "Shield", "Bow", "Bomb", "Item_Magnetglove", "ShiekahStone", "Unequip"};
}  // namespace

// NON_MATCHING: Compiler folds table addressing into fewer instructions.
const sead::SafeString& PlayerBase::getEquipmentTypeName(u32 type) const {
    return sEquipmentTypeNames[type];
}

// NON_MATCHING: The original addresses this entry through a larger merged global.
bool PlayerBase::m179() {
    return _d30 == sEquipmentTypeNames[3];
}

void PlayerLink::m379(sead::BufferedSafeString* out) {}

void PlayerLink::m380(sead::BufferedSafeString* out) {}

void PlayerLink::m381(sead::BufferedSafeString* out) {}

Actor* PlayerLink::m382() {
    return nullptr;
}

Unk_71024ef4e8* PlayerBase::getAttachedTargetActor2() {
    return nullptr;
}

Unk_71024ef4e8* PlayerBase::getAttachedTargetActor() {
    return nullptr;
}

void* PlayerBase::m314() {
    return &_e60;
}

gsys::BoneAccessKey PlayerBase::m312(int idx) {
    return mModel->searchBone("Root");
}

bool PlayerBase::x_2() {
    if (getAttachedTargetActor()->_110.isOnBit(6))
        return true;
    return getAttachedTargetActor()->_110.isOnBit(9);
}

bool PlayerBase::isSlowTime() const {
    return VFR::instance()->getTimeSpeedMultiplierValue(0) < 1.0f;
}

bool PlayerBase::x_50() {
    return false;
}

bool PlayerBase::runeMgrCheckCanUseRoundBomb() {
    return uking::RuneMgr::instance()->checkIsSelectedRuneAndCanUse(0, this);
}

bool PlayerBase::runeMgrCheckCanUseSquareBomb() {
    return uking::RuneMgr::instance()->checkIsSelectedRuneAndCanUse(1, this);
}

bool PlayerBase::runeMgrCheckCanUseMagnesis() {
    return uking::RuneMgr::instance()->checkIsSelectedRuneAndCanUse(2, this);
}

bool PlayerBase::runeMgrCheckCanUseCryonis() {
    return uking::RuneMgr::instance()->checkIsSelectedRuneAndCanUse(4, this);
}

bool PlayerBase::runeMgrCheckCanUseCamera() {
    return uking::RuneMgr::instance()->checkIsSelectedRuneAndCanUse(5, this);
}

bool PlayerBase::runeMgrCheckIsCameraSelected() {
    auto* mgr = uking::RuneMgr::instance();
    if (mgr->_90 & 0x10)
        return mgr->isSelectedRune(5);
    return false;
}

void PlayerBase::m92(phys::RigidBody* body) {
    sead::Vector3f position;
    body->getPosition(&position);
}

f32 PlayerBase::m317() {
    if (auto* chemical = getChemicalStuff())
        return chemical->_19c;
    return 0.0f;
}

// NON_MATCHING: the original calls the damage manager slot without a tail call and zero-extends the result to 64 bits
// (`and x0, x0, #0xffffffff`; the return type is probably wider than u32).
u32 PlayerBase::getDeathReason() {
    if (auto* manager = getDamageMgr())
        return manager->getFlags2();
    return 0;
}

bool PlayerBase::sub_710084A6B8() {
    return (uking::RuneMgr::instance()->_90 >> 5) & 1;
}

bool PlayerBase::m202() {
    if (_cf0.isOnBit(19))
        return true;
    return (uking::RuneMgr::instance()->_90 >> 5) & 1;
}

bool PlayerBase::isRidingHorse() {
    auto* info = getPlayerRideInfo();
    return info && (info->_30 & 1);
}

bool PlayerBase::m239() {
    if (_c50.isOnBit(17) || m202() || m292())
        return false;
    return _17d0->controllerCheckPressedMaybe(26);
}

bool PlayerBase::m240() {
    if (m292() || _17d0->isHold(0xd0000) || m225())
        return false;
    return _17d0->controllerCheckPressedMaybe(27);
}

bool PlayerBase::x_48() {
    auto* info = getPlayerRideInfo();
    if (info && (info->_30 & 1)) {
        ActorConstDataAccess accessor;
        if (acquireActor(&info->_18, &accessor))
            return accessor.sub_7100D14598() == Unk_7100d14598::_11;
    }
    return false;
}

bool PlayerBase::checkCanUseMagnesis() {
    if (GameSceneSubsys5::instance()->sub_71009059D4() || m193())
        return false;
    return checkCanUseRuneCommon();
}

bool PlayerBase::m237() {
    return _17d0->controllerCheckPressedMaybe(2);
}

bool PlayerBase::m238() {
    return _17d0->playerCheckController(2);
}

sead::Vector3f* PlayerBase::m357() {
    return &_1770;
}

SeadController* PlayerBase::m358() {
    return _17d0;
}


// NON_MATCHING: most member types are still unknown (placeholders)
PlayerBase::~PlayerBase() = default;

// NON_MATCHING: the original tail-calls CriticalSection::unlock (the locked part was probably an inlined helper)
void PlayerBase::m266(const sead::SafeString& slot, int frames) {
    switchEquipment(slot, frames);
    setC98Locked(0x20);
}

void PlayerBase::getActorDirect() {}

void PlayerBase::m308() {
    const auto lock = sead::makeScopedLock(_1478);
    _14b8 = true;
}

void PlayerBase::setExtraLife(s32 extra_life, f32 x) {
    const auto lock = sead::makeScopedLock(_1140);
    _1198 = extra_life;
    _119c = x;
}

void PlayerBase::addExtraStamina(f32 x, f32 y) {
    const auto lock = sead::makeScopedLock(_1140);
    _11a0 = x;
    _11a4 = y;
}

void PlayerBase::setStaminaDelta(f32 delta) {
    _e7c[sead::CoreInfo::getCurrentCoreId()] += delta;
}

void PlayerBase::addLifeDelta(s32 delta) {
    _e70[sead::CoreInfo::getCurrentCoreId()] += delta;
}

void PlayerBase::sub_710084AC68() {
    const f32 max_life = PlayerInfo::instance()->getMaxLifeFromPlayerActor();
    auto& delta = _e70[sead::CoreInfo::getCurrentCoreId()];
    delta = s32(max_life + f32(delta));
}

void PlayerBase::sub_710084AE78() {
    const f32 max_stamina = PlayerInfo::instance()->getMaxStaminaFromPlayerActor();
    _e7c[sead::CoreInfo::getCurrentCoreId()] += max_stamina;
}

void PlayerBase::sub_710084AA0C() {
    const auto lock = sead::makeScopedLock(_1238);
    _1278 = false;
    _1280.reset();
    _1290 = "";
}

void PlayerBase::setItemVel(s32 type, f32 vel) {
    const auto lock = sead::makeScopedLock(_1140);
    _1180 = f32(type);
    _1184 = vel;
}

void PlayerBase::setItemSwimVel(s32 type, f32 vel) {
    const auto lock = sead::makeScopedLock(_1140);
    _1188 = f32(type);
    _118c = vel;
}

void PlayerBase::sub_710084B6D4(s32 type, f32 vel) {
    const auto lock = sead::makeScopedLock(_1140);
    _1190 = f32(type);
    _1194 = vel;
}

void PlayerBase::sub_710084B7C0(s32 type, f32 value) {
    const auto lock = sead::makeScopedLock(_1140);
    _11a8[0].type = type;
    _11a8[0].value = value;
}

void PlayerBase::sub_710084B810(s32 type, f32 value) {
    const auto lock = sead::makeScopedLock(_1140);
    _11a8[1].type = type;
    _11a8[1].value = value;
}

void PlayerBase::sub_710084B860(s32 type, f32 value) {
    const auto lock = sead::makeScopedLock(_1140);
    _11a8[2].type = type;
    _11a8[2].value = value;
}

void PlayerBase::sub_710084B8B0(s32 type, f32 value) {
    const auto lock = sead::makeScopedLock(_1140);
    _11a8[3].type = type;
    _11a8[3].value = value;
}

void PlayerBase::sub_710084B900(s32 type, f32 value) {
    const auto lock = sead::makeScopedLock(_1140);
    _11a8[4].type = type;
    _11a8[4].value = value;
}

void PlayerBase::sub_710084B950(s32 type, f32 value) {
    const auto lock = sead::makeScopedLock(_1140);
    _11a8[5].type = type;
    _11a8[5].value = value;
}

void PlayerBase::sub_710084B9A0(s32 type, f32 value) {
    const auto lock = sead::makeScopedLock(_1140);
    _11a8[6].type = type;
    _11a8[6].value = value;
}

void PlayerBase::sub_710084B9F0(s32 type, f32 value) {
    const auto lock = sead::makeScopedLock(_1140);
    _11a8[7].type = type;
    _11a8[7].value = value;
}

void PlayerBase::sub_710084BA40(s32 type, f32 value) {
    const auto lock = sead::makeScopedLock(_1140);
    _11a8[8].type = type;
    _11a8[8].value = value;
}

void PlayerBase::x_12(bool keep_extra) {
    const auto lock = sead::makeScopedLock(_1140);
    _1180 = 0;
    _1184 = 0;
    _1188 = 0;
    _118c = 0;
    _1190 = 0;
    _1194 = 0;
    if (!keep_extra) {
        _1198 = 0;
        _119c = 0;
        _11a0 = 0;
        _11a4 = 0;
    }
    memset(_11a8, 0, 0x48);
}

// NON_MATCHING: the original keeps the full word load of _c40 (ldr + tbz #14) where we narrow it to a byte load
bool PlayerBase::sub_710084AA9C(BaseProcLink* out) {
    if (out && _c40.isOnBit(14)) {
        *out = _1280;
        return true;
    }
    return false;
}

void PlayerBase::sub_710084AEF8() {
    auto* info = PlayerInfo::instance();
    info->setStaminaCurrentMax(info->getMaxStaminaFromPlayerActor());
}

void PlayerBase::setNewPlayerMtx(const sead::Matrix34f& mtx) {
    const auto lock = sead::makeScopedLock(_1700);
    _1740 = mtx;
    const auto lock2 = sead::makeScopedLock(_ca0);
    _ce0.set(0x80);
}

sead::Vector3f& PlayerBase::getPlayerPosForPostCalc() {
    return PlayerInfo::instance()->getPlayerPosForPostCalc();
}

PlayerBase* PlayerBase::getPlayer() {
    BaseProcMgr::instance()->isAccessingProcSafe(this, nullptr);
    return this;
}

bool PlayerBase::checkCanUseMotorcycle() {
    if (m193())
        return false;
    return checkCanUseRuneCommon();
}

bool PlayerBase::checkCanUseAmiibo() {
    if (m193())
        return false;
    return checkCanUseRuneCommon();
}

bool PlayerBase::x_51() {
    return _17d0->controllerCheckPressedMaybe(3);
}

bool PlayerBase::getActorViaAccessor(ActorLinkConstDataAccess* accessor) {
    return accessor->acquire(this);
}

}  // namespace ksys::act

namespace ksys::act::acc {

bool PlayerBase::x_3() const {
    if (!getPlayerBase())
        return false;
    if (!eventMgrHasActiveEvent())
        return false;
    auto* info = ksys::act::PlayerInfo::instance();
    info->setStaminaCurrentMax(info->getMaxStaminaFromPlayerActor());
    return true;
}

bool PlayerBase::x_4() const {
    if (!getPlayerBase())
        return false;
    if (!eventMgrHasActiveEvent())
        return false;
    auto* info = ksys::act::PlayerInfo::instance();
    info->setLifeForPlayerActor(info->getMaxLifeFromPlayerActor());
    return true;
}

bool PlayerBase::isMainWeaponHitEnemy() const {
    auto* player = getPlayerBase();
    if (!player)
        return false;
    debugLog(2, "isMainWeaponHitEnemy");
    Weapon weapon;
    auto& link = player->getWeapons()->mWeapons[0].link;
    if (link.hasProc())
        act::acquireActor(&link, &weapon);
    return weapon.isHitEnemy();
}

bool PlayerBase::getPlayerFromPlayerInfo() {
    auto* info = PlayerInfo::instance();
    if (!info)
        return false;
    act::acquireActor(&info->getPlayerLink(), this);
    return hasProc();
}

static BaseProc* getProcIfActor(BaseProc* proc) {
    if (proc && sead::IsDerivedFrom<Actor>(proc))
        return proc;
    return nullptr;
}

act::PlayerBase* PlayerBase::getPlayerBase() const {
    auto* actor = static_cast<Actor*>(getProcIfActor(mProc));
    return sead::DynamicCast<act::PlayerBase>(actor);
}

void PlayerBase::x_0(BaseProc* proc) const {
    if (auto* player = getPlayerBase()) {
        const auto lock = sead::makeScopedLock(player->_1530);
        player->_1570.acquire(proc, false);
    }
}

void PlayerBase::x_1(bool a, const sead::SafeString& name, BaseProc* proc) const {
    if (auto* player = getPlayerBase()) {
        const auto lock = sead::makeScopedLock(player->_1238);
        player->_1278 = a;
        player->_1280.acquire(proc, false);
        player->_1290 = name;
    }
}

void PlayerBase::setExtraEnergy(f32 energy) const {
    if (auto* player = getPlayerBase())
        player->addExtraStamina(energy, 0.0f);
}

void PlayerBase::setExtraLife(f32 life) const {
    if (auto* player = getPlayerBase())
        player->setExtraLife(life, 0.0f);
}

void PlayerBase::setMtx(const sead::Matrix34f& mtx) const {
    if (auto* player = getPlayerBase()) {
        const auto lock = sead::makeScopedLock(player->_1700);
        player->_1740 = mtx;
        const auto lock2 = sead::makeScopedLock(player->_ca0);
        player->_ce0.set(0x80);
    }
}

bool PlayerBase::x_2() const {
    if (auto* player = getPlayerBase()) {
        player->m323();
        return true;
    }
    return false;
}

// NON_MATCHING: the original calls the virtual operator=(const SafeStringBase&); lib/sead's
// BufferedSafeStringBase has no copy assignment forwarding to it, so ours is the implicit memberwise one
bool PlayerBase::getLastDamageAttacker(sead::BufferedSafeString* name) const {
    auto* player = getPlayerBase();
    if (!player)
        return false;
    debugLog(0, "getLastDamageAttacker");
    *name = player->_da0;
    return true;
}

bool PlayerBase::setRestartBuf(const sead::Vector3f& pos, f32 angle) const {
    auto* player = getPlayerBase();
    if (!player)
        return false;
    debugLog(1, "setRestartBuf");
    const auto lock = sead::makeScopedLock(player->_1658);
    player->_169c = pos;
    player->_16a8 = angle;
    player->_1698 = true;
    return true;
}

bool PlayerBase::isRidingThisSandSeal(BaseProc* proc) const {
    if (auto* player = getPlayerBase())
        return player->_e98.hasProcById(proc);
    return false;
}

bool PlayerBase::getSandSealActor(ActorConstDataAccess* accessor) const {
    auto* player = getPlayerBase();
    if (player && player->_e98.hasProcInCalcState())
        return act::acquireActor(&player->_e98, accessor);
    return false;
}

bool PlayerBase::getAttachedTargetActor(ActorConstDataAccess* accessor) const {
    auto* player = getPlayerBase();
    if (!player)
        return false;
    debugLog(0, "getAttachedTargetActor");
    if (!accessor)
        return false;
    auto* target = player->getAttachedTargetActor();
    if (!target)
        return false;
    auto* info = target->mAttachInfo;
    if (!info)
        return false;
    act::acquireActor(&info->mTargetLink, accessor);
    return info->mTargetLink.hasProc();
}

bool PlayerBase::reserveParashawlStart() const {
    auto* player = getPlayerBase();
    if (!player)
        return false;
    const auto lock = sead::makeScopedLock(player->_1358);
    player->_1398 = true;
    return true;
}

const sead::Vector3f& PlayerBase::getPosCopyMagnesis() const {
    if (auto* player = getPlayerBase())
        return *player->getPosCopyMagnesis();
    return sead::Vector3f::zero;
}

const sead::Vector3f& PlayerBase::getPosCopyMagnesis2() const {
    if (auto* player = getPlayerBase())
        return *player->m244();
    return sead::Vector3f::zero;
}

void PlayerBase::getMaskType(sead::BufferedSafeString* out) const {
    if (auto* player = getPlayerBase())
        player->getMaskType(out);
    else
        *out = sead::SafeString::cEmptyString;
}

void PlayerBase::getArmorSeriesType(sead::BufferedSafeString* out) const {
    if (auto* player = getPlayerBase())
        player->getArmorSeriesType(out);
    else
        *out = sead::SafeString::cEmptyString;
}

void PlayerBase::getEnemyTeam(sead::BufferedSafeString* out) const {
    if (auto* player = getPlayerBase())
        player->getEnemyTeam(out);
    else
        *out = sead::SafeString::cEmptyString;
}

bool PlayerBase::ArmorSeriesTypeStuff() const {
    if (auto* player = getPlayerBase())
        return player->ArmorSeriesTypeStuff();
    return false;
}

bool PlayerBase::armorSeriesStuff(u8 idx, const sead::SafeString& series) const {
    if (auto* player = getPlayerBase())
        return player->armorSeriesStuff(idx, series);
    return false;
}

bool PlayerBase::isEquipedDyedArmor() const {
    if (auto* player = getPlayerBase())
        return player->isEquipedDyedArmor();
    return false;
}

s32 PlayerBase::getArmorDyeStuff() const {
    if (auto* player = getPlayerBase())
        return player->getArmorDyeStuff();
    return 0;
}

bool PlayerBase::m280() const {
    if (auto* player = getPlayerBase())
        return player->m280();
    return false;
}

bool PlayerBase::x_14() const {
    auto* player = getPlayerBase();
    if (!player)
        return false;
    return !player->m359() && player->m179() && !player->_c40.isOnBit(30);
}

bool PlayerBase::m328() const {
    if (auto* player = getPlayerBase())
        return player->m328();
    return false;
}

bool PlayerBase::x_15() const {
    if (auto* player = getPlayerBase())
        return player->_cf0.isOnBit(31);
    return false;
}

bool PlayerBase::x_16() const {
    if (auto* player = getPlayerBase())
        return player->_cec.isOnBit(21);
    return false;
}

bool PlayerBase::x_17() const {
    if (auto* player = getPlayerBase())
        return player->_cec.isOnBit(22);
    return false;
}

bool PlayerBase::x_18() const {
    if (auto* player = getPlayerBase())
        return player->_cec.isOnBit(23);
    return false;
}

bool PlayerBase::x_19() const {
    if (auto* player = getPlayerBase())
        return player->_cf0.isOnBit(23);
    return false;
}

bool PlayerBase::isClimbingStep() const {
    auto* player = getPlayerBase();
    return player && player->getRootAi() && player->getRootAi()->isCurrentAction("段差登り");
}

bool PlayerBase::m212() const {
    if (auto* player = getPlayerBase())
        return player->m212();
    return false;
}

bool PlayerBase::m190() const {
    if (auto* player = getPlayerBase())
        return player->m190();
    return false;
}

bool PlayerBase::x_20() const {
    if (auto* player = getPlayerBase())
        return player->_cf0.isOnBit(19);
    return false;
}

bool PlayerBase::x_22() const {
    if (auto* player = getPlayerBase())
        return player->_c48.isOnBit(19);
    return false;
}

f32 PlayerBase::getStopTimerReloadTime() const {
    if (auto* player = getPlayerBase())
        return player->getParam()->getRes().mGParamList->getPlayer()->mStopTimerReloadTime.ref();
    return 0.0f;
}

f32 PlayerBase::getStopTimerBlowAngle() const {
    if (auto* player = getPlayerBase())
        return player->getParam()->getRes().mGParamList->getPlayer()->mStopTimerBlowAngle.ref();
    return 0.0f;
}

f32 PlayerBase::getStopTimerBlowSpeedLimit() const {
    if (auto* player = getPlayerBase())
        return player->getParam()->getRes().mGParamList->getPlayer()->mStopTimerBlowSpeedLimit.ref();
    return 0.0f;
}

s32 PlayerBase::getStopTimerImpulseMaxCountSmallSword() const {
    if (auto* player = getPlayerBase())
        return player->getParam()->getRes().mGParamList->getPlayer()->mStopTimerImpluseMaxCountSmallSword.ref();
    return 1;
}

s32 PlayerBase::getStopTimerImpulseMaxCountLargeSword() const {
    if (auto* player = getPlayerBase())
        return player->getParam()->getRes().mGParamList->getPlayer()->mStopTimerImpluseMaxCountLargeSword.ref();
    return 1;
}

s32 PlayerBase::getStopTimerImpulseMaxCountSpear() const {
    if (auto* player = getPlayerBase())
        return player->getParam()->getRes().mGParamList->getPlayer()->mStopTimerImpluseMaxCountSpear.ref();
    return 1;
}

f32 PlayerBase::m232() const {
    if (auto* player = getPlayerBase())
        return player->getAncientAttackRate();
    return 1.0f;
}

bool PlayerBase::setPlayerStateToUnequipAndWait() const {
    auto* player = getPlayerBase();
    if (!player)
        return false;
    debugLog(0, "method");
    player->m307();
    return true;
}

bool PlayerBase::isNoStandSquat() const {
    auto* player = getPlayerBase();
    if (!player)
        return false;
    debugLog(0, "isNoStandSquat");
    return player->_c50.isOnBit(9);
}

bool PlayerBase::forbidComebackMaybe() const {
    auto* player = getPlayerBase();
    if (!player)
        return false;
    debugLog(1, "method");
    const auto lock = sead::makeScopedLock(player->_ca0);
    player->_ce0.setBit(3);
    return true;
}

bool PlayerBase::x_24() const {
    auto* player = getPlayerBase();
    if (!player)
        return false;
    debugLog(1, "method");
    const auto lock = sead::makeScopedLock(player->_ca0);
    player->_ce0.setBit(5);
    return true;
}

bool PlayerBase::isBgCrossFoot() const {
    auto* player = getPlayerBase();
    if (!player)
        return false;
    debugLog(1, "isBgCrossFoot");
    return player->_cfc.isOnBit(0);
}

bool PlayerBase::isBgCrossSlideFoot() const {
    auto* player = getPlayerBase();
    if (!player)
        return false;
    debugLog(1, "isBgCrossSlideFoot");
    return player->_cfc.isOnBit(2);
}

bool PlayerBase::isGroundForEvent() const {
    auto* player = getPlayerBase();
    if (!player)
        return false;
    debugLog(1, "isGroundForEvent");
    return player->isGroundForEvent();
}

bool PlayerBase::isHitRoof() const {
    auto* player = getPlayerBase();
    if (!player)
        return false;
    debugLog(1, "isHitRoof");
    return player->_cfc.isOnBit(7);
}

bool PlayerBase::isShieldRideOnGround() const {
    auto* player = getPlayerBase();
    if (!player)
        return false;
    debugLog(1, "isShieldRideOnGround");
    return player->_cf0.isOnBit(23) && !player->_cec.isOnBit(17) && player->_cfc.isOnBit(0);
}

bool PlayerBase::isNoShieldDamageFloor() const {
    auto* player = getPlayerBase();
    if (!player)
        return false;
    debugLog(1, "isNoShieldDamageFloor");
    return player->isNoShieldDamageFloor();
}

bool PlayerBase::isOnRaft() const {
    auto* player = getPlayerBase();
    if (!player)
        return false;
    debugLog(1, "isOnRaft");
    return player->_c98.isOnBit(9);
}

bool PlayerBase::isOnIceMakerBlock() const {
    auto* player = getPlayerBase();
    if (!player)
        return false;
    debugLog(1, "isOnIceMakerBlock");
    return player->_c98.isOnBit(10);
}

BaseProcLink& PlayerBase::getSpAttackTarget() const {
    auto* player = getPlayerBase();
    if (!player)
        return getDummyBaseProcLink();
    debugLog(1, "getSpAttackTarget");
    return player->getSpAttackTarget();
}

const sead::Vector3f& PlayerBase::getLookAtPosForCamera() const {
    auto* player = getPlayerBase();
    if (!player)
        return sead::Vector3f::zero;
    debugLog(1, "getLookAtPosForCamera");
    return player->_17a0;
}

bool PlayerBase::x_23() const {
    auto* player = getPlayerBase();
    if (!player)
        return false;
    if (player->getAttachedTargetActor()->_110.isOnBit(6))
        return true;
    return player->getAttachedTargetActor()->_110.isOnBit(9);
}

bool PlayerBase::slowTimeStuff() const {
    auto* player = getPlayerBase();
    if (!player)
        return false;
    if (VFR::instance()->getTimeSpeedMultiplierValue(0) < 1.0f)
        return false;
    return !player->_c4c.isOnBit(15);
}

f32 PlayerBase::getBowSlowRateDiam() const {
    auto* player = getPlayerBase();
    if (!player)
        return 1.0f;
    if (VFR::instance()->getTimeSpeedMultiplierValue(0) < 1.0f && player->_cf4.isOnBit(17))
        return player->getParam()->getRes().mGParamList->getPlayer()->mBowSlowRateDiam.ref();
    return 1.0f;
}

bool PlayerBase::x_21() const {
    if (!getPlayerBase())
        return false;
    return (uking::RuneMgr::instance()->_90 & 0x20) != 0;
}

bool PlayerBase::isInWater() const {
    auto* player = getPlayerBase();
    if (!player)
        return false;
    debugLog(1, "isInWater");
    auto* controller = player->getCharacterController();
    if (!controller)
        return false;
    return (controller->_116 & 4) != 0;
}

bool PlayerBase::checkControllerX() const {
    if (auto* player = getPlayerBase())
        return player->_17d0->controllerCheckPressedMaybe(37);
    return false;
}

bool PlayerBase::runeMgrCheckCanUseStasis() const {
    if (auto* player = getPlayerBase())
        return uking::RuneMgr::instance()->checkIsSelectedRuneAndCanUse(3, player);
    return false;
}

bool PlayerBase::runeMgrCheckCanUseRoundBomb() const {
    if (auto* player = getPlayerBase())
        return uking::RuneMgr::instance()->checkIsSelectedRuneAndCanUse(0, player);
    return false;
}

bool PlayerBase::isSlowStartInterval() const {
    auto* player = getPlayerBase();
    if (!player)
        return false;
    debugLog(1, "isSlowStartInterval");
    return player->_c4c.isOnBit(15);
}

bool PlayerBase::x_25() const {
    if (auto* player = getPlayerBase())
        return player->_cf0.isOnBit(8);
    return true;
}

bool PlayerBase::x_26() const {
    if (auto* player = getPlayerBase())
        return player->_cf4.isOnBit(15);
    return false;
}

bool PlayerBase::x_27() const {
    if (auto* player = getPlayerBase())
        return player->_c4c.isOnBit(5);
    return false;
}

bool PlayerBase::x_28() const {
    if (auto* player = getPlayerBase())
        return player->_cf4.isOnBit(16);
    return false;
}

f32 PlayerBase::m301() const {
    if (auto* player = getPlayerBase())
        return player->m301();
    return 1.0f;
}

bool PlayerBase::m179() const {
    if (auto* player = getPlayerBase())
        return player->m179();
    return false;
}

bool PlayerBase::m180() const {
    if (auto* player = getPlayerBase())
        return player->m180();
    return false;
}

bool PlayerBase::m181() const {
    if (auto* player = getPlayerBase())
        return player->m181();
    return false;
}

bool PlayerBase::x_29() const {
    if (auto* player = getPlayerBase())
        return player->_c44.isOnBit(8) && player->_d11 == 0;
    return false;
}

bool PlayerBase::m182_213() const {
    auto* player = getPlayerBase();
    if (!player)
        return false;
    return player->m182() && player->isMasterSwordEquipped();
}

bool PlayerBase::m194() const {
    if (auto* player = getPlayerBase())
        return player->m194();
    return false;
}

s32 PlayerBase::m322() const {
    if (auto* player = getPlayerBase())
        return player->m322();
    return 0;
}

s32 PlayerBase::m321() const {
    if (auto* player = getPlayerBase())
        return player->m321();
    return 0;
}

f32 PlayerBase::getHitSlowRate() const {
    if (auto* player = getPlayerBase())
        return player->getParam()->getRes().mGParamList->getPlayer()->mHitSlowRate.ref();
    return 1.0f;
}

bool PlayerBase::x_30() const {
    if (auto* player = getPlayerBase())
        return player->_cf0.isOnBit(25);
    return false;
}

bool PlayerBase::x_31() const {
    if (auto* player = getPlayerBase())
        return player->_cec.isOnBit(24);
    return false;
}

bool PlayerBase::x_32() const {
    if (auto* player = getPlayerBase())
        return player->_c44.isOnBit(5);
    return false;
}

bool PlayerBase::x_6() const {
    if (auto* player = getPlayerBase())
        return player->_c44.isOnBit(6);
    return false;
}

bool PlayerBase::isRidingSandSeal() const {
    if (auto* player = getPlayerBase())
        return player->_cec.isOnBit(17);
    return false;
}

bool PlayerBase::x_8() const {
    if (auto* player = getPlayerBase())
        return player->_cec.isOnBit(18);
    return false;
}

s32 PlayerBase::x_9() const {
    if (auto* player = getPlayerBase())
        return player->_d18;
    return 0;
}

bool PlayerBase::x_10() const {
    if (auto* player = getPlayerBase())
        return player->_cec.isOnBit(25);
    return false;
}

f32 PlayerBase::m248() const {
    if (auto* player = getPlayerBase())
        return player->m248();
    return 0.0f;
}

bool PlayerBase::m200() const {
    if (auto* player = getPlayerBase())
        return player->m200();
    return false;
}

bool PlayerBase::m226() const {
    if (auto* player = getPlayerBase())
        return player->m226();
    return false;
}

bool PlayerBase::x_11() const {
    if (auto* player = getPlayerBase())
        return player->_d11 != 0;
    return false;
}

bool PlayerBase::x_12() const {
    if (auto* player = getPlayerBase())
        return player->_cec.isOnBit(31);
    return true;
}

bool PlayerBase::x_13() const {
    if (auto* player = getPlayerBase())
        return player->_cf0.isOnBit(0);
    return false;
}

bool PlayerBase::m205() const {
    if (auto* player = getPlayerBase())
        return player->m205();
    return false;
}

bool PlayerBase::isRisingInAirMaybe() const {
    if (auto* player = getPlayerBase())
        return player->_cf0.isOnBit(12);
    return true;
}

bool PlayerBase::m186() const {
    if (auto* player = getPlayerBase())
        return player->m186();
    return false;
}

bool PlayerBase::groundedCheckStuff() const {
    if (auto* player = getPlayerBase())
        return player->_cf0.isOnBit(17);
    return false;
}

bool PlayerBase::m188() const {
    if (auto* player = getPlayerBase())
        return player->m188();
    return false;
}

bool PlayerBase::x_33() const {
    if (auto* player = getPlayerBase())
        return player->_c48.isOnBit(3);
    return false;
}

bool PlayerBase::m199() const {
    if (auto* player = getPlayerBase())
        return player->m199();
    return false;
}

bool PlayerBase::x_34() const {
    if (auto* player = getPlayerBase())
        return player->_cec.isOnAll(5);
    return false;
}

bool PlayerBase::m178() const {
    if (auto* player = getPlayerBase())
        return player->m178();
    return false;
}

bool PlayerBase::x_35() const {
    if (auto* player = getPlayerBase())
        return player->_cf4.isOnBit(2);
    return false;
}

bool PlayerBase::m191() const {
    if (auto* player = getPlayerBase())
        return player->m191();
    return false;
}

bool PlayerBase::x_36() const {
    if (auto* player = getPlayerBase())
        return player->_cf0.isOnBit(14) && player->_c48.isOnBit(24);
    return false;
}

bool PlayerBase::x_37() const {
    if (auto* player = getPlayerBase())
        return player->_cec.isOnBit(13);
    return false;
}

bool PlayerBase::m204() const {
    if (auto* player = getPlayerBase())
        return player->m204();
    return false;
}

bool PlayerBase::m193() const {
    if (auto* player = getPlayerBase())
        return player->m193();
    return false;
}

bool PlayerBase::x_7() const {
    if (auto* player = getPlayerBase())
        return player->_c44.isOnBit(21);
    return false;
}

bool PlayerBase::m224() const {
    if (auto* player = getPlayerBase())
        return player->m224();
    return false;
}

bool PlayerBase::x_38() const {
    if (auto* player = getPlayerBase())
        return player->_c44.isOnBit(17);
    return false;
}

bool PlayerBase::m302() const {
    if (auto* player = getPlayerBase())
        return player->m302();
    return false;
}

bool PlayerBase::x_39() const {
    if (auto* player = getPlayerBase())
        return player->_c48.isOnBit(26);
    return false;
}

bool PlayerBase::x_40() const {
    if (auto* player = getPlayerBase())
        return player->_c40.isOnBit(14);
    return false;
}

s32 PlayerBase::m297() const {
    if (auto* player = getPlayerBase())
        return player->m297();
    return 0;
}

s32 PlayerBase::m298_271() const {
    if (auto* player = getPlayerBase())
        return player->m298(player->m271());
    return 0;
}

bool PlayerBase::x_41() const {
    if (auto* player = getPlayerBase())
        return player->_cf4.isOnBit(30);
    return false;
}

bool PlayerBase::m304() const {
    if (auto* player = getPlayerBase())
        return player->m304();
    return false;
}

f32 PlayerBase::m305() const {
    if (auto* player = getPlayerBase())
        return player->m305();
    return 0.0f;
}

bool PlayerBase::checkActionX() const {
    auto* player = getPlayerBase();
    return player && player->getRootAi() && player->getRootAi()->isCurrentAction("よじ登り飛びつき");
}

bool PlayerBase::m185() const {
    if (auto* player = getPlayerBase())
        return player->m185();
    return false;
}

bool PlayerBase::checkActionX_0() const {
    auto* player = getPlayerBase();
    return player && player->getRootAi() && player->getRootAi()->isCurrentAction("ぶら下がりからのよじ登り");
}

bool PlayerBase::checkActionX_1() const {
    auto* player = getPlayerBase();
    return player && player->getRootAi() && player->getRootAi()->isCurrentAction("小段差よじ登り壁つかみ");
}

bool PlayerBase::x_42() const {
    if (auto* player = getPlayerBase())
        return player->_cf4.isOnBit(1);
    return false;
}

bool PlayerBase::m187() const {
    if (auto* player = getPlayerBase())
        return player->m187();
    return false;
}

bool PlayerBase::isRidingHorse() const {
    if (auto* player = getPlayerBase())
        return player->isRidingHorse();
    return false;
}

Actor* PlayerBase::x_43() const {
    if (auto* player = getPlayerBase())
        return sead::DynamicCast<Actor>(player->_e88.getProc(nullptr, nullptr));
    return nullptr;
}

f32 PlayerBase::m231() const {
    if (auto* player = getPlayerBase())
        return player->m231();
    return 1.0f;
}

bool PlayerBase::runeMgrCheckCanUseSquareBomb() const {
    if (auto* player = getPlayerBase())
        return uking::RuneMgr::instance()->checkIsSelectedRuneAndCanUse(1, player);
    return false;
}

f32 PlayerBase::x_44() const {
    if (auto* player = getPlayerBase())
        return player->_e54;
    return 0.0f;
}

}  // namespace ksys::act::acc

bool sub_710084D068() {
    auto* info = ksys::act::PlayerInfo::instance();
    if (!info)
        return false;
    return info->getPlayerLink().hasProc();
}
