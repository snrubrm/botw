#include "Game/Actor/actSwarm.h"
#include <basis/seadNew.h>
#include <math/seadMatrixCalcCommon.h>
#include "Game/gameStasisMgr.h"
#include "KingSystem/ActorSystem/actActorSystem.h"
#include "KingSystem/ActorSystem/AS/ASList.h"

namespace uking::act {

Swarm::Swarm(const CreateArg& arg) : Enemy(arg) {}

Unk_71025ae680* Swarm::m178(sead::Heap* heap) {
    return new (heap) Unk_710244ff68(this);
}

bool Swarm::startPreparingForPreDelete_() {
    bool ready = true;
    for (s32 i = 0; i < _14c8.size(); ++i) {
        if (auto* unit = _14c8[i])
            ready &= unit->m9();
    }
    if (!ready)
        return false;
    return Enemy::startPreparingForPreDelete_();
}

// NON_MATCHING: member types incomplete
Swarm::~Swarm() = default;

// NON_MATCHING: store schedule only: the original stores the units buffer pointer (_14d0) first, we merge it into
// the zeroing of _14d8 .. _14f0
ksys::act::BaseProc* Swarm::construct(const CreateArg& arg, sead::Heap* heap) {
    return new (heap, std::nothrow) Swarm(arg);
}

void Swarm::m68() {
    if (_14d8)
        _14d8->sub_710115CA28();
    if (_14e0)
        _14e0->sub_710115CA28();
    if (_14e8)
        _14e8->sub_710115CA28();
    if (_14f0)
        _14f0->sub_710115CA28();
    Actor::m68();
}

void Swarm::m76(ksys::VFR::ScopedDeltaSetter* setter) {
    Enemy::m76(setter);
    if (mActorFlags2.isOn(ActorFlag2::_1) || mActorFlags2.isOn(ActorFlag2::_40) ||
        !mSpecialJobTypesMaskOverride.isOnBit(0))
        return;
    if (_14d8)
        _14d8->sub_710115C53C();
    if (_14e0)
        _14e0->sub_710115C53C();
    if (_14e8)
        _14e8->sub_710115C53C();
    if (_14f0)
        _14f0->sub_710115C53C();
}

void Swarm::setMtx(const sead::Matrix34f& mtx, bool a2, bool a3) {
    Actor::setMtx(mtx, a2, a3);
    sead::Matrix34CalcCommon<f32>::inverse(_15b8, mMtx);
}

bool Swarm::m81(const ksys::Message& message) {
    if (message.getType() == ksys::MessageType(0x3000003)) {
        Enemy::m81(message);
        _1614 = true;
        if (auto* sender = ksys::act::ActorSystem::instance()->getStasisMessageSender())
            sender->sendMessage(this, ksys::MessageType(0x3000004), true);
        return true;
    }

    const ksys::MessageType type = message.getType();
    const bool handled = Enemy::m81(message);
    if (type == ksys::MessageType(0x3000004)) {
        clearFlag(ActorFlag::_9);
        return true;
    }
    return handled;
}

void Swarm::sub_71002D47D4(const sead::SafeString& name) {}

}  // namespace uking::act
