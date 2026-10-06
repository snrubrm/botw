#include "Game/gameHorseMgr.h"
#include <prim/seadScopedLock.h>
#include "Game/Actor/actHorseBase.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actInfoCommon.h"
#include "KingSystem/ActorSystem/actInfoData.h"
#include "KingSystem/GameData/gdtManager.h"

namespace uking {

SEAD_SINGLETON_DISPOSER_IMPL(HorseMgr)

// NON_MATCHING: The compiler tail-calls hasProcById rather than normalizing its bool result.
bool HorseMgr::isLinkedToActor(ksys::act::Actor* actor) {
    return actor && _30.hasProcById(actor);
}

// NON_MATCHING: The compiler tail-calls hasProcById rather than normalizing its bool result.
bool HorseMgr::sub_7100E84AB8(ksys::act::Actor* actor) {
    return actor && mOwnedHorse.hasProcById(actor);
}

bool HorseMgr::sub_7100E85334(const ksys::act::BaseProcLink& link) const {
    return mOwnedHorse == link;
}

// The validity test of a horse record that x_3, sub_7100E8883C and sub_7100E8612C's callee all inline; it is
// the original's own (all five names non-empty, familiarity in [0, 1], collar and foot type not negative).
static bool isValid(const HorseMgr::HorseData& data) {
    return !sead::SafeString(data.actorName).isEmpty() && !sead::SafeString(data.userName).isEmpty() &&
           !sead::SafeString(data.reinsName).isEmpty() && !sead::SafeString(data.saddleName).isEmpty() &&
           !sead::SafeString(data.maneName).isEmpty() && data.familiarity <= 1.0f &&
           data.familiarity >= 0.0f && (data.collarType | data.footType) >= 0;
}

// 0x7100e83a08 (CSV x_8): the Horse_* flags of horse `index` through the regular getters.
// NON_MATCHING: register allocation (this / result registers swapped) and the placement of the first `and`.
bool HorseMgr::x_8(HorseData* data, s32 index) {
    using ksys::gdt::Manager;
    bool ok = Manager::instance()->getStr64(_1a4, &data->actorName, index);
    ok &= Manager::instance()->getF32(_19c, &data->familiarity, index);
    ok &= Manager::instance()->getParam().get().getStr64(&data->userName, "Horse_UserName", index);
    ok &= Manager::instance()->getParam().get().getStr64(&data->reinsName, "Horse_ReinsName", index);
    ok &= Manager::instance()->getParam().get().getStr64(&data->saddleName, "Horse_SaddleName", index);
    ok &= Manager::instance()->getParam().get().getStr64(&data->maneName, "Horse_ManeName", index);
    ok &= Manager::instance()->getParam().get().getStr64(&data->amiiboUidHash, "Horse_AmiiboUidHash", index);
    ok &= Manager::instance()->getParam().get().getS32(&data->collarType, "Horse_CollarType", index);
    ok &= Manager::instance()->getParam().get().getS32(&data->footType, "Horse_FootType", index);
    ok &= Manager::instance()->getParam().get().getS32(&data->rideTimeSec, "Horse_RideTimeSec", index);
    ok &= Manager::instance()->getParam().get().getBool(&data->familiarityChecked,
                                                        "Horse_IsFamiliarityChecked", index);
    return ok;
}

// 0x7100e854ec: the Horse_* flags of horse `index`; the first two are read through their handles (buffer 1, failing
// while `_40000` is set), the others by name.
// NON_MATCHING: the original lays out the handle unwrapping of the first two reads differently (the direct path first).
bool HorseMgr::sub_7100E854EC(HorseData* data, s32 index) {
    using ksys::gdt::Manager;
    bool ok = Manager::instance()->getStr64Buffer1(_1a4, &data->actorName, index);
    ok &= Manager::instance()->getF32Buffer1(_19c, &data->familiarity, index);
    ok &= Manager::instance()->getParam().get1().getStr64(&data->userName, "Horse_UserName", index);
    ok &= Manager::instance()->getParam().get1().getStr64(&data->reinsName, "Horse_ReinsName", index);
    ok &= Manager::instance()->getParam().get1().getStr64(&data->saddleName, "Horse_SaddleName", index);
    ok &= Manager::instance()->getParam().get1().getStr64(&data->maneName, "Horse_ManeName", index);
    ok &= Manager::instance()->getParam().get1().getStr64(&data->amiiboUidHash, "Horse_AmiiboUidHash",
                                                          index);
    ok &= Manager::instance()->getParam().get1().getS32(&data->collarType, "Horse_CollarType", index);
    ok &= Manager::instance()->getParam().get1().getS32(&data->footType, "Horse_FootType", index);
    ok &= Manager::instance()->getParam().get1().getS32(&data->rideTimeSec, "Horse_RideTimeSec", index);
    ok &= Manager::instance()->getParam().get1().getBool(&data->familiarityChecked,
                                                         "Horse_IsFamiliarityChecked", index);
    return ok;
}

// NON_MATCHING: only the operand order of the `and` on the flags differs (see isFlagOn).
void HorseMgr::sub_7100E8533C(HorseData* data, s32 index) {
    using ksys::gdt::Manager;
    if (!isFlagOn(Flag::_0))
        return;
    Manager::instance()->setStr64(data->actorName, _1a4, index);
    Manager::instance()->setF32(data->familiarity, _19c, index);
    Manager::instance()->setStr64(data->userName, "Horse_UserName", index);
    Manager::instance()->setStr64(data->reinsName, "Horse_ReinsName", index);
    Manager::instance()->setStr64(data->saddleName, "Horse_SaddleName", index);
    Manager::instance()->setStr64(data->maneName, "Horse_ManeName", index);
    Manager::instance()->setStr64(data->amiiboUidHash, "Horse_AmiiboUidHash", index);
    Manager::instance()->setS32(data->collarType, "Horse_CollarType", index);
    Manager::instance()->setS32(data->footType, "Horse_FootType", index);
    Manager::instance()->setS32(data->rideTimeSec, "Horse_RideTimeSec", index);
    Manager::instance()->setBool(data->familiarityChecked, "Horse_IsFamiliarityChecked", index);
}

// 0x7100e89b20: the DeadHorse_* flags of dead horse `index` (no `this`).
bool HorseMgr::sub_7100E89B20(HorseData* data, s32 index) {
    using ksys::gdt::Manager;
    bool ok = Manager::instance()->getParam().get1().getStr64(&data->actorName, "DeadHorse_ActorName", index);
    ok &= Manager::instance()->getParam().get1().getF32(&data->familiarity, "DeadHorse_Familiarity", index);
    ok &= Manager::instance()->getParam().get1().getS32(&data->collarType, "DeadHorse_CollarType", index);
    ok &= Manager::instance()->getParam().get1().getS32(&data->footType, "DeadHorse_FootType", index);
    ok &= Manager::instance()->getParam().get1().getStr64(&data->userName, "DeadHorse_UserName", index);
    ok &= Manager::instance()->getParam().get1().getStr64(&data->reinsName, "DeadHorse_ReinsName", index);
    ok &= Manager::instance()->getParam().get1().getStr64(&data->saddleName, "DeadHorse_SaddleName", index);
    ok &= Manager::instance()->getParam().get1().getStr64(&data->maneName, "DeadHorse_ManeName", index);
    ok &= Manager::instance()->getParam().get1().getStr64(&data->amiiboUidHash, "DeadHorse_AmiiboUidHash",
                                                          index);
    ok &= Manager::instance()->getParam().get1().getS32(&data->rideTimeSec, "DeadHorse_RideTimeSec", index);
    ok &= Manager::instance()->getParam().get1().getS32(&data->deadCause, "DeadHorse_DeadCause", index);
    return ok;
}

// NON_MATCHING: only the operand order of the `and` on the flags differs (see isFlagOn).
void HorseMgr::sub_7100E88A08(HorseData* data, s32 index) {
    using ksys::gdt::Manager;
    if (!isFlagOn(Flag::_0))
        return;
    Manager::instance()->setStr64(data->actorName, "DeadHorse_ActorName", index);
    Manager::instance()->setF32(data->familiarity, "DeadHorse_Familiarity", index);
    Manager::instance()->setS32(data->collarType, "DeadHorse_CollarType", index);
    Manager::instance()->setS32(data->footType, "DeadHorse_FootType", index);
    Manager::instance()->setStr64(data->userName, "DeadHorse_UserName", index);
    Manager::instance()->setStr64(data->reinsName, "DeadHorse_ReinsName", index);
    Manager::instance()->setStr64(data->saddleName, "DeadHorse_SaddleName", index);
    Manager::instance()->setStr64(data->maneName, "DeadHorse_ManeName", index);
    Manager::instance()->setStr64(data->amiiboUidHash, "DeadHorse_AmiiboUidHash", index);
    Manager::instance()->setS32(data->rideTimeSec, "DeadHorse_RideTimeSec", index);
    Manager::instance()->setS32(data->deadCause, "DeadHorse_DeadCause", index);
}

// 0x7100e86340: picks the horse with the highest familiarity out of the five records (ties: the one with the highest
// gear top charge count). The original compares the charge count of the best record with itself.
// NON_MATCHING: the original indexes the best record with a clamped index (`index < 5 ? index : 0`, like
// SafeArray::operator[]) which a HorseData* parameter cannot express; the loop registers differ because of it.
bool HorseMgr::sub_7100E86340(HorseData* data, s32* index) {
    s32 best = -1;
    s32 best_charge = -1;
    for (s32 i = 0; i != 5; ++i) {
        const HorseData& d = data[i];
        if (x_8(&data[i], i) && !sead::SafeString(d.actorName).isEmpty() &&
            !sead::SafeString(d.userName).isEmpty() && !sead::SafeString(d.reinsName).isEmpty() &&
            !sead::SafeString(d.saddleName).isEmpty() && !sead::SafeString(d.maneName).isEmpty() &&
            d.familiarity >= 0.0f && d.familiarity <= 1.0f && d.collarType >= 0 && d.footType >= 0) {
            if (best < 0) {
                best = i;
            } else {
                const HorseData& b = data[best];
                if (d.familiarity == b.familiarity) {
                    if (best_charge < 0)
                        best_charge = ksys::act::getHorseGearTopChargeNum(ksys::act::InfoData::instance(),
                                                                         b.actorName);
                    const s32 charge =
                        ksys::act::getHorseGearTopChargeNum(ksys::act::InfoData::instance(), b.actorName);
                    if (charge > best_charge) {
                        best = i;
                        best_charge = charge;
                    }
                } else if (d.familiarity > b.familiarity) {
                    best = i;
                    best_charge = -1;
                }
            }
        }
    }
    if (best < 0)
        return false;
    *index = best;
    return true;
}

// NON_MATCHING: the original lays out the loop blocks differently (the early exits of the validity checks come
// after the success path) and has the flags first in the isOnBit `and`.
s32 HorseMgr::getNumRegisteredHorses() {
    s32 count = 5;
    if (isFlagOn(Flag::_0)) {
        count = 0;
        auto lock = sead::makeScopedLock(_230);
        for (s32 i = 0; i != 5; ++i) {
            HorseData data;
            if (!sub_7100E854EC(&data, i) || !isValid(data)) {
                if (i == _d0) {
                    _d0 = -1;
                    ksys::gdt::Manager::instance()->setS32(-1, _1a0);
                }
            } else {
                if (i != count) {
                    sub_7100E8533C(&data, count);
                    if (i == _d0) {
                        _d0 = count;
                        ksys::gdt::Manager::instance()->setS32(count, _1a0);
                    }
                }
                ++count;
            }
        }
    }
    return count;
}

// NON_MATCHING: only the operand order of the `and` on the flags differs.
s32 HorseMgr::getNumDeadHorsesRegistered() {
    if (!isFlagOn(Flag::_0))
        return 5;
    s32 count = 0;
    for (s32 i = 0; i != 5; ++i) {
        HorseData data;
        if (sub_7100E89B20(&data, i) && isValid(data)) {
            if (i != count)
                sub_7100E88A08(&data, count);
            ++count;
        }
    }
    return count;
}

// NON_MATCHING: the original tests the flag with `cmp w8, #0 / cset ne` before the `and` (we get `and` + `and #1`).
bool HorseMgr::isSelectedHorseFamiliarityChecked() {
    bool result = false;
    {
        auto lock = sead::makeScopedLock(_230);
        if (static_cast<u32>(_d0) <= 4) {
            bool checked = false;
            result = ksys::gdt::Manager::instance()->getParam().get().getBool(
                         &checked, "Horse_IsFamiliarityChecked", _d0) &&
                     checked;
        }
    }
    return result;
}

// NON_MATCHING: only the operand order of the and / orr on the flags differs (the original has the flags first) and the
// placement of the final `*type = ...` store.
s32 HorseMgr::sub_7100E8612C(RiddenAnimalType* type) {
    _228.resetBit(9);
    _228.resetBit(10);
    ksys::act::ActorConstDataAccess accessor;
    if (ksys::act::acquireActor(&mOwnedHorse, &accessor) && _d0 >= 0) {
        *type = RiddenAnimalType(act::sub_7100E6ECC4(accessor));
        return _d0;
    }
    sead::SafeArray<HorseData, 5> data;
    s32 found;
    if (sub_7100E86340(data.getBufferPtr(), &found)) {
        const s32 index = found;
        _d0 = index;
        if (isFlagOn(Flag::_0))
            ksys::gdt::Manager::instance()->setS32(index, _1a0);
        setFlagOn(Flag::_9);
        *type = RiddenAnimalType(ksys::act::getHorseUnitRiddenAnimalType(
            ksys::act::InfoData::instance(), data[index].actorName));
    } else {
        if (_d0 >= 0)
            _d0 = -1;
        setFlagOn(Flag::_10);
        *type = RiddenAnimalType::_1;
        return -1;
    }
    return _d0;
}

bool HorseMgr::sub_7100E86CF4() {
    return _80.isAllocatedOrFailed() && !_80.isProcReady() && !_80.hasProcCreationFailed();
}

bool HorseMgr::sub_7100E86D44() {
    if (_80.isAllocatedOrFailed()) {
        setFlagOn(Flag::_8);
        return true;
    }
    return false;
}

bool HorseMgr::sub_7100E87710() {
    if (mOwnedHorse.hasProc()) {
        setFlagOn(Flag::_3);
        return true;
    }
    return false;
}

bool HorseMgr::sub_7100E875EC() {
    bool result = false;
    ksys::act::ActorConstDataAccess accessor;
    if (ksys::act::acquireActor(&mOwnedHorse, &accessor)) {
        act::sub_7100E6E98C(accessor, false);
        setFlagOn(Flag::_2);
        result = true;
    }
    return result;
}

bool HorseMgr::sub_7100E87340(const sead::SafeString& name, sead::Heap* heap) {
    bool result = false;
    ksys::act::ActorConstDataAccess accessor;
    if (ksys::act::acquireActor(&mOwnedHorse, &accessor)) {
        act::sub_7100E6E98C(accessor, true);
        result = true;
        act::sub_7100E6E140(accessor, name, heap);
    }
    return result;
}

bool HorseMgr::sub_7100E87424(const sead::SafeString& name, sead::Heap* heap) {
    bool result = false;
    ksys::act::ActorConstDataAccess accessor;
    if (ksys::act::acquireActor(&mOwnedHorse, &accessor)) {
        act::sub_7100E6E98C(accessor, true);
        result = true;
        act::sub_7100E6E404(accessor, name, heap);
    }
    return result;
}

bool HorseMgr::sub_7100E87508(const sead::SafeString& name, sead::Heap* heap) {
    bool result = false;
    ksys::act::ActorConstDataAccess accessor;
    if (ksys::act::acquireActor(&mOwnedHorse, &accessor)) {
        act::sub_7100E6E98C(accessor, true);
        result = true;
        act::sub_7100E6E6C8(accessor, name, heap);
    }
    return result;
}

void HorseMgr::sub_7100E873BC(const sead::SafeString& name, sead::Heap* heap) {
    ksys::act::ActorConstDataAccess accessor;
    if (ksys::act::acquireActor(&mOwnedHorse, &accessor)) {
        act::sub_7100E6E98C(accessor, false);
        act::sub_7100E6E140(accessor, name, heap);
    }
}

void HorseMgr::sub_7100E874A0(const sead::SafeString& name, sead::Heap* heap) {
    ksys::act::ActorConstDataAccess accessor;
    if (ksys::act::acquireActor(&mOwnedHorse, &accessor)) {
        act::sub_7100E6E98C(accessor, false);
        act::sub_7100E6E404(accessor, name, heap);
    }
}

void HorseMgr::sub_7100E87584(const sead::SafeString& name, sead::Heap* heap) {
    ksys::act::ActorConstDataAccess accessor;
    if (ksys::act::acquireActor(&mOwnedHorse, &accessor)) {
        act::sub_7100E6E98C(accessor, false);
        act::sub_7100E6E6C8(accessor, name, heap);
    }
}

}  // namespace uking
