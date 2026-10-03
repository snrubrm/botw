#include "KingSystem/ActorSystem/Profiles/actPlayerBase.h"
#include "Game/gameRuneMgr.h"
#include "Game/gameUnk_710246d058.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "KingSystem/ActorSystem/actBaseProcMgr.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/ActorSystem/actAiRoot.h"
#include "KingSystem/ActorSystem/actPlayerInfo.h"
#include "KingSystem/Resource/Actor/resResourceGParamList.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectPlayer.h"

namespace ksys::act {

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

sead::Vector3f& PlayerBase::getPlayerPosForPostCalc() {
    return PlayerInfo::instance()->getPlayerPosForPostCalc();
}

PlayerBase* PlayerBase::getPlayer() {
    BaseProcMgr::instance()->isAccessingProcSafe(this, nullptr);
    return this;
}

bool PlayerBase::x_51() {
    return _17d0->controllerCheckPressedMaybe(3);
}

bool PlayerBase::getActorViaAccessor(ActorLinkConstDataAccess* accessor) {
    return accessor->acquire(this);
}

}  // namespace ksys::act

namespace ksys::act::acc {

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

bool PlayerBase::m298_271() const {
    if (auto* player = getPlayerBase())
        return player->m298(player->m271());
    return false;
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
