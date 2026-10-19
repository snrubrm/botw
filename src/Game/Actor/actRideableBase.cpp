#include <basis/seadNew.h>
#include <math/seadMathCalcCommon.h>
#include "Game/Actor/actRideable.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/Resource/Actor/resResourceGParamList.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectAnimalUnit.h"
#include "KingSystem/Resource/resHandle.h"

namespace uking::act {

RideableBase::SpeedEntry::Gear sUnk_7102603058{};

// 0x710259d120 (placeholder name): the animal animation-driven speed resource handle.
ksys::res::Handle sUnk_710259D120;

// 0x7100e625e0 (CSV name): loads the shared animal animation-driven speed table and builds the
// animal move name table.
void loadAnimationDrivenSpeedAnimal() {
    sUnk_710259D120.load("AnimationDrivenSpeed/AnimalUnitSpeed.bin", nullptr, nullptr);
    formatAnimalMoveStrings();
}

RideableBase* RideableBase::make(sead::Heap* heap) {
    return new (heap, std::nothrow) RideableBase;
}

RideableBase::RideableBase() = default;

void RideableBase::sub_7100E639C4() {
    const auto* animal = mActor->getParam()->getRes().mGParamList->getAnimalUnit();
    if (animal) {
        _a0._40 = &animal->mSteeringOutputAvoidanceLerpRatio.ref();
        _a0._48 = &sUnk_7101EC1904;
    }
}

RideableBase::~RideableBase() = default;

bool RideableBase::m4(ksys::act::Actor* actor, sead::Heap* heap) {
    mActor = actor;
    _18.sub_7100E747E8(actor->getASList());
    _170 = nullptr;
    _178 = 0;
    getSomethingFromAnimalUnitSpeed();
    return true;
}

// NON_MATCHING: native enum stack temporaries and separate state branches are folded into register selection.
int RideableBase::m11(int mode) {
    s32 limit = _168;
    if (mode == 0) {
        if (_138 > 0.0f)
            limit = sead::Mathi::min(limit, 1);
        else if (_13c > 0.0f)
            limit = sead::Mathi::min(limit, 2);
    }
    s32 gear = _18._b == 0 ? _18._9 : _18._b;
    if ((_18._9 == _18._b && _18._8 == _18._a) || !(_18._c > 0.0f))
        --gear;
    return sead::Mathi::max(limit, gear);
}

void RideableBase::m9() {
    _18.sub_7100E74890((_8 & 4) != 0, (_8 & 2) != 0, _154, _164);
    _8 |= 0x40;
}

void RideableBase::sub_7100E63424() {
    const auto* animal = mActor->getParam()->getRes().mGParamList->getAnimalUnit();
    if (animal) {
        _18._52 = animal->mIsSetWaitASAtGear0.ref() ? (_18._52 | 2) : (_18._52 & ~2);
    }
}

// NON_MATCHING: the body is complete, but the original keeps the current gear and the gear
// argument in stack slots (the register allocator spills them in the entry block) and reloads
// them for the two comparisons, while this build keeps them in registers.
// 0x7100e63198: the gear the rider's AS controller is in, limited by the current gear of the
// controller (_18._b, or _18._9 when _18._b is 0).
s32 RideableBase::sub_7100E63198(s32 gear) {
    const s32 cur = _18._b == 0 ? _18._9 : _18._b;
    s32 result;
    if ((_18._9 == _18._b && _18._8 == _18._a) || !(_18._c > 0.0f)) {
        if (gear == 0) {
            result = 0;
        } else {
            const s32 g = cur < 3 && gear == 4 ? 3 : gear;
            const s32 r = cur - 1;
            result = cur <= gear ? g : r;
        }
    } else {
        result = cur;
    }
    return result;
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

// NON_MATCHING: the original computes &_a0 before the m45 call and keeps it in a callee-saved register
void RideableBase::sub_7100E62B84() {
    auto* as_list = mActor->getASList();
    auto* nav = mActor->m45();
    as_list->sub_710115EC98(1, nullptr, 0);
    _a0.sub_7100E6FAB4(this, as_list, nav);
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

// NON_MATCHING: see sub_7100E62B84
void RideableBase::sub_7100E633AC() {
    _18.sub_7100E761A4(true, true);
    auto* as_list = mActor->getASList();
    auto* nav = mActor->m45();
    as_list->sub_710115EC98(1, nullptr, 0);
    _a0.sub_7100E6FAB4(this, as_list, nav);
}

}  // namespace uking::act
