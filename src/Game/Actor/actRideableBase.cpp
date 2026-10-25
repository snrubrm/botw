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

// 0x7100e6391c (placeholder name): the three steering gains of the AnimalUnit parameters: the
// Override values when `use_override` is 1 and all three are set (>= 0), the base values otherwise;
// false when there is no AnimalUnit object.
bool RideableBase::sub_7100E6391C(const f32** kp, const f32** ki, const f32** kd, u8 use_override) {
    const auto* animal = mActor->getParam()->getRes().mGParamList->getAnimalUnit();
    if (!animal)
        return false;
    if (use_override == 1) {
        *kp = &animal->mOverrideSteeringOutputKp.ref();
        *ki = &animal->mOverrideSteeringOutputKi.ref();
        *kd = &animal->mOverrideSteeringOutputKd.ref();
        if (**kp < 0.0f || **ki < 0.0f || **kd < 0.0f) {
            *kp = &animal->mSteeringOutputKp.ref();
            *ki = &animal->mSteeringOutputKi.ref();
            *kd = &animal->mSteeringOutputKd.ref();
        }
        return true;
    }
    *kp = &animal->mSteeringOutputKp.ref();
    *ki = &animal->mSteeringOutputKi.ref();
    *kd = &animal->mSteeringOutputKd.ref();
    return true;
}

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

// NON_MATCHING: the original computes all four parameter pointer pairs before the first store; ours stores
// each pair right after its two adds and materialises the masked bit earlier.
void RideableBase::m5() {
    _18.sub_7100E761A4(true, true);

    auto* const as_list = mActor->getASList();
    auto& s2 = _a0;
    auto* const nav = mActor->m45();
    as_list->sub_710115EC98(1, nullptr, 0);
    s2.sub_7100E6FAB4(this, as_list, nav);

    _8 = 0;
    _134 = 0;
    _138 = 0;
    _13c = 0;
    _140 = 0;
    _144 = 0;
    _148.set(0.0f, 0.0f, 0.0f);
    _158.set(0.0f, 0.0f, 0.0f);
    _154 = 1.0f;
    _164 = 1.0f;

    const auto* animal = mActor->getParam()->getRes().mGParamList->getAnimalUnit();
    if (animal) {
        s2._0 = &animal->mSteeringOutputKp.ref();
        s2._8 = &animal->mSteeringOutputKi.ref();
        s2._10 = &animal->mSteeringOutputKd.ref();
        s2._18 = &animal->mSteeringOutputIClamp.ref();
        s2._20 = &animal->mSteeringOutputIReduceRatio.ref();
        s2._28 = &animal->mSteeringOutputDLerpRatio.ref();
        s2._40 = &animal->mSteeringOutputAvoidanceLerpRatio.ref();
        s2._48 = &sUnk_7101EC1904;
        s2._58 = &animal->mSteeringOutputIIRLerpRatio.ref();
        _164 = animal->mBasePlayRate.ref();
        _168 = animal->mGearMaxNum.ref();
        const bool wait_as = animal->mIsSetWaitASAtGear0.ref();
        _18._52 = wait_as ? (_18._52 | 2) : (_18._52 & ~2);
    }
}

// 0x7100e63224: requests the gear pair (`type`, `gear`) with the gear clamped to the limit m11 reports for
// `type`; ignored while flag 4 of _8 is set.
void RideableBase::sub_7100E63224(S1::UnkGear type, S1::UnkGear gear) {
    if (_8 & 4)
        return;
    {
        const s32 g = int(gear);
        const S1::UnkGear limit = m11(type);
        gear = sead::Mathi::clampMax(g, limit);
    }
    _18.sub_7100E76AA4(type, gear, sUnk_7101EC1960);
}

// 0x7100e63470: a movement request (gear and the two auto-down limits) forwarded to S2 with both gear
// values clamped to the gear limit for `gear_type`; false when the actor has no navmesh character /
// character controller / AS list.
bool RideableBase::sub_7100E63470(S1::UnkGear gear_type, S1::UnkGear gear,
                                  S1::UnkGear min_gear_at_auto_down, AutoStopAndTurnMode mode) {
    auto* const nav = mActor->m45();
    auto* const cc = mActor->getCharacterController();
    auto* const as_list = mActor->getASList();
    if (!nav || !cc || !as_list)
        return false;

    const S1::UnkGear limit = m11(gear_type);
    return _a0.sub_7100E6FDD4(this, as_list, nav, cc, gear_type, sead::Mathi::clampMax(gear, limit),
                              sead::Mathi::clampMax(min_gear_at_auto_down, limit), mode);
}

// 0x7100e63560: the direction-taking movement request. The direction is normalised first (the zero vector
// when it is shorter than Mathf::epsilon()); false without a character controller or an AS list.
bool RideableBase::sub_7100E63560(S1::UnkGear gear_type, S1::UnkGear gear,
                                  S1::UnkGear min_gear_at_auto_down, const sead::Vector3f& direction,
                                  AutoStopAndTurnMode mode) {
    auto* const nav = mActor->m45();
    auto* const cc = mActor->getCharacterController();
    auto* const as_list = mActor->getASList();
    if (!cc || !as_list)
        return false;

    sead::Vector3f dir;
    const f32 len = direction.length();
    if (len > 0.0f) {
        const f32 inv_len = 1.0f / len;
        dir.x = direction.x * inv_len;
        dir.y = direction.y * inv_len;
        dir.z = direction.z * inv_len;
    }
    if (len < sead::Mathf::epsilon())
        dir.set(0.0f, 0.0f, 0.0f);

    const S1::UnkGear limit = m11(gear_type);
    return _a0.sub_7100E6FF38(this, as_list, nav, dir, dir, cc, gear_type,
                              sead::Mathi::clampMax(gear, limit),
                              sead::Mathi::clampMax(min_gear_at_auto_down, limit), mode);
}

// NON_MATCHING: the target's equal-pair test falls through into the decrement arm and each arm
// converts its own 4-byte gear temporary; this build inverts the second equality test and shares
// one decrement block.
RideableBase::S1::UnkGear RideableBase::m11(S1::UnkGear mode) {
    S1::UnkGear limit = _168;
    if (mode == S1::UnkGear::_0) {
        if (_138 > 0.0f)
            limit = sead::Mathi::min(int(limit), 1);
        else if (_13c > 0.0f)
            limit = sead::Mathi::min(int(limit), 2);
    }
    if (_18._9 != _18._b || _18._8 != _18._a) {
        const S1::UnkGear gear = _18._b == 0 ? _18._9 : _18._b;
        if (_18._c > 0.0f)
            return S1::UnkGear(sead::Mathi::max(int(limit), int(gear)));
    }
    const S1::UnkGear gear = _18._b == 0 ? _18._9 : _18._b;
    return S1::UnkGear(sead::Mathi::max(int(limit), int(gear) - 1));
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
    sead::Atomic<u32>* ids;
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

void RideableBase::sub_7100E62B84() {
    auto* as_list = mActor->getASList();
    auto& s2 = _a0;
    auto* nav = mActor->m45();
    as_list->sub_710115EC98(1, nullptr, 0);
    s2.sub_7100E6FAB4(this, as_list, nav);
}

// NON_MATCHING: the original computes the member address (`add x8, x0, #0x140`) and loads through it, with a 64-bit zero for
// the third result; we fold the offset into the load and return a 32-bit zero.
u64 RideableBase::sub_7100E63374() {
    if (_138 > 0.0f)
        return _140.load();
    if (_13c > 0.0f)
        return _144.load();
    return 0;
}

void RideableBase::sub_7100E633AC() {
    _18.sub_7100E761A4(true, true);
    auto* as_list = mActor->getASList();
    auto& s2 = _a0;
    auto* nav = mActor->m45();
    as_list->sub_710115EC98(1, nullptr, 0);
    s2.sub_7100E6FAB4(this, as_list, nav);
}

}  // namespace uking::act
