#include "KingSystem/ActorSystem/actPlayerInfo.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"
#include "KingSystem/ActorSystem/Profiles/actPlayerBase.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "KingSystem/ActorSystem/actBaseProc.h"
#include "KingSystem/ActorSystem/actBaseProcMgr.h"
#include "KingSystem/GameData/gdtCommonFlagsUtils.h"
#include "KingSystem/ksys.h"

namespace ksys::act {

SEAD_SINGLETON_DISPOSER_IMPL(PlayerInfo)

PlayerInfo::PlayerInfo() = default;
PlayerInfo::~PlayerInfo() = default;

bool PlayerInfo::init() {
    return true;
}

void PlayerInfo::setAndAcquirePlayer(PlayerBase* player) {
    if (mPlayerActor)
        return;
    mPlayerActor = player;
    ksys::setPlayerLink(player);
    mPlayerLink.acquire(player, false);
}

void PlayerInfo::resetPlayer(PlayerBase* player) {
    if (mPlayerActor == player) {
        mPlayerActor = nullptr;
        ksys::setPlayerLink(nullptr);
    }
}

bool PlayerInfo::acquireHorse(BaseProc* horse) {
    return mHorseLink.acquire(horse, false);
}

void PlayerInfo::setHorseLink(const BaseProcLink& horse_link) {
    mHorseLink = horse_link;
}

PlayerBase* PlayerInfo::getPlayer() const {
    if (!mPlayerActor) {
        return nullptr;
    }
    BaseProcMgr::instance()->isAccessingProcSafe(mPlayerActor, nullptr);
    return mPlayerActor;
}

PlayerBase* PlayerInfo::getPlayer_() const {
    if (!mPlayerActor) {
        return nullptr;
    }
    BaseProcMgr::instance()->isAccessingProcSafe(mPlayerActor, nullptr);
    return mPlayerActor;
}

Actor* PlayerInfo::getRiddenHorse() const {
    auto* player = getPlayer();
    if (!player || !player->isRidingHorse())
        return nullptr;
    return sead::DynamicCast<Actor>(mHorseLink.getProc(nullptr, nullptr));
}

void PlayerInfo::setMaxLifeForPlayerActor(s32 max_heart) {
    if (mPlayerActor)
        static_cast<Player*>(mPlayerActor)->_1868 = max_heart;
}

s32 PlayerInfo::getMaxLifeFromPlayerActor() const {
    return mPlayerActor ? mPlayerActor->getMaxLife() : 0;
}

void PlayerInfo::setMaxHeartValue(s32 quarter_hearts) {
    gdt::setFlag_MaxHartValue(quarter_hearts);
    mMaxHeartValue = static_cast<f32>(quarter_hearts);
}

u32 PlayerInfo::getMaxHeartValue() const {
    // Return type is unsigned, but the conversion is signed
    return static_cast<s32>(mMaxHeartValue);
}

void PlayerInfo::updateMaxHeartValueFromGameData() {
    mMaxHeartValue = static_cast<f32>(gdt::getFlag_MaxHartValue());
}

void PlayerInfo::setLifeForPlayerActor(s32 life) {
    if (mPlayerActor) {
        *mPlayerActor->getLife() = life;
    }
}

s32 PlayerInfo::getLifeFromPlayerActor() const {
    if (!mPlayerActor) {
        return 0;
    }
    auto* life = mPlayerActor->getLife();
    return life ? *life : 1;
}

void PlayerInfo::updateCurrentHartFlagFromPlayerActor() {
    s32 life = getLifeFromPlayerActor();
    if (life > getMaxLifeFromPlayerActor()) {
        life = getMaxLifeFromPlayerActor();
        setLifeForPlayerActor(life);
    }
    gdt::setFlag_CurrentHart(life);
}

void PlayerInfo::saveLifeInfoForSwordPull() {
    if (!mPlayerActor)
        return;
    auto* life = mPlayerActor->getLife();
    mLifeBeforeSwordPull = life ? static_cast<f32>(*life) : 1.0f;
    mExtraLifeBeforeSwordPull = mPlayerActor->m321();
}

void PlayerInfo::recoverLife() {
    setLifeForPlayerActor(getMaxLifeFromPlayerActor());
}

void PlayerInfo::setStaminaCurrentMax(f32 max_stamina) {
    gdt::setFlag_StaminaCurrentMax(max_stamina);
    mStaminaCurrentMax = max_stamina;
}

f32 PlayerInfo::getStaminaCurrentMax() const {
    return mStaminaCurrentMax;
}

void PlayerInfo::updateStaminaCurrentMaxFromGameData() {
    mStaminaCurrentMax = gdt::getFlag_StaminaCurrentMax();
}

void PlayerInfo::setStaminaMax(f32 max_stamina) {
    gdt::setFlag_StaminaMax(max_stamina);
    mStaminaMax = max_stamina;
}

f32 PlayerInfo::getStaminaMax() const {
    return mStaminaMax;
}

void PlayerInfo::updateStaminaMaxFromGameData() {
    mStaminaMax = gdt::getFlag_StaminaMax();
}

void PlayerInfo::setMaxStaminaForPlayerActor(f32 max_stamina) {
    if (mPlayerActor)
        static_cast<Player*>(mPlayerActor)->_186c = max_stamina;
}

f32 PlayerInfo::getMaxStaminaFromPlayerActor() const {
    if (mPlayerActor)
        return static_cast<Player*>(mPlayerActor)->_186c;
    return 0.0f;
}

void PlayerInfo::recoverStamina() {
    setStaminaCurrentMax(getMaxStaminaFromPlayerActor());
}

void PlayerInfo::recoverCondition() {
    auto* player = mPlayerActor;
    if (player) {
        const auto lock = sead::makeScopedLock(player->_c58);
        player->_c98.set(0x100);
    }
}

PlayerBase* PlayerInfo::getPlayerUnchecked() {
    return mPlayerActor;
}

sead::Vector3f& PlayerInfo::getPlayerPos() {
    ActorConstDataAccess accessor;

    acquireActor(&mPlayerLink, &accessor);
    accessor.debugLog(1, "getPlayerPos");
    return mPlayerPos;
}

sead::Vector3f& PlayerInfo::getPlayerPosForPostCalc() {
    ActorConstDataAccess accessor;

    acquireActor(&mPlayerLink, &accessor);
    accessor.debugLog(0, "getPlayerPosForPostCalc");
    return mPlayerPosForPostCalc;
}

const sead::Vector3f& PlayerInfo::getPlayerM265() const {
    if (mPlayerActor)
        return *mPlayerActor->m265();
    return sead::Vector3f::zero;
}

}  // namespace ksys::act
