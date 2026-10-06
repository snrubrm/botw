#include "Game/Actor/actEnemy.h"
#include "KingSystem/ActorSystem/actLifeRecoveryInfo.h"
#include <basis/seadNew.h>
#include <prim/seadScopedLock.h>
#include "Game/Actor/actRideable.h"
#include "Game/Actor/actWeapon.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/ActorSystem/actAiRoot.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actTag.h"
#include "KingSystem/System/PlayReportMgr.h"
#include "KingSystem/GameData/gdtSpecialFlags.h"
#include "KingSystem/GameData/gdtManager.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Resource/Actor/resResourceGParamList.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectEnemy.h"
#include "KingSystem/Map/mapObjectLink.h"
#include "KingSystem/World/worldManager.h"

bool sub_71002F0924(const ksys::act::ActorConstDataAccess& accessor);

namespace uking::act {

// NON_MATCHING: Existing atomic bool conversion and accessor stack placement differ.
void Enemy::onDeleteRequested_(DeleteReason reason) {
    PlayerOrEnemy::onDeleteRequested_(reason);
    if (!sub_71011CBC28() && !_540)
        return;
    getWeapons();
    for (s32 i = 0; i < 6; ++i) {
        ksys::act::acc::Weapon weapon;
        if (!(_e82 & 0x80)) {
            ksys::act::ActorConstDataAccess candidate;
            ksys::act::acquireActor(&_c38[i], &candidate);
            if (!sub_71002F0924(candidate))
                weapon.acquireActor(candidate);
        }
        if (!weapon.sub_71002EF980() && weapon.hasProc())
            weapon.deleteEx(reason);
    }
}

void Enemy::incrementDefeatedCount() {
    if (!this)
        return;
    auto* manager = ksys::gdt::Manager::instance();
    if (!manager || ksys::act::hasTag(this, ksys::act::tags::NotCountDefeatedNum))
        return;
    sead::SafeString name = getName();
    ksys::act::getSameGroupActorName(&name, this);
    sead::FormatFixedSafeString<128> key("Defeated_%s_Num", name.cstr());
    s32 count = 0;
    if (manager->getParam().get().getS32(&count, key) && count <= 9)
        manager->incrementS32(1, key);
}

void Enemy::killWithDropsAndEffects(int a1) {
    if (auto* reporter = ksys::PlayReportMgr::instance())
        reporter->reportDebug("KillEnemy", sead::SafeString(getName().cstr()));
    incrementDefeatedCount();
    Actor::killWithDropsAndEffects(a1);
}

void Enemy::m92(ksys::phys::RigidBody* body) {
    if (ksys::world::Manager::instance()->isAocField() && getLife()) {
        if (auto* life = getLife())
            *life = 0;
        emitSignal(ksys::map::MapLinkDefType::LifeZero, true);
        emitSignal(ksys::map::MapLinkDefType::DeadUp, true);
    }
    Actor::m92(body);
}

void Enemy::onEnterSleep_() {
    Actor::onEnterSleep_();
    if (_1148._48)
        _1148._48->sub_7100E64E60();
    ksys::act::ActorConstDataAccess first;
    if (ksys::act::acquireActor(&_1148._38, &first))
        first.sleep(SleepWakeReason::_0);
    ksys::act::ActorConstDataAccess second;
    if (ksys::act::acquireActor(&_1100, &second))
        second.sleep(SleepWakeReason::_0);
}

ksys::act::BaseProc* Enemy::construct(const CreateArg& arg, sead::Heap* heap) {
    return new (heap, std::nothrow) Enemy(arg);
}

// NON_MATCHING: BoneHandle members (0xf68, 0x1010) are not typed yet; the original also skips the
// vtable store of the object at 0x1148
Enemy::~Enemy() = default;

void Enemy::Unk_12d0::sub_7100710F04() {}

void Enemy::Unk_12d0::sub_7100710F08() {
    if (_0) {
        _8 = -1;
        _c = 0;
    }
}

bool Enemy::m57() {
    if (mActorFlags2.isOn(ActorFlag2::_40))
        return true;
    return _1290._38 > 0.0f;
}

bool Unk_7102357a08::m2(const ksys::Message& message) {
    if (message.getType() != 0x80000b0)
        return false;

    _30 = true;
    _18 = message.getSource();
    return true;
}

bool Unk_7102357a38::m2(const ksys::Message& message) {
    if (message.getType() != 0x80000af)
        return false;

    _30 = true;
    _18 = message.getSource();
    return true;
}

bool Unk_71023579d8::m2(const ksys::Message& message) {
    if (message.getType() != 0x80000cb)
        return false;

    auto* payload = static_cast<Unk_71023579d8_Payload*>(message.getUserData());
    if (!payload)
        return false;

    {
        sead::ScopedLock<sead::JobQueueLock> lock(&payload->mLock);
        _34._0 = payload->_0;
    }
    _30 = true;
    _18 = message.getSource();
    return true;
}

bool Unk_71023579a8::m2(const ksys::Message& message) {
    if (message.getType() != 0x80000d0)
        return false;

    auto* payload = static_cast<Unk_71023579a8_Payload*>(message.getUserData());
    if (!payload)
        return false;

    {
        sead::ScopedLock<sead::JobQueueLock> lock(&payload->mLock);
        _34._0 = payload->_0;
    }
    _30 = true;
    _18 = message.getSource();
    return true;
}

bool Unk_7102357978::m2(const ksys::Message& message) {
    if (message.getType() != 0x80000d1)
        return false;

    auto* payload = static_cast<Unk_7102357978_Payload*>(message.getUserData());
    if (!payload)
        return false;

    {
        sead::ScopedLock<sead::JobQueueLock> lock(&payload->mLock);
        _34._0 = payload->_0;
    }
    _30 = true;
    _18 = message.getSource();
    return true;
}

bool Unk_7102357948::m2(const ksys::Message& message) {
    if (message.getType() != 0x80000d2)
        return false;

    auto* payload = static_cast<Unk_7102357948_Payload*>(message.getUserData());
    if (!payload)
        return false;

    {
        sead::ScopedLock<sead::JobQueueLock> lock(&payload->mLock);
        _34._0 = payload->_0;
    }
    _30 = true;
    _18 = message.getSource();
    return true;
}

Unk_71023579d8::~Unk_71023579d8() = default;

Unk_71023579a8::~Unk_71023579a8() = default;

Unk_7102357978::~Unk_7102357978() = default;

Unk_7102357948::~Unk_7102357948() = default;

Unk_7100d3cd74* Enemy::m101() {
    return &_1128;
}

HorseRideInfo* Enemy::getPlayerRideInfo() {
    return _10f8;
}

ksys::act::Actor* Enemy::m31() {
    if (auto* rideable = getHorseOptionsMaybe())
        return rideable->sub_7100E8B644();
    return DynamicActor::m31();
}

ksys::act::Actor* Enemy::m48() {
    if (auto* rideable = getHorseOptionsMaybe())
        return rideable->sub_7100E8B6E0();
    return DynamicActor::m48();
}

void Enemy::m70() {
    if (auto* rideable = sead::DynamicCast<Rideable>(_1148._20))
        rideable->Unk_7100e8b2b8::_10 &= ~0x38u;
}

Rideable* Enemy::getHorseOptionsMaybe() {
    return sead::DynamicCast<Rideable>(_1148._20);
}

RideableBase* Enemy::m132() {
    return _1148._20;
}

Unk_7100e8b2b8* Enemy::getMotorcyclePriorityStuffMaybe() {
    return sead::DynamicCast<Rideable>(_1148._20);
}

Enemy::IsSpecialJobTypeResult Enemy::isSpecialJobType_(ksys::act::JobType type) {
    const auto result = DynamicActor::isSpecialJobType_(type);
    if (auto* rideable = getHorseOptionsMaybe())
        return IsSpecialJobTypeResult(rideable->sub_7100E8BB4C(int(result)));
    return result;
}

void* Enemy::m119() {
    return _12d8;
}

void Enemy::m117(ksys::act::Unk117* arg) {
    if (auto* rideable = getHorseOptionsMaybe()) {
        if (!rideable->sub_7100E8B780(arg))
            return;
    }
    PlayerOrEnemy::m117(arg);
}

void Enemy::updateMtxFromPhysics() {
    sead::Vector3f velocity;
    sead::Matrix34f mtx;
    auto* controller = getCharacterController();
    if (controller && !_e84.isOnBit(11)) {
        controller->sub_7100F5F598(&velocity);
        mVelocity = velocity * (1.0f / 30.0f);
        controller->sub_7100F635BC(&velocity);
        mAngVelocity = velocity * (1.0f / 30.0f);
        controller->sub_7100F626E8(&mtx);
    } else {
        auto* body = mMainBody.load();
        if (!body)
            return;
        body->getLinearVelocity(&velocity);
        mVelocity = velocity * (1.0f / 30.0f);
        body->getAngularVelocity(&velocity);
        mAngVelocity = velocity * (1.0f / 30.0f);
        body->getTransform(&mtx);
    }
    mMtx = mtx;
    nullsub_4648();
}

s32 Enemy::getMaxLife() {
    const auto* param = getParam()->getRes().mGParamList->getEnemy();
    if (!param->mStatusChangeFlag.ref().isEmpty() &&
        ksys::gdt::getBoolByKey(param->mStatusChangeFlag.ref(), false) &&
        param->mChangeLife.ref() >= 0.0f)
        return param->mChangeLife.ref();
    return Actor::getMaxLife();
}

// NON_MATCHING: the two stack slots (reason / the Rideable mode enum) are assigned in the opposite order
bool Enemy::shouldUnload(s32* a1) {
    s32 reason = 0;
    if (auto* rideable = getHorseOptionsMaybe()) {
        const Unk_7100e8b2b8::Unk8 type = rideable->Unk_7100e8b2b8::_8 & 0xff;
        if (int(type) != Unk_7100e8b2b8::Unk8::_0)
            return false;
    }

    const bool unload = shouldUnloadBecauseOfDistance(&reason);
    if (reason == 10 || reason == 11) {
        if (_e84.isOn(0x40004))
            return false;
        if (mActorFlags2.isOn(ActorFlag2::_80000000))
            return false;
    }
    *a1 = reason;
    return unload;
}

// NON_MATCHING: register allocation / the original keeps `first_result | is_mini` in a register
bool Enemy::isGuard() {
    auto* as_list = mASList;
    if (!as_list)
        return false;

    const bool is_mini = ksys::act::hasTag(this, ksys::act::tags::TeamGuardianMini);
    if (as_list->x(14, nullptr, 0, 0, &ksys::as::ASList::Unk2::sub_71011638DC, true))
        return true;
    if (!is_mini)
        return false;
    if (as_list->x(14, nullptr, 1, 0, &ksys::as::ASList::Unk2::sub_71011638DC, true))
        return true;
    return as_list->x(14, nullptr, 2, 0, &ksys::as::ASList::Unk2::sub_71011638DC, true);
}

void Enemy::onPreDeleteStart_(PrepareArg& arg) {
    ksys::act::ActorConstDataAccess accessor1;
    if (ksys::act::acquireActor(&_1148._38, &accessor1))
        accessor1.deleteLater(ksys::act::BaseProc::DeleteReason::_0);
    _1148._38.reset();

    ksys::act::ActorConstDataAccess accessor2;
    if (ksys::act::acquireActor(&_1100, &accessor2))
        accessor2.deleteLater(ksys::act::BaseProc::DeleteReason::_0);
    _1100.reset();
}

void Enemy::m36(const sead::Vector3f& a1, const sead::Vector3f& a2, bool a3, bool a4, bool a5) {
    if (_e84.isOnBit(19))
        DynamicActor::m36(a1, a2, a3, a4, a5);
}

void Enemy::m41(sead::Matrix34f* mtx) {
    auto* body = mMainBody.load();
    if (body && _e84.isOnBit(11))
        body->getTransform(mtx);
    else
        Actor::m41(mtx);
}

ksys::act::Actor* Enemy::m141(const s32* index) {
    if (_e82 & 0x80)
        return nullptr;
    auto* weapon = sead::DynamicCast<Weapon>(_c38[*index].getProc(nullptr, nullptr));
    if (!weapon || weapon->get920() != 0xff || weapon->get921())
        weapon = nullptr;
    return weapon;
}

bool Enemy::m164(s32 idx, ksys::act::Actor* weapon, bool a3, bool a4) {
    if (!PlayerOrEnemy::m164(idx, weapon, false, false))
        return false;
    const u32 mask = 1 << idx;
    if (!(_e82 & 0x80) && _e81.isOn(mask) && !_c38[idx].hasProcById(weapon)) {
        setDroppedWeaponFlag();
        _e82 |= 0x80;
    }
    _c38[idx].acquire(weapon, false);
    _e80.set(mask);
    return true;
}

bool Enemy::m177(s32 idx, ksys::act::Actor* weapon) {
    if (!getWeapons()->m2(idx, weapon))
        return false;
    _c38[idx].acquire(weapon, false);
    _e80.set(1 << idx);
    return true;
}

void Enemy::sub_7100015438(s32 idx, ksys::act::Actor* weapon) {
    _c38[idx].acquire(weapon, false);
    _e82 |= 0x1000;
}

// NON_MATCHING: the original loads the flag byte after computing the bit mask (schedule only)
ksys::act::LifeRecoverInfo* Enemy::getLifeRecoverInfo() {
    auto* info = _13c0;
    if (!info)
        return nullptr;
    const ksys::act::LifeRecoverInfo::Flag flag(0);
    if (info->mFlags & (1 << int(flag)))
        return info;
    return nullptr;
}

}  // namespace uking::act

namespace uking::act {

bool Enemy::m165(sead::BufferedSafeString* out) {
    sead::SafeString arrow_name;
    if (!getRootAi()->getMapUnitParam(&arrow_name, "ArrowName"))
        return false;
    out->copy(arrow_name);
    return true;
}

}  // namespace uking::act
