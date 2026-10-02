#include "KingSystem/ActorSystem/actActorAtk.h"
#include <basis/seadNew.h>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAttackSensor.h"

namespace ksys::act {

ActorAtk::ActorAtk(Actor* actor) : Unk_71025ae640(actor) {}

ActorAtk* ActorAtk::makeForActor(Actor* actor, sead::Heap* heap) {
    auto* atk = new (heap) ActorAtk(actor);
    if (atk && !atk->init(heap)) {
        atk->free();
        delete atk;
        atk = nullptr;
    }
    return atk;
}

void ActorAtk::m5() {
    _78 = 0;
    if (mActor->getProfile() == "MapConstActive")
        _78 |= 1;
    if (_18)
        _18->reset();
    if (_48)
        _48->sub_71007A124C();
}

bool ActorAtk::reset() {
    if (_18)
        _18->reset();
    if (_48)
        _48->sub_71007A124C();
    return true;
}

void ActorAtk::m13() {
    if (_18)
        _18->reset();
    if (_48)
        _48->sub_71007A124C();
}

void ActorAtk::m8() {}

void ActorAtk::m9() {
    if (_18) {
        _18->reset();
        _18->sub_710079EFBC(&_30, mActor);
        _18->sub_710079E958(&_20, mActor);
    }
    if (_48) {
        _48->sub_71007A124C();
        _48->sub_71007A1C40(&_60, mActor);
        _48->sub_71007A12CC(&_50, mActor);
    }
}

s32 ActorAtk::getNumAttackInfoMaybe() const {
    if (!_18)
        return 0;
    return _18->mNumAttackInfo;
}

s32 ActorAtk::sub_710079E270() const {
    if (!_48)
        return 0;
    return _48->mNum;
}

ActorAtk::~ActorAtk() = default;

bool ActorAtk::m10() {
    if (!_48)
        return false;
    return _48->mNum > 0;
}

bool ActorAtk::hasAttackInfoMaybe() {
    if (!_18)
        return false;
    return _18->mNumAttackInfo > 0;
}

AttackSensor::AttackSensor(Actor* actor) : PhysicsUserTag(actor) {}

void AttackSensor::activateAttackSensor(u32 a1, u32 a2, u32 a3, u32 a4, f32 a5, u32 a6, u32 a7,
                                        u32 a8, bool a11, u32 a9, u32 a10) {
    _18 = a1;
    _1c = a2;
    _24 = a3;
    _28 = a4;
    _2c = a5;
    _30 = a6;
    _34 = a7;
    _38 = a8;
    _3c = a9;
    _40 = a10;
    _48 = a11;
}

}  // namespace ksys::act
