#include <basis/seadNew.h>
#include "Game/Actor/actRideable.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/Resource/Actor/resResourceGParamList.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectAnimalUnit.h"

namespace uking::act {

RideableBase* RideableBase::make(sead::Heap* heap) {
    return new (heap, std::nothrow) RideableBase;
}

RideableBase::RideableBase() = default;

RideableBase::~RideableBase() = default;

bool RideableBase::m4(ksys::act::Actor* actor, sead::Heap* heap) {
    mActor = actor;
    _18.sub_7100E747E8(actor->getASList());
    _170 = 0;
    _178 = 0;
    getSomethingFromAnimalUnitSpeed();
    return true;
}

void RideableBase::m9() {
    _18.sub_7100E74890((_8 & 4) != 0, (_8 & 2) != 0, _154, _164);
    _8 |= 0x40;
}

// NON_MATCHING: flag-set and flag-clear operations are scheduled differently.
void RideableBase::sub_7100E63424() {
    const auto* animal = mActor->getParam()->getRes().mGParamList->getAnimalUnit();
    if (animal) {
        if (animal->mIsSetWaitASAtGear0.ref())
            _18._52 |= 2;
        else
            _18._52 &= ~2;
    }
}

void RideableBase::sub_7100E63900() {
    if (_8 & 0x20)
        _8 |= 0x80;
}

void RideableBase::sub_7100E6314C(Rank rank, f32 value, u32 id) {
    f32* ranked;
    u32* ids;
    switch (rank) {
    case 1:
        ranked = &_138;
        ids = &_140;
        break;
    case 2:
        ranked = &_13c;
        ids = &_144;
        break;
    default:
        return;
    }
    if (*ranked < value) {
        *ranked = value;
        *ids = id;
    }
}

// NON_MATCHING: the original computes the member address (`add x8, x0, #0x140`) and loads through it, with a 64-bit zero for
// the third result; we fold the offset into the load and return a 32-bit zero.
u64 RideableBase::sub_7100E63374() {
    if (_138 > 0.0f)
        return _140;
    if (_13c > 0.0f)
        return _144;
    return 0;
}

}  // namespace uking::act
