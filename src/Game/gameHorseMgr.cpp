#include "Game/gameHorseMgr.h"
#include <prim/seadScopedLock.h>
#include "Game/Actor/actHorseBase.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actInfoCommon.h"
#include "KingSystem/ActorSystem/actInfoData.h"
#include "KingSystem/GameData/gdtManager.h"

namespace uking {

// NON_MATCHING: The compiler tail-calls hasProcById rather than normalizing its bool result.
bool HorseMgr::isLinkedToActor(ksys::act::Actor* actor) {
    return actor && _30.hasProcById(actor);
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

// NON_MATCHING: the original lays out the loop blocks differently (the early exits of the validity checks come
// after the success path) and uses the other operand order for the isOnBit mask.
s32 HorseMgr::getNumRegisteredHorses() {
    s32 count = 5;
    if (_228.isOnBit(Flag(Flag::_0))) {
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

// NON_MATCHING: stack layout only (the original keeps the horse record at sp+8 and shares the Flag temporary's slot
// with it) and the isOnBit mask operand order.
s32 HorseMgr::getNumDeadHorsesRegistered() {
    if (!_228.isOnBit(Flag(Flag::_0)))
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

// NON_MATCHING: stack layout only (the original shares one slot for the Flag temporaries, ours uses three).
s32 HorseMgr::sub_7100E8612C(s32* type) {
    _228.resetBit(9);
    _228.resetBit(10);
    ksys::act::ActorConstDataAccess accessor;
    if (ksys::act::acquireActor(&mOwnedHorse, &accessor) && _d0 >= 0) {
        *type = act::sub_7100E6ECC4(accessor);
        return _d0;
    }
    sead::SafeArray<HorseData, 5> data;
    s32 found;
    if (sub_7100E86340(data.getBufferPtr(), &found)) {
        const s32 index = found;
        _d0 = index;
        if (_228.isOnBit(Flag(Flag::_0)))
            ksys::gdt::Manager::instance()->setS32(index, _1a0);
        _228.setBit(Flag(Flag::_9));
        *type = ksys::act::getHorseUnitRiddenAnimalType(ksys::act::InfoData::instance(),
                                                        data[index].actorName);
    } else {
        if (_d0 >= 0)
            _d0 = -1;
        _228.setBit(Flag(Flag::_10));
        *type = 1;
        return -1;
    }
    return _d0;
}

}  // namespace uking
