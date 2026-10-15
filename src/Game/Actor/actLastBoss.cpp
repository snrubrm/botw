#include "Game/Actor/actLastBoss.h"
#include <basis/seadNew.h>
#include "Game/Actor/actSiteBoss.h"
#include "KingSystem/Event/evtMetadata.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "Game/Actor/Player/actPlayerInfo.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Physics/System/physInstanceSet.h"
#include "KingSystem/System/VFR.h"
#include <prim/seadScopedLock.h>
#include "KingSystem/XLink/xlinkXLink.h"
#include "KingSystem/ActorSystem/actTag.h"

bool fadeSlowEffect();

namespace uking::act {

Unk_71025ae680* LastBoss::m178(sead::Heap* heap) {
    return new (heap) Unk_710244eb48(this);
}

namespace {
void forwardX17ToParts(ksys::act::Actor* actor, ksys::act::Unk117* arg) {
    if (!sead::IsDerivedFrom<Enemy>(actor))
        return;
    auto* enemy = static_cast<Enemy*>(actor);
    for (auto* part : enemy->_1128.mList) {
        if (auto* part_actor =
                sead::DynamicCast<ksys::act::Actor>(part->mLink.getProc(nullptr, nullptr)))
            part_actor->x_17(arg);
    }
}
}  // namespace

void LastBoss::initMaybe() {
    if (auto* x = _1250) {
        if (auto* y = x->_18)
            y->m0();
    }
    if (auto* body = findPhysicsBodyByName(sub_71007A250C()->cstr(), "BgSensor")) {
        if (!body->isAddedToWorld()) {
            body->addToWorld();
            body->setContactAll();
            body->setFlag1000000();
        }
    }
    Enemy::initMaybe();
}

// 0x71002c5978: m159() is the controller; DynamicCast<Unk_710244eb48> has its own function-local static.
void LastBoss::stunEnd() {
    if (auto* controller = sead::DynamicCast<Unk_710244eb48>(m159()))
        controller->sub_71006E252C();
}

void LastBoss::sub_71002C5E58(bool keep_effect) {
    auto lock = sead::makeScopedLock(_14ec);
    if (!_14e8.isOn(0x40))
        return;
    ksys::VFR::instance()->resetTimeMultiplier(4);
    if (auto* physics = getPhysics())
        physics->sub_7100FB9DB0(true);
    if (!keep_effect)
        fadeSlowEffect();
    _14e8.reset(0xc0);
    _14e8.set(0x80);
    _14f8._30.reset(0x40);
}

void LastBoss::sub_71002C5B3C() {
    if (auto* controller = sead::DynamicCast<Unk_710244eb48>(m159()))
        controller->_1c = true;
}

void LastBoss::sub_71002C6A78() {
    if (auto* controller = sead::DynamicCast<Unk_710244eb48>(m159()))
        controller->_1c = false;
}

void LastBoss::callHyruleCastleGanonDeadAndDemo145DemosIfDead() {
    if (_14e8.isOnBit(16))
        return;
    _14e8.setBit(16);
    ksys::evt::Metadata dead("HyruleCastle", "GanonDead");
    _1ab8.initWithEvent_(this, &dead);
    _1ab8.loadEvent();
    ksys::evt::Metadata demo("Demo145_0");
    _1c88.initWithEvent_(this, &demo);
    _1c88.loadEvent();
}

// NON_MATCHING: stack slots of the accessors and the message type are swapped; one `mov w0, wzr` is scheduled
// before the flag store.
bool LastBoss::transitionToSecondHalf_(f32 life_ratio) {
    const s32* life = getLife();
    const f32 current_life = life ? f32(*life) : 1.0f;
    const s32 max_life = getMaxLife();
    const f32 threshold = f32(max_life - getNumberOfClearedRemains() * 1000);
    if (!(threshold * life_ratio >= current_life))
        return false;

    if (_14e8.isOnBit(3)) {
        _14e8.setBit(14);
        return false;
    }
    if (_14e8.isOnBit(4))
        return true;

    ksys::evt::ResidentEvent* event;
    if (_14f8._30.isOnBit(4))
        event = &_18e8;
    else if (_14e4 == 1)
        event = &_1718;
    else
        event = &_1548;
    if (!event->callEvent(true))
        return false;

    ksys::act::ActorLinkConstDataAccess accessor;
    ksys::act::acquireActor(&PlayerInfo::getSomeProcLink(), &accessor);
    sendMessage(*accessor.getMessageTransceiverId(), ksys::MessageType(0x80000b2), nullptr, true);

    for (auto* part : _1128.mList) {
        if (!part->mLink.hasProcInCalcState())
            continue;
        ksys::act::ActorLinkConstDataAccess part_accessor;
        ksys::act::acquireActor(&part->mLink, &part_accessor);
        if (part_accessor.isStateCalc())
            part_accessor.sleep(ksys::act::BaseProc::SleepWakeReason::_0);
    }

    if (auto* controller = sead::DynamicCast<Unk_710244eb48>(m159()))
        controller->sub_71006E252C();
    sub_71007A36BC(this);
    _14f8._30.reset(0x300);
    sub_71002C5A14();
    callHyruleCastleGanonDeadAndDemo145DemosIfDead();
    sub_71002C5B3C();
    return true;
}

bool LastBoss::transitionToSecondHalf(f32 life_ratio, const sead::SafeString& event,
                                      const sead::SafeString& entry1, const sead::SafeString& entry2,
                                      const sead::SafeString& entry3) {
    loadAuraResidentEventsIfNeeded(event, entry1, entry2, entry3);
    if (_14e8.isOnBit(0))
        return false;
    if (!transitionToSecondHalf_(life_ratio))
        return false;
    _14e8.setBit(0);
    return true;
}

void LastBoss::loadAuraResidentEventsIfNeeded(const sead::SafeString& event, const sead::SafeString& entry1,
                                              const sead::SafeString& entry2,
                                              const sead::SafeString& entry3) {
    if (_14e8.isOnBit(15))
        return;
    _14e8.setBit(15);
    ksys::evt::Metadata metadata1(event.cstr(), entry1.cstr());
    _1548.initWithEvent_(this, &metadata1);
    _1548.loadEvent();
    ksys::evt::Metadata metadata2(event.cstr(), entry2.cstr());
    _1718.initWithEvent_(this, &metadata2);
    _1718.loadEvent();
    ksys::evt::Metadata metadata3(event.cstr(), entry3.cstr());
    _18e8.initWithEvent_(this, &metadata3);
    _18e8.loadEvent();
}

void LastBoss::sub_71002C5A14() {
    if (_1548.mEventFlow)
        _1548.unloadEvent();
    if (_1718.mEventFlow)
        _1718.unloadEvent();
    if (_18e8.mEventFlow)
        _18e8.unloadEvent();
}

void LastBoss::sub_71002C5DB4() {
    if (_1ab8.mEventFlow)
        _1ab8.unloadEvent();
    if (_1c88.mEventFlow)
        _1c88.unloadEvent();
}

void LastBoss::sub_71002C6930() {
    for (auto* part : _1128.mList) {
        if (!part->mLink.hasProcInCalcState())
            continue;
        ksys::act::ActorLinkConstDataAccess accessor;
        ksys::act::acquireActor(&part->mLink, &accessor);
        if (!accessor.isDeletedOrDeleting())
            accessor.deleteLater(ksys::act::BaseProc::DeleteReason::_0);
    }
}

void LastBoss::sub_71002C69CC() {
    if (_14f8.mDamageManager)
        return;
    if (auto* damage_mgr = getDamageMgr())
        damage_mgr->addDamageCallback(4, &_14f8);
}

void LastBoss::sub_71002C6A24() {
    if (!_14f8.mDamageManager)
        return;
    if (auto* damage_mgr = getDamageMgr())
        damage_mgr->removeDamageCallback(&_14f8);
}

void LastBoss::m117(ksys::act::Unk117* arg) {
    forwardX17ToParts(this, arg);
}

// NON_MATCHING: member types incomplete
LastBoss::LastBoss(const CreateArg& arg) : Enemy(arg) {}

LastBoss::~LastBoss() = default;

// NON_MATCHING: store schedule only (the original zeroes _14e8 / _14ec with an 8-byte store plus a separate
// word store, and keeps _14d0 / _14e4 / _14f0 separate)
ksys::act::BaseProc* LastBoss::construct(const CreateArg& arg, sead::Heap* heap) {
    return new (heap, std::nothrow) LastBoss(arg);
}

void LastBoss::m63() {
    Enemy::m63();
    _14e4 = 0;
    _14e8.makeAllZero();
    const s32 max_life = getMaxLife();
    s32* life = getLife();
    *life = max_life - getNumberOfClearedRemains() * 1000;
    _14f8._34 = 0;
    _1530 = 0;
    _1544 = 0;
    _14f8._30.makeAllZero();
    _14f0 = 1000.0f;
}

void LastBoss::x() {
    if (_14e8.isOnBit(17))
        return;
    if (auto* life = getLife()) {
        if (*life == 0)
            return;
    }
    _14e8.setBit(17);
    if (auto* as_list = mASList) {
        if (as_list->x_1(1, 0) != "Barrier_On")
            as_list->startAnimationMaybe(-1.0f, -1.0f, "Barrier_On", 1, 0, true);
    }
}

void LastBoss::update() {
    if (_14e8.isOnBit(17)) {
        _14e8.resetBit(17);
        auto* as_list = mASList;
        if (!as_list)
            return;
        auto* life = getLife();
        if (life && *life == 0)
            as_list->startAnimationMaybe(-1.0f, -1.0f, "Barrier_Off_Damage_Last", 1, 0, true);
        else if (isSlowTimeMaybe())
            as_list->startAnimationMaybe(-1.0f, -1.0f, "Barrier_Off_AtSlow", 1, 0, true);
        else
            as_list->startAnimationMaybe(-1.0f, -1.0f, "Barrier_Off", 1, 0, true);
    } else {
        auto* as_list = mASList;
        if (!as_list)
            return;
        if (as_list->x_1(1, 0) == "Barrier_Off" || as_list->x_1(1, 0) == "Barrier_Off_AtSlow") {
            if (isSlowTimeMaybe())
                as_list->startAnimationMaybe(-1.0f, -1.0f, "Barrier_Off_AtSlow", 1, 0, true);
            else
                as_list->startAnimationMaybe(-1.0f, -1.0f, "Barrier_Off", 1, 0, true);
        }
    }
}

void LastBoss::m76(ksys::VFR::ScopedDeltaSetter* setter) {
    setter->set(0x20, 0x10);
    _14e8.reset(0x80);
    Enemy::m76(setter);
}

void LastBoss::m77(ksys::VFR::ScopedDeltaSetter* setter) {
    setter->set(0x20, 0x10);
}

bool LastBoss::isGuard() {
    return false;
}

bool LastBoss::isGuardJust() {
    return _14f8._30.isOn(1);
}

bool LastBoss::sub_71002C6210(f32 value) const {
    return _14f0 < value;
}

bool LastBoss::m140() {
    return _14e8.isOnBit(9);
}

}  // namespace uking::act

// inline-only in the original; name is a guess (same helper as in acc::Weapon / acc::Armor).
static ksys::act::BaseProc* getProcIfActor(ksys::act::BaseProc* proc) {
    if (proc && sead::IsDerivedFrom<ksys::act::Actor>(proc))
        return proc;
    return nullptr;
}

uking::act::LastBoss* sub_71002C6B30(const ksys::act::ActorLinkConstDataAccess& accessor) {
    auto* actor = static_cast<ksys::act::Actor*>(getProcIfActor(accessor.getProc()));
    return sead::DynamicCast<uking::act::LastBoss>(actor);
}

bool sub_71002C6B0C(const ksys::act::ActorLinkConstDataAccess& accessor) {
    auto* boss = sub_71002C6B30(accessor);
    return boss ? boss->_14e4 == 1 : false;
}

void sub_71002C6408(sead::Vector3f* out, const sead::Vector3f& from, const sead::Vector3f& to, f32 y_offset) {
    sead::Vector3f pos = from;
    pos.y += y_offset;
    sead::Vector3f dir = pos - to;
    dir.normalize();
    *out = dir;
}

void sub_71002C64A0(sead::Vector3f* out, ksys::act::Actor* actor) {
    const sead::Vector3f pos = actor->getMtx().getTranslation();
    sead::Vector3f home;
    actor->getHomePos(&home);
    const sead::Vector3f diff = pos - home;
    sead::Vector3f side;
    side.setCross(diff, sead::Vector3f::ey);
    sead::Vector3f dir;
    dir.setCross(side, diff);
    dir.normalize();
    *out = pos + dir * 2.0f;
}

// Source owner unknown; this global helper is among LastBoss native neighbors.
// NON_MATCHING: the optional parts value uses a floating-point select instead of branches.
void sub_71002C67E8(f32 value, ksys::act::Actor* actor, bool sync_parts) {
    actor->x_3(value);
    if (!sync_parts)
        value = 0.0f;
    sub_71002C682C(actor, value);
}

void sub_71002C682C(ksys::act::Actor* actor, f32 value) {
    auto* enemy = sead::DynamicCast<uking::act::Enemy>(actor);
    if (!enemy)
        return;
    for (auto* part : enemy->_1128.mList) {
        if (!part->mLink.hasProcInCalcState())
            continue;
        ksys::act::ActorLinkConstDataAccess accessor;
        ksys::act::acquireActor(&part->mLink, &accessor);
        accessor.sub_7100D153A4(value);
    }
}

// NON_MATCHING: one parts-message loop replaces the native duplicated on/off loops.
void sub_71002C65DC(ksys::act::Actor* actor, bool on, bool sync_parts, bool xlink_flag) {
    actor->getActorFlags2().change(ksys::act::Actor::ActorFlag2::_20, on);
    if (auto* xlink = actor->getXLink())
        xlink->_cc.change(0x80000, xlink_flag);
    auto* enemy = sead::DynamicCast<uking::act::Enemy>(actor);
    if (!enemy)
        return;
    for (auto* part : enemy->_1128.mList) {
        if (!part->mLink.hasProcInCalcState())
            continue;
        ksys::act::ActorLinkConstDataAccess accessor;
        ksys::act::acquireActor(&part->mLink, &accessor);
        if (accessor.getProc() && accessor.hasTag(ksys::act::tags::SiteBossParts)) {
            actor->sendMessage(*accessor.getMessageTransceiverId(),
                               ksys::MessageType(on && sync_parts ? 0x3000001 : 0x3000002),
                               nullptr, true);
        }
    }
}

void sub_71002C65C8(ksys::act::Actor* actor, bool on, bool sync_parts) {
    sub_71002C65DC(actor, on, sync_parts, !on);
}
