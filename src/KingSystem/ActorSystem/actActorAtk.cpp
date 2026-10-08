#include "KingSystem/ActorSystem/actActorAtk.h"
#include <basis/seadNew.h>
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actAttackSensor.h"
#include "KingSystem/ActorSystem/Profiles/actPlayerOrEnemy.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/Physics/System/physInstanceSet.h"

namespace ksys::act {

namespace {
ActorAtk::Struct7::AttackInfo sDefaultAttackInfo;
}  // namespace

// NON_MATCHING: Compiler separates fallback paths and default-record addressing.
ActorAtk::Struct7::AttackInfo* ActorAtk::getAttackInfo(int idx) const {
    if (_18 && idx < _18->mNumAttackInfo)
        return &_18->mAttackInfos[idx];
    return &sDefaultAttackInfo;
}

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

void ActorAtk::free() {
    _20.freeBuffer();
    _30.freeBuffer();
    _50.freeBuffer();
    _60.freeBuffer();
    if (_18) {
        delete _18;
        _18 = nullptr;
    }
    if (_48) {
        delete _48;
        _48 = nullptr;
    }
    if (_40) {
        delete _40;
        _40 = nullptr;
    }
    if (_70) {
        delete _70;
        _70 = nullptr;
    }
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

void ActorAtk::sub_710079E344(AttackSensor2Listener* listener) {
    if (auto* sensor = _70)
        sensor->_20.pushBack(listener);
}

void ActorAtk::sub_710079E3B8(AttackSensor2Listener* listener) {
    if (_70)
        listener->erase();
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

void ActorAtk::m7() {
    auto* actor = mActor;
    if (auto* list = actor->getASList()) {
        if (list->sub_710115FBC8(0x20, nullptr, &as::ASList::Unk2::sub_710116383C, true))
            sub_71007A397C(actor);
        if (list->sub_710115FBC8(0x20, nullptr, &as::ASList::Unk2::sub_710116388C, true))
            sub_71007A3800(actor);
    }
    if (auto* sensor = _40) {
        const bool value = sensor->_49;
        sensor->_49 = false;
        sensor->_4a = value;
    }
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

// NON_MATCHING: the original counts remaining entries down; the range iterator counts up.
bool sub_71007A0E18(const sead::RingBuffer<ActorAtk::Unk_710079e64c::HistoryEntry>& history,
                   BaseProc* proc) {
    ActorConstDataAccess accessor(proc);
    if (!accessor.hasProc())
        return false;
    const u32 id = accessor.getId();
    for (const auto& entry : history) {
        if (entry.actor_id == id)
            return true;
    }
    return false;
}

// NON_MATCHING: the compiler inlines the history lookup; the original calls it.
bool ActorAtk::sub_710079E300(BaseProc* proc) {
    if (_48)
        return sub_71007A0E18(_48->_808, proc);
    return false;
}

void ActorAtk::sub_710079E318() {
    if (_48)
        _48->_808.clear();
}

void ActorAtk::sub_710079E32C(const ActorAtk& other) {
    if (_18 && other._18)
        _18->sub_710079F208(*other._18);
}

}  // namespace ksys::act

bool actorHasTgtBody(ksys::act::Actor* actor) {
    auto* physics = actor->getPhysics();
    if (!physics)
        return false;
    if (sead::IsDerivedFrom<ksys::act::PlayerOrEnemy>(actor))
        return true;
    if (physics->findBodyGroupByName(*sub_71007A24BC()))
        return true;
    return physics->findBodyGroupByName(*sub_71007A24D0()) != nullptr;
}
