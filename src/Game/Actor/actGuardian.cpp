#include "Game/Actor/actGuardian.h"
#include <basis/seadNew.h>
#include "Game/Damage/dmgDamageCallback.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "Game/gameLastBossMgr.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Resource/Actor/resResourceGParamList.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectGuardian.h"

namespace uking::act {

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

    ksys::act::ActorConstDataAccess accessor;
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

    ksys::act::ActorConstDataAccess accessor;
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

// NON_MATCHING: the original loads the 30.0 from rodata (adrp/ldr) instead of an fmov immediate
bool Guardian::sub_71000370B4() const {
    return _15cc < 30.0f;
}

}  // namespace uking::act
