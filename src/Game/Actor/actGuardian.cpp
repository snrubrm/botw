#include "Game/Actor/actGuardian.h"
#include <basis/seadNew.h>
#include "Game/Actor/Damage/dmgDamageCallback.h"
#include "Game/Actor/Damage/dmgDamageManager.h"
#include "KingSystem/ActorSystem/actTag.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "Game/gameLastBossMgr.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Physics/Constraint/physConstraint.h"
#include "KingSystem/Resource/Actor/resResourceGParamList.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectGuardian.h"
#include "KingSystem/Sound/sndBgmMgr.h"
#include <random/seadGlobalRandom.h>
#include "KingSystem/ActorSystem/Attention/actActorAttention.h"
#include "KingSystem/Map/mapPlacementMgr.h"
#include "KingSystem/Physics/System/physInstanceSet.h"
#include "KingSystem/Physics/System/physRayCastBodyQuery.h"
#include "Game/Actor/aiUnk_71007377D4.h"

KSYS_VISIBILITY_HIDDEN extern const f32 sUnk_710235b9f0[70];
KSYS_VISIBILITY_HIDDEN extern u32 sUnk_71025af300;
KSYS_VISIBILITY_HIDDEN extern const f32 sUnk_710235ada0[30];



// 0x710235ab6c / 0x710235ab70: the Guardian target-distance tunables (15 / 25). Writable in the
// original, so clang loads them instead of folding the literals.
KSYS_VISIBILITY_HIDDEN f32 sUnk_710235ab6c = 15.0f;
KSYS_VISIBILITY_HIDDEN f32 sUnk_710235ab70 = 25.0f;

namespace uking::act {

// NON_MATCHING: the body is the same; clang sinks the constant/scale loads into the body here while
// the original hoists them above the rigid-body query, so the frame and register allocation differ.
void Guardian::Unk1::sub_7100044B68(sead::Vector3f* out, s32 index) {
    const sead::Vector2f& scale = _8->_15b8[index];
    const f32 radius = sUnk_710235b9f0[5];
    const sead::Vector3f offset(scale.x * radius, 0.0f, scale.y * radius);
    if (auto* body = sub_71000418C4()) {
        const sead::Matrix34f mtx = body->getTransform();
        out->x = mtx(0, 0) * offset.x + mtx(0, 1) * offset.y + mtx(0, 2) * offset.z + mtx(0, 3);
        out->y = mtx(1, 0) * offset.x + mtx(1, 1) * offset.y + mtx(1, 2) * offset.z + mtx(1, 3);
        out->z = mtx(2, 0) * offset.x + mtx(2, 1) * offset.y + mtx(2, 2) * offset.z + mtx(2, 3);
    }
}

ksys::act::BaseProc* Guardian::construct(const CreateArg& arg, sead::Heap* heap) {
    return new (heap, std::nothrow) Guardian(arg);
}

Guardian::~Guardian() {
    if (auto* mgr = uking::LastBossMgr::instance())
        mgr->sub_7100677F24(this);
}

void Guardian::onPreDeleteStart_(PrepareArg& arg) {
    _1908.sub_710066E15C();
}

void Guardian::onSleepRequested_(SleepWakeReason reason) {
    DynamicActor::onSleepRequested_(reason);

    ksys::act::ActorLinkConstDataAccess accessor;
    ksys::act::acquireActor(&_14f8, &accessor);
    accessor.sleep(reason);
    ksys::act::acquireActor(&_1508, &accessor);
    accessor.sleep(reason);
    for (s32 i = 0, n = _1518.size(); i < n; ++i) {
        ksys::act::acquireActor(&_1518[i], &accessor);
        accessor.sleep(reason);
    }
    for (s32 i = 0, n = _1528.size(); i < n; ++i) {
        ksys::act::acquireActor(&_1528[i], &accessor);
        accessor.sleep(reason);
    }
}

void Guardian::onWakeUpRequested_(SleepWakeReason reason) {
    Actor::onWakeUpRequested_(reason);

    ksys::act::ActorLinkConstDataAccess accessor;
    ksys::act::acquireActor(&_14f8, &accessor);
    accessor.setProperties(int(reason), accessor.getActorMtx(), nullptr, nullptr, nullptr, false, 0,
                           -1);
    ksys::act::acquireActor(&_1508, &accessor);
    accessor.setProperties(int(reason), accessor.getActorMtx(), nullptr, nullptr, nullptr, false, 0,
                           -1);
    for (s32 i = 0, n = _1518.size(); i < n; ++i) {
        ksys::act::acquireActor(&_1518[i], &accessor);
        accessor.setProperties(int(reason), accessor.getActorMtx(), nullptr, nullptr, nullptr,
                               false, 0, -1);
    }
    for (s32 i = 0, n = _1528.size(); i < n; ++i) {
        if (_14cc.isOnBit(i))
            continue;
        ksys::act::acquireActor(&_1528[i], &accessor);
        accessor.setProperties(int(reason), accessor.getActorMtx(), nullptr, nullptr, nullptr,
                               false, 0, -1);
    }
}

void Guardian::onEnterSleep_() {
    sub_71005DA114(this, &_18c8);
    Enemy::onEnterSleep_();
}

bool Guardian::m80(const ksys::MessageAck& ack) {
    if (!_17c0.sub_710070E070(ack))
        return false;
    if (_17c0._14)
        _14c8.set(0x20);
    return true;
}

bool Guardian::m33() {
    return getParam()->getRes().mGParamList->getGuardian()->mGuardianControllerType.ref() == 2;
}

const ksys::res::GParamListObjectGuardian* Guardian::sub_710003955C() const {
    return getParam()->getRes().mGParamList->getGuardian();
}

int Guardian::sub_7100033E10() const {
    switch (getParam()->getRes().mGParamList->getGuardian()->mGuardianControllerType.ref()) {
    case 0:
        return 0;
    case 1:
        return 6;
    case 2:
        return 3;
    default:
        return 0;
    }
}

u32 Guardian::sub_710003B1E4(u32 a) const {
    const int count = sub_7100033E10();
    if (!count)
        return 0;
    return 0xFFFFFFFFu / count * a;
}

f32 Guardian::sub_710003B238() const {
    const int count = sub_7100033E10();
    if (!count)
        return 0.0f;
    return f32(sead::BitFlagUtil::countOnBit(_14cc.getDirect())) / f32(count);
}

f32 Guardian::sub_710003B2C4() const {
    return getParam()->getRes().mGParamList->getGuardian()->mMaxSpeed.ref();
}

const sead::SafeString& Guardian::sub_710003B2EC() const {
    return getParam()->getRes().mGParamList->getGuardian()->mCannonBoneName.ref();
}

void Guardian::sub_7100034514(bool on) {
    _14c8.change(4, on);
}

// NON_MATCHING: the body is complete; this build lays the controller-type tests out as 2, 1, 0 and
// schedules the flag/body setup slightly differently, while the original tests 0, 1, 2.
// 0x71000374c4: the GuardianControllerType switch that adds/removes the two rigid bodies and moves
// the active one onto the inactive one when the controller type changes.
void Guardian::m73() {
    const auto* guardian = getParam()->getRes().mGParamList->getGuardian();
    if (!_1790 || !_17a0)
        return;

    const s32 controller_type = guardian->mGuardianControllerType.ref();
    const bool flag2 = _14c8.isOnBit(1);
    const u32 flags = _14c8.getDirect();
    const bool c = _1908._3c != 0;

    if (controller_type == 0) {
        const bool bit14 = flag2 != c;
        const u32 value = bit14 ? (flags | 0x4000) : (flags & ~0x4000u);
        _14c8.setDirect(value);
        if (!c) {
            _14c8.setDirect(value | 2);
            if (value & 0x4000) {
                _1790->addToWorld();
                if (_1780)
                    _1780->addToWorld();
            }
        } else {
            _14c8.setDirect(value & ~2u);
            if (value & 0x4000) {
                _1790->removeFromWorld();
                if (_1780)
                    _1780->removeFromWorld();
            }
        }
    } else if (controller_type == 1) {
        const u32 value = flag2 ? (flags & ~0x4002u) : (flags | 0x4000);
        _14c8.setDirect(value | 2);
    } else if (controller_type == 2) {
        if (!_1788 || !_1798)
            return;
        const bool bit14 = flag2 != c;
        const u32 value = bit14 ? (flags | 0x4000) : (flags & ~0x4000u);
        const u32 new_flags = c ? (value & ~2u) : (value | 2);
        _14c8.setDirect(new_flags);
        if (new_flags & 0x4000) {
            if (!c) {
                _1798->removeFromWorld();
                _1788->removeFromWorld();
                _17a0->addToWorld();
                _1790->addToWorld();
                _1790->setTransform(_1788->getTransform());
                _1790->setLinearVelocity(_1788->getLinearVelocity());
                _1790->setAngularVelocity(_1788->getAngularVelocity());
                _17a8->sub_7100F6AAA4(_1790, _1780);
                _17a8->sub_7100F69FF0();
                sub_71011DB364(_1790);
                sub_710011DBB8(_17a0);
            } else {
                _17a0->removeFromWorld();
                _1790->removeFromWorld();
                _1798->addToWorld();
                _1788->addToWorld();
                _1788->setTransform(_1790->getTransform());
                _1788->setLinearVelocity(_1790->getLinearVelocity());
                _1788->setAngularVelocity(_1790->getAngularVelocity());
                _17a8->sub_7100F6AAA4(_1788, _1780);
                _17a8->sub_7100F69FF0();
                sub_71011DB364(_1788);
                sub_710011DBB8(_1798);
            }
        }
    }

    Enemy::m73();
}

// 0x7100035a90: switches the guardian state. State 5 tells the registered last-boss transceiver
// that this guardian is present; states 12 / 13 toggle the "LockOn" attention client. The new state
// also gets a random +-1 sign in _14f0.
// NON_MATCHING: only the early "same state or 3 -> 2" check differs; the original hoists both
// equality csets above the first branch and combines them with and / tbnz, this build branches on
// each test.
void Guardian::sub_7100035A90(s32 state) {
    if (_14d8 == state || (_14d8 == 3 && state == 2))
        return;

    if (state == 5) {
        if (auto* mgr = LastBossMgr::instance()) {
            if (mgr->getMesTransceiverId().isRegistered())
                sendMessage(mgr->getMesTransceiverId(), ksys::MessageType(0x800000d), nullptr,
                            true);
        }
    } else if (state == 12 || state == 13) {
        if (mAttention) {
            if (auto* client = mAttention->getClientByName("LockOn"))
                client->setEnabled(_14d8 == 12);
        }
    }

    _14dc = 0.0f;
    _14f0 = s32(sead::GlobalRandom::instance()->getU32() & 2) - 1;
    _14d8 = state;
}

void Guardian::sub_710003B3FC() {
    _14c8.set(0x208);
    if (_15b0)
        _15b0->sub_7100042B40();
}

s32 Guardian::sub_710003B098() const {
    for (s32 i = 0; i < 5; ++i) {
        ksys::act::ActorLinkConstDataAccess accessor;
        ksys::act::acquireActor(&_1538[i], &accessor);
        if (accessor.isStateSleep())
            return i;
    }
    return -1;
}

bool Guardian::sub_710003B2A8() const {
    return sub_710003B098() >= 0;
}

// NON_MATCHING: the body is complete; this build schedules the position/start copies with stp and
// delays the start stores past the end computation, while the original stores each component first.
// 0x710003733c: after the static compound is ready, update the position holder; while flag bit 4 is
// set and a body exists, cast 3 m down and drop the flag (and the instance-set body) when it misses.
void Guardian::updatePositionMaybe() {
    const sead::Vector3f pos = getMtx().getTranslation();
    if (!ksys::map::PlacementMgr::instance()->isStaticCompoundReady(pos, false))
        return;

    _1908.sub_710066E178(pos);

    if (_14c8.isOnBit(4) && _1780) {
        ksys::phys::RayCastBodyQuery query(nullptr, ksys::phys::GroundHit::HitAll);
        query.enableLayer(ksys::phys::ContactLayer::EntityTree);
        query.enableLayer(ksys::phys::ContactLayer::EntityGround);
        query.enableLayer(ksys::phys::ContactLayer::EntityGroundObject);
        query.enableLayer(ksys::phys::ContactLayer::EntityObject);
        query.setNormalCheckingMode(ksys::phys::RayCast::NormalCheckingMode::DoNotCheck);
        const sead::Vector3f start = getMtx().getTranslation();
        const sead::Vector3f end = start - sead::Vector3f::ey * 3.0f;
        query.setStartAndEnd(start, end);
        query.setGroupHandlerIfAny(sub_710072E804(this, 0));
        if (!query.worldRayCast(ksys::phys::ContactLayerType::Entity)) {
            if (mPhysics && _1780)
                mPhysics->sub_7100FBAF18(_1780);
            _14c8.resetBit(4);
        }
    }

    Enemy::updatePositionMaybe();
}

// 0x710003b43c / 0x710003b4c8: the target (link at Enemy::_c48._8, position _c48._18) is closer than
// 15 / farther than 25.
bool Guardian::sub_710003B43C() const {
    if (!_c48._8.hasProc())
        return false;
    return (_c48._18 - getMtx().getTranslation()).length() < sUnk_710235ab6c;
}

bool Guardian::sub_710003B4C8() const {
    if (!_c48._8.hasProc())
        return true;
    return (_c48._18 - getMtx().getTranslation()).length() > sUnk_710235ab70;
}

void Guardian::sub_710003B564(s32* damage, s32*, u32*, u32* a4, s32* a5, DamageCallbackInfo*,
                              DamageManager* damage_mgr, s32 part) {
    if (*a5 == -1 || *a4 != 3)
        return;
    ksys::act::ActorLinkConstDataAccess accessor;
    ksys::act::acquireActor(damage_mgr->getAttacker(), &accessor);
    if (!accessor.hasTag(ksys::act::tags::AncientWeapon))
        return;
    const bool full = (part | 1) == 1;
    s32 value = getMaxLife();
    if (!full)
        value = sead::Mathf::ceil(value / 3.0f);
    *damage = value;
}

void Guardian::sub_710003B41C() {
    _14c8.set(0x208);
    if (_15b0)
        _15b0->sub_7100042B48();
}

void Guardian::sub_710003B090(u32 value) {
    _14d4 = value;
}

void Guardian::updateMtxFromPhysics() {
    if (auto* body = mMainBody.load()) {
        mMtx = body->getTransform();
        nullsub_4648();
    } else {
        Actor::updateMtxFromPhysics();
    }
}

ksys::phys::NavMeshCharacter* Guardian::m45() {
    if (_15b0)
        return _15b0->_30;
    return Actor::m45();
}

void Guardian::m44(ksys::phys::NavMeshCharacter* nav) {
    if (_15b0)
        _15b0->sub_7100042048();
    else
        Actor::m44(nav);
}

void Guardian::onDeleteRequested_(DeleteReason reason) {
    Enemy::onDeleteRequested_(reason);
    if (_14c8.isOnBit(20))
        return;
    if (auto* mgr = ksys::snd::sub_7100FFD7CC())
        mgr->sub_7100FFBE38(false, mId, _15b0 == nullptr);
    else if (auto* mgr2 = ksys::snd::sub_7100FFDB28())
        mgr2->sub_7100FF987C(false, mId, _15b0 == nullptr);
}

bool Guardian::sub_71000370B4() const {
    return _15cc < sUnk_710235ada0[0];
}

bool Guardian::sub_710003B554() const {
    return sUnk_71025af300 & 1;
}

bool Guardian::sub_71000380A8() const {
    return (sUnk_71025af300 & 0x80) == 0;
}

void Guardian::m34(sead::Vector3f* pos, f32* value) {
    if (_15a8) {
        *pos = _15a8->_0 - sead::Vector3f::ey * sUnk_710235ada0[29];
    }
    *value = sUnk_710235ada0[28];
}

}  // namespace uking::act

// NON_MATCHING: the first cast initializes RTTI before the null guard and selects its result.
uking::act::Guardian* sub_710003B738(const ksys::act::ActorLinkConstDataAccess& accessor) {
    auto* actor = sead::DynamicCast<ksys::act::Actor>(accessor.getProc());
    return sead::DynamicCast<uking::act::Guardian>(actor);
}

u32 sub_710003B71C(const ksys::act::ActorLinkConstDataAccess& accessor) {
    auto* guardian = sub_710003B738(accessor);
    return guardian ? guardian->_14d8 : 0;
}

