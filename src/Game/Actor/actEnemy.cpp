#include "Game/Actor/actEnemy.h"
#include <limits>
#include <random/seadGlobalRandom.h>
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectAttackInterval.h"
#include <geom/seadGeometry.h>
#include <math/seadMathCalcCommon.h>
#include "KingSystem/ActorSystem/actInfoCommon.h"
#include "KingSystem/ActorSystem/actInfoData.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/ActorSystem/actLifeRecoveryInfo.h"
#include <basis/seadNew.h>
#include <prim/seadScopedLock.h>
#include "Game/Actor/actRideable.h"
#include "Game/Actor/actHorseBase.h"
#include "Game/Actor/actWeapon.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/ActorSystem/aiRootAi.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/Profiles/actWeaponBase.h"
#include "Game/Actor/Player/actPlayerInfo.h"
#include "KingSystem/ActorSystem/actTag.h"
#include "KingSystem/System/PlayReportMgr.h"
// For Enemy::m75: the callback element type (lane5 owns it; used, not modified).
#include "Game/Actor/Action/actionRemainElectricCannonBeamHerald.h"
#include "KingSystem/System/PlayReportMgr.h"
#include "KingSystem/GameData/gdtSpecialFlags.h"
#include "KingSystem/GameData/gdtManager.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Resource/Actor/resResourceGParamList.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectEnemy.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectHorseRider.h"
#include "KingSystem/Map/mapObjectLink.h"
#include "Game/Actor/actUnk_71025ae680.h"
#include "KingSystem/ActorSystem/actActorBind.h"

#include "KingSystem/World/worldManager.h"
#include "Game/gameUnkRttiPlaceholders.h"

bool sub_71002F0924(const ksys::act::ActorLinkConstDataAccess& accessor);

// The Enemy filter Unk_71023572b8 does not override the shared material-filter virtuals, so the Enemy
// TU holds the base class's out-of-line definitions (address neighbours of the Unk_71023572b8
// destructors).
bool ksys::phys::NavMeshCharacterUnk58::m2(ksys::phys::NavMeshCharacter* nav, u32 material) {
    // NON_MATCHING: the original keeps `material` zero-extended in x19 across the F94 call
    // (and x19, x2, then mov x1, x19); ours keeps the 32-bit value (mov w19, w2, then mov w1, w19).
    // Same classifier call.
    return ksys::phys::NavMeshCharacter::sub_7100F74FA0(
        ksys::phys::NavMeshCharacter::sub_7100F74F94(nav), material);
}

f32 ksys::phys::NavMeshCharacterUnk58::m3(ksys::phys::NavMeshCharacter* nav, s32 material, s32 a,
                                          ksys::phys::NavMeshCharacterType type, f32 cost) {
    return ksys::phys::NavMeshCharacter::sub_7100F74FD8(
        ksys::phys::NavMeshCharacter::sub_7100F74F94(nav), material);
}

bool ksys::phys::NavMeshCharacterUnk58::m4(ksys::phys::NavMeshCharacter* nav, s32 material, s32 a,
                                           ksys::phys::NavMeshCharacterType type) {
    const f32 cost = m3(nav, material, a, type, ksys::phys::sUnk_7101ec296c);
    return !(sead::Mathf::abs(cost) > std::numeric_limits<f32>::max());
}

bool ksys::phys::NavMeshCharacterUnk58::m6() {
    return false;
}

// Shared m5: forwards to m4 with the other material after a few swimmer-type special cases that
// accept the pair directly.
// NON_MATCHING: register allocation of the prologue and the branch layout differ (the original keeps
// `this` in x22 and the type in x6; ours spills the type to x21 first and branches on m4's false
// result instead of its true result). Same checks, same calls.
bool ksys::phys::NavMeshCharacterUnk58::m5(ksys::phys::NavMeshCharacter* nav, s32 material, s32 a,
                                           s32 other_material, s32 other_a,
                                           ksys::phys::NavMeshCharacterType type) {
    if (nav) {
        const ksys::phys::NavMeshCharacterType nav_type(nav->_1d8);
        if (nav_type == ksys::phys::NavMeshCharacterType::PoorSwimmer ||
            nav_type == ksys::phys::NavMeshCharacterType::GoodSwimmer ||
            nav_type == ksys::phys::NavMeshCharacterType::IceSwimmer) {
            if (material == 7) {
                if (!m4(nav, 7, a, type))
                    return true;
            }
        } else if (nav_type == ksys::phys::NavMeshCharacterType::GiantSwimmer) {
            if (material == 7) {
                if (!m4(nav, 7, a, type))
                    return true;
            } else if (material == 10) {
                return true;
            }
        } else if (material == 5 && nav_type == ksys::phys::NavMeshCharacterType::TallEnemy) {
            return true;
        }
    }
    return m4(nav, other_material, other_a, type);
}

namespace uking::act {

// Enemy material filter, vtable 0x71023572b8. The factory stores its actor at +0x8.
class Unk_71023572b8 : public ksys::phys::NavMeshCharacterUnk58 {
public:
    explicit Unk_71023572b8(ksys::act::Actor* actor) : mActor(actor) {}
    // The original keeps its vptr store; { ; } follows GameDataFlagSelector (96101229).
    ~Unk_71023572b8() override { ; }

    ksys::act::Actor* mActor;
};
KSYS_CHECK_SIZE_NX150(Unk_71023572b8, 0x10);

ksys::phys::NavMeshCharacterUnk58* Enemy::m179(sead::Heap* heap) {
    if (ksys::act::isPreyOrSwarm(this))
        return new (heap, 8) Unk_71024eb548;
    return new (heap, 8) Unk_71023572b8(this);
}

// NON_MATCHING: the clearance comparison operands are reversed.
bool Enemy::sub_710001A204(const sead::Vector3f& a, const sead::Vector3f& b,
                          const sead::Vector3f& pos, f32 radius) {
    if (radius <= 0.0f)
        return true;
    if (radius * radius < sead::Geometry::calcSquaredDistancePointToSegment(
                              pos, sead::Segment3f(b, a), nullptr))
        return sub_710001A2B0(a, b, radius);
    return false;
}

// NON_MATCHING: stack temporary slots and early-return block placement differ.
bool Enemy::sub_710001A2B0(const sead::Vector3f& target, const sead::Vector3f& origin,
                          f32 distance) {
    if (distance <= 0.0f)
        return true;
    const f32 squared_distance = distance * distance;
    if (_c48._8.hasProc() &&
        !(sead::Geometry::calcSquaredDistancePointToSegment(
              _c48._18, sead::Segment3f(origin, target), nullptr) > squared_distance))
        return false;
    for (auto& entry : _d70.mEntries) {
        if (!entry.link.hasProcInCalcState())
            continue;
        ksys::act::ActorLinkConstDataAccess accessor;
        ksys::act::acquireActor(&entry.link, &accessor);
        if (!(entry.link.hasProcInCalcState() && (entry.flags & 2)) &&
            !ksys::act::isPlayerProfile(accessor) && accessor.getProfile() != "WolfLink")
            continue;
        sead::Vector3f position;
        accessor.getActorMtx().getTranslation(position);
        if (!(sead::Geometry::calcSquaredDistancePointToSegment(
                  position, sead::Segment3f(origin, target), nullptr) > squared_distance))
            return false;
    }
    return true;
}

Unk_71025ae680* Enemy::m178(sead::Heap* heap) {
    if (sub_71006E8644(this))
        return new (heap, 8) Unk_710244edc0(this);
    return new (heap, 8) Unk_710244dd20(this);
}

void Enemy::sub_7100016494() {
    ++_11a0;
    sead::FixedSafeString<32> name;
    if (m165(&name)) {
        const s32 limit = ksys::act::getArrowEnemyShootNumForDelete(
            ksys::act::InfoData::instance(), name.cstr());
        _11a0 = sead::Mathf::clampMax(_11a0, limit);
    }
}


Unk_7102357908::Unk50::Unk50(ksys::phys::CharacterController* controller)
    : mController(controller),
      mPosteriorLimbOffset(std::numeric_limits<f32>::quiet_NaN(),
                           std::numeric_limits<f32>::quiet_NaN(),
                           std::numeric_limits<f32>::quiet_NaN()) {}

bool Unk_7102357908::Unk50::sub_71006F0800(const CalcArg& arg) {
    if (!mController)
        return false;
    mController->mFlags.set(0x10);
    mPosteriorLimbOffset.set(arg.posterior_limb_offset);
    mRayCastLength = arg.ray_cast_length;
    mPriorLimbOffset.set(arg.prior_limb_offset);
    mPriorRayCastLength = arg.prior_ray_cast_length;
    _28 = arg.enabled ? (_28 | 1) : (_28 & ~1);
    return true;
}


// NON_MATCHING: Existing atomic bool conversion and accessor stack placement differ.
void Enemy::onDeleteRequested_(DeleteReason reason) {
    PlayerOrEnemy::onDeleteRequested_(reason);
    if (!sub_71011CBC28() && !_540)
        return;
    getWeapons();
    for (s32 i = 0; i < 6; ++i) {
        ksys::act::acc::Weapon weapon;
        if (!(_e82 & 0x80)) {
            ksys::act::ActorLinkConstDataAccess candidate;
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
    if (_1190)
        _1190->sub_7100E64E60();
    ksys::act::ActorLinkConstDataAccess first;
    if (ksys::act::acquireActor(&_1180, &first))
        first.sleep(SleepWakeReason::_0);
    ksys::act::ActorLinkConstDataAccess second;
    if (ksys::act::acquireActor(&_1100, &second))
        second.sleep(SleepWakeReason::_0);
}

ksys::act::BaseProc* Enemy::construct(const CreateArg& arg, sead::Heap* heap) {
    return new (heap, std::nothrow) Enemy(arg);
}

// NON_MATCHING: BoneHandle members (0xf68, 0x1010) are not typed yet; the original also skips the
// vtable store of the object at 0x1148
Enemy::Enemy(const CreateArg& arg) : PlayerOrEnemy(arg), _ea8() {
    _e84.makeAllZero();
    _e82 = 0;
    _1c0 = 1;
    m135()->_4 = 1;
}

Enemy::~Enemy() = default;

void Enemy::Unk_12d0::sub_7100710F04() {}

void Enemy::Unk_12d0::sub_7100710F1C() {
    _8 = -1;
    _c = 0;
}

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

// 0x7100019e20: whether `body` belongs to this enemy or to one of its own weapons: the base check,
// then the eight BaseProcLinks at 0xea8, then Weapon bit 0 of _e50.
bool Enemy::m49(ksys::phys::RigidBody* body) {
    if (PlayerOrEnemy::m49(body))
        return true;

    auto* tag = sead::DynamicCast<ksys::act::PhysicsUserTag>(body->getUserTag());
    if (!tag)
        return false;

    for (s32 i = 0; i < 8; ++i) {
        if (_ea8[i].hasProcById(tag->getActor(nullptr, nullptr)))
            return true;
    }

    auto* weapon = sead::DynamicCast<uking::act::Weapon>(tag->getActor(nullptr, nullptr));
    if (weapon && (weapon->_e50 & 1))
        return true;
    return false;
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
    if (auto* rideable = sead::DynamicCast<Rideable>(_1168))
        rideable->Unk_7100e8b2b8::_10 &= ~0x38u;
}

// Dispatches the registered effect callbacks (lane5's Unk_71023b30d8 family: single Actor*
// virtual slot 0) and forwards to Actor::m75.
void Enemy::m75() {
    for (auto it = _1110.begin(); it != _1110.end(); ++it)
        (*it)->sub_710022C55C(this);
    Actor::m75();
}

Rideable* Enemy::getHorseOptionsMaybe() {
    return sead::DynamicCast<Rideable>(_1168);
}

RideableBase* Enemy::m132() {
    return _1168;
}

Unk_7100e8b2b8* Enemy::getMotorcyclePriorityStuffMaybe() {
    return sead::DynamicCast<Rideable>(_1168);
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
    ksys::act::ActorLinkConstDataAccess accessor1;
    if (ksys::act::acquireActor(&_1180, &accessor1))
        accessor1.deleteLater(ksys::act::BaseProc::DeleteReason::_0);
    _1180.reset();

    ksys::act::ActorLinkConstDataAccess accessor2;
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

bool Enemy::sub_7100016284(s32 idx) {
    if (!_e80.isOnBit(idx))
        return false;
    auto* weapon = sead::DynamicCast<Weapon>(_c38[idx].getProc(nullptr, nullptr));
    if (!weapon)
        return false;
    return weapon->isParentEqual(uking::act::PlayerInfo::getSomeProcLink());
}

bool Enemy::sub_71000161A4(s32 idx) {
    if (!sub_7100016284(idx))
        return false;
    auto* weapon = sead::DynamicCast<Weapon>(_c38[idx].getProc(nullptr, nullptr));
    if (!weapon || !weapon->hasParentActor())
        return false;
    return !weapon->getParentLink().hasProcById(this);
}

void Enemy::sub_7100018A9C(f32 time) {
    _f50 = time;
    for (s32 i = 0; i < _c38.size(); ++i) {
        ksys::act::ActorLinkConstDataAccess accessor;
        ksys::act::acquireActor(&_c38[i], &accessor);
        sub_71002F1400(accessor, s32(time));
    }
}

void Enemy::sub_7100019C58(ksys::act::Actor* actor) {
    if (!actor)
        return;
    for (auto& link : _ea8) {
        if (link.hasProcById(actor)) {
            link.reset();
            return;
        }
    }
}

void Enemy::sub_7100019D38(const ksys::act::BaseProcLink& link) {
    if (!link.hasProc())
        return;
    for (auto& other : _ea8) {
        if (other == link) {
            other.reset();
            return;
        }
    }
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

void Enemy::m114(bool, bool) {
    if (_1168) {
        _1168->m9();
        if (_1170)
            _1170->dispatch();
    }
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

void Unk_7100013308::sub_71002DBC8C(const ksys::act::BaseProcLink& link, const sead::Matrix34f* mtx,
                                    const sead::Vector3f* pos) {
    _8 = link;
    _7c = 2;
    if (pos)
        _54 = *pos;
    else {
        ksys::act::ActorLinkConstDataAccess accessor;
        ksys::act::acquireActor(&_8, &accessor);
        _54 = accessor.getPreviousPos();
    }
    if (mtx) {
        mtx->getTranslation(_18);
        _24 = *mtx;
    } else {
        ksys::act::ActorLinkConstDataAccess accessor;
        ksys::act::acquireActor(&_8, &accessor);
        const sead::Matrix34f* m = &accessor.getActorMtx();
        _24 = *m;
        _24.getTranslation(_18);
    }
    _70 = _18;
    _80._1e = 1;
}

}  // namespace uking::act

Unk_7102357ab0::~Unk_7102357ab0() = default;

void Unk_7102357ab0::m4() {
    Unk_710244eaa0::m4();
    mActor->sub_71011DA868(&_1f0);
}

bool Unk_7102357ab0::m5(const ksys::act::ActorLinkConstDataAccess& accessor) {
    if (!Unk_710244eaa0::m5(accessor))
        return false;
    auto* rideable = accessor.getHorseOptions();
    if (!rideable)
        return false;
    if (!rideable->m22(uking::act::Unk_7100e8b2b8::Unk8::_2))
        return false;
    _1f0._68 = sead::Matrix34f::ident;
    _2a4 = 0;
    return true;
}

void Unk_7102357ab0::m6() {
    Unk_710244eaa0::m6();
    _30 &= ~0x40;
}

bool Unk_7102357ab0::m7() {
    if (!Unk_710244eaa0::m7())
        return false;
    const auto* rider = mActor->getParam()->getRes().mGParamList->getHorseRider();
    if (!rider)
        return false;
    _1f0.setName(rider->mRotBaseNode.ref());
    return true;
}

void Unk_7102357ab0::m8() {
    Unk_710244eaa0::m8();
    _1f0._68 = sead::Matrix34f::ident;
    _2a4 = 0;
    _30 &= ~0x80;
    mActor->sub_71011DA868(&_1f0);
}

const sead::SafeString& Unk_7102357ab0::getRootNodeName() const {
    const auto* rider = mActor->getParam()->getRes().mGParamList->getHorseRider();
    if (!rider)
        return sead::SafeString::cEmptyString;
    return rider->mRootNode.ref();
}

const sead::SafeString& Unk_7102357ab0::getSpineNodeName() const {
    const auto* rider = mActor->getParam()->getRes().mGParamList->getHorseRider();
    if (!rider)
        return sead::SafeString::cEmptyString;
    return rider->mSpineNode.ref();
}

namespace uking::act {

// NON_MATCHING: random-kind selection and parameter value selection use different branch layouts.
int Enemy::Unk_7100001aa4::sub_7100001AA4(f32 scale) {
    auto* random = sead::GlobalRandom::instance();
    if (_8 == 2) {
        const u32 choice = random->getU32(3) + random->getU32(3);
        if (choice < 2)
            _8 = 1;
        else if (choice < 4)
            _8 = 0;
        else
            _8 = 2;
    } else if (_8 == 0) {
        _8 = random->getU32(2) + 1;
    } else {
        _8 = random->getU32(3);
    }
    const auto* param = mActor->getParam()->getRes().mGParamList->getAttackInterval();
    s32 minimum;
    s32 maximum;
    switch (_8) {
    case 0:
        minimum = param->mShortAttackTimeMin.ref();
        maximum = param->mShortAttackTimeMax.ref();
        break;
    case 1:
        minimum = param->mMiddleAttackTimeMin.ref();
        maximum = param->mMiddleAttackTimeMax.ref();
        break;
    case 2:
        minimum = param->mLongAttackTimeMin.ref();
        maximum = param->mLongAttackTimeMax.ref();
        break;
    default:
        return 0;
    }
    const s32 time = minimum == maximum ? minimum : random->getS32Range(minimum, maximum);
    return s32(f32(time) * scale);
}

bool Enemy::sub_71000198E4(ksys::act::Actor* actor) {
    if (!actor)
        return false;
    s32 free_slot = -1;
    for (s32 i = 0; i < _ea8.size(); ++i) {
        if (_ea8[i].hasProcById(actor))
            return true;
        if (free_slot < 0 && !_ea8[i].hasProc())
            free_slot = i;
    }
    if (free_slot < 0)
        return false;
    _ea8[free_slot].acquire(actor, false);
    return true;
}

bool Enemy::sub_7100019A9C(const ksys::act::BaseProcLink& link) {
    if (!link.hasProc())
        return false;
    s32 free_slot = -1;
    for (s32 i = 0; i < _ea8.size(); ++i) {
        if (_ea8[i] == link)
            return true;
        if (free_slot < 0 && !_ea8[i].hasProc())
            free_slot = i;
    }
    if (free_slot < 0)
        return false;
    _ea8[free_slot] = link;
    return true;
}

}  // namespace uking::act
