#include "Game/Actor/actRideableHorse.h"
#include <math/seadMathCalcCommon.h>
#include "Game/Actor/actHorseBase.h"
#include "KingSystem/ActorSystem/actGlobalParameter.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectGlobal.h"
#include "Game/gameHorseMgr.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actTag.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/Resource/Actor/resResourceGParamList.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectHorse.h"
#include "KingSystem/Utils/Thread/Message.h"
#include "KingSystem/ActorSystem/Awareness/actAwarenessInstance.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"

namespace uking::act {

RideableHorse::RideableHorse() = default;

RideableHorse::~RideableHorse() {
    _280.freeBuffer();
}

RideableBase* RideableHorse::make(sead::Heap* heap) {
    return new (heap, std::nothrow) RideableHorse;
}

// NON_MATCHING: the native enum conversion uses a stack temporary; the table complement is folded.
void RideableHorse::m7() {
    Rideable::m7();
    auto* actor = RideableBase::mActor;
    if (RideableBase::_8.load() & 8)
        _294 = actor->getMtx().m[1][3];
    if (auto* awareness = actor->getAwareness()) {
        u32 mask = 0;
        switch (Unk_7100e8b2b8::_c.load()) {
        case 1:
        case 3:
            mask = 3;
            break;
        case 2:
            mask = 7;
            break;
        }
        awareness->_318 = awareness->_31c & ~mask;
    }
}

// NON_MATCHING: the first clamp uses compare/select instead of FMAX, with different load scheduling.
void RideableHorse::m8() {
    Rideable::m8();
    auto* controller = RideableBase::mActor->getCharacterController();
    if (!controller)
        return;
    if (!(RideableBase::_8.load() & 4)) {
        controller->sub_7100F605C8(sead::Vector3f::zero);
        return;
    }
    // The clamps preserve unordered values and the native signs of zero.
    const f32 rate = 1.0f - (_29c <= 0.0f ? 0.0f : _29c) / _298;
    const f32 height = RideableBase::mActor->getMtx().m[1][3] - _294;
    f32 correction;
    if (RideableBase::_8.load() & 0x10)
        correction = height + (rate - 1.0f) * _298;
    else
        correction = rate * height;
    correction = -correction;
    const sead::Vector3f velocity{0.0f, correction > 0.0f ? 0.0f : correction, 0.0f};
    controller->sub_7100F605C8(velocity);
}

void RideableHorse::procLink8() {
    Unk_7100e8b2b8::_c = 1;
    Unk_7100e8b2b8::_8 &= ~0x400u;
}

f32 RideableHorse::procLink13() {
    return m41() == nullptr ? -0.1f : 0.0f;
}

void RideableHorse::m42(s32 a) {
    s32 value;
    {
        const Unk8 state = Unk8(u8(Unk_7100e8b2b8::_8));
        value = state;
    }
    if (a == 1 && value == 0 &&
        ksys::act::hasTag(RideableBase::mActor, ksys::act::tags::ResetLastRiddenAnimalHorse)) {
        if (auto* mgr = HorseMgr::instance()) {
            if (mgr->isLinkedToActor(RideableBase::mActor))
                mgr->setRiddenHorseMaybe(nullptr);
        }
    }
}

void RideableHorse::m43() {
    if (Unk_7100e8b2b8::_c == 1) {
        if (auto* mgr = HorseMgr::instance()) {
            if (mgr->isLinkedToActor(RideableBase::mActor))
                mgr->setRiddenHorseMaybe(nullptr);
        }
    }
}

bool RideableHorse::m10(const ksys::Message& message) {
    message.getType();
    return Rideable::m10(message);
}

f32 RideableHorse::m12() {
    return RideableBase::mActor->getParam()->getRes().mGParamList->getHorse()->mRunnableFramesAtGearTop.ref();
}

void* RideableHorse::m13() {
    return &_280;
}

f32 RideableHorse::m14() {
    return static_cast<HorseBase*>(RideableBase::mActor)->sub_7100E6BE6C();
}

void RideableHorse::m15(f32 a, f32 b) {
    _298 = a;
    _29c = b;
}

f32 RideableHorse::m18() {
    return RideableBase::mActor->getParam()->getRes().mGParamList->getHorse()->mGearTopInterval.ref();
}

s32 RideableHorse::m19() {
    const s32 num = RideableBase::mActor->getParam()->getRes().mGParamList->getHorse()->mGearTopChargeNum.ref();
    return (static_cast<HorseBase*>(RideableBase::mActor)->_b70 & 0x200) ? num + 2 : num;
}

void RideableHorse::m20(s32 a) {
    _290 = a;
}

s32 RideableHorse::m21() {
    return _290;
}

// NON_MATCHING (m26 - m28, m32 - m38): the original keeps the zero result in a callee-saved register across the
// HorseBase call (frame 0x30); we materialise it after the call.
f32 RideableHorse::m26() {
    f32 value = 0.0f;
    auto* global = ksys::act::GlobalParameter::instance();
    if (global && global->getGlobalParam()) {
        const HorseBase::Nature nature =
            static_cast<HorseBase*>(RideableBase::mActor)->sub_7100E68298();
        const s32 type = nature;
        if (u32(type) <= 2)
            value = global->getGlobalParam()->mHorseAlertProbability.ref().e[type];
    }
    return value;
}

f32 RideableHorse::m27() {
    f32 value = 0.0f;
    auto* global = ksys::act::GlobalParameter::instance();
    if (global && global->getGlobalParam()) {
        const HorseBase::Nature nature =
            static_cast<HorseBase*>(RideableBase::mActor)->sub_7100E68298();
        const s32 type = nature;
        if (u32(type) <= 2)
            value = global->getGlobalParam()->mHorseAlertFramesMin.ref().e[type];
    }
    return value;
}

f32 RideableHorse::m28() {
    f32 value = 0.0f;
    auto* global = ksys::act::GlobalParameter::instance();
    if (global && global->getGlobalParam()) {
        const HorseBase::Nature nature =
            static_cast<HorseBase*>(RideableBase::mActor)->sub_7100E68298();
        const s32 type = nature;
        if (u32(type) <= 2)
            value = global->getGlobalParam()->mHorseAlertFramesMax.ref().e[type];
    }
    return value;
}

HorseReins* RideableHorse::m39() {
    return static_cast<HorseBase*>(RideableBase::mActor)->getReinsB();
}

HorseReins* RideableHorse::m40() {
    return static_cast<HorseBase*>(RideableBase::mActor)->getReinsA();
}

HorseReins* RideableHorse::m41() {
    return static_cast<HorseBase*>(RideableBase::mActor)->getReinsC();
}

void RideableHorse::m29(f32 a) {
    _2a0 = a;
}

f32 RideableHorse::m30(f32 delta) {
    if (_2a0 >= 1.0f)
        return 1.0f;
    _2a0 = sead::Mathf::clamp(_2a0 + delta, 0.0f, 1.0f);
    return _2a0;
}

f32 RideableHorse::m31() {
    return _2a0;
}

f32 RideableHorse::m32() {
    f32 value = 0.0f;
    auto* global = ksys::act::GlobalParameter::instance();
    if (global && global->getGlobalParam()) {
        const HorseBase::Nature nature =
            static_cast<HorseBase*>(RideableBase::mActor)->sub_7100E68298();
        const s32 type = nature;
        if (u32(type) <= 2)
            value = global->getGlobalParam()->mHorseFamiliarityIncreasePerFrame.ref().e[type];
    }
    return value;
}

f32 RideableHorse::m33() {
    f32 value = 0.0f;
    auto* global = ksys::act::GlobalParameter::instance();
    if (global && global->getGlobalParam()) {
        const HorseBase::Nature nature =
            static_cast<HorseBase*>(RideableBase::mActor)->sub_7100E68298();
        const s32 type = nature;
        if (u32(type) <= 2)
            value = global->getGlobalParam()->mHorseFamiliarityIncreaseSootheAtFirstRun.ref().e[type];
    }
    return value;
}

f32 RideableHorse::m34() {
    f32 value = 0.0f;
    auto* global = ksys::act::GlobalParameter::instance();
    if (global && global->getGlobalParam()) {
        const HorseBase::Nature nature =
            static_cast<HorseBase*>(RideableBase::mActor)->sub_7100E68298();
        const s32 type = nature;
        if (u32(type) <= 2)
            value = global->getGlobalParam()->mHorseFamiliarityIncreaseSootheAfterRun.ref().e[type];
    }
    return value;
}

f32 RideableHorse::m35() {
    f32 value = 0.0f;
    auto* global = ksys::act::GlobalParameter::instance();
    if (global && global->getGlobalParam()) {
        const HorseBase::Nature nature =
            static_cast<HorseBase*>(RideableBase::mActor)->sub_7100E68298();
        const s32 type = nature;
        if (u32(type) <= 2)
            value = global->getGlobalParam()->mHorseFamiliarityIncreaseSootheAfterGearTop.ref().e[type];
    }
    return value;
}

f32 RideableHorse::m36() {
    f32 value = 0.0f;
    auto* global = ksys::act::GlobalParameter::instance();
    if (global && global->getGlobalParam()) {
        const HorseBase::Nature nature =
            static_cast<HorseBase*>(RideableBase::mActor)->sub_7100E68298();
        const s32 type = nature;
        if (u32(type) <= 2)
            value = global->getGlobalParam()->mHorseFamiliarityIncreaseSootheAfterJump.ref().e[type];
    }
    return value;
}

f32 RideableHorse::m37() {
    f32 value = 0.0f;
    auto* global = ksys::act::GlobalParameter::instance();
    if (global && global->getGlobalParam()) {
        const HorseBase::Nature nature =
            static_cast<HorseBase*>(RideableBase::mActor)->sub_7100E68298();
        const s32 type = nature;
        if (u32(type) <= 2)
            value = global->getGlobalParam()->mHorseFamiliarityIncreaseSootheWhileResisting.ref().e[type];
    }
    return value;
}

f32 RideableHorse::m38() {
    f32 value = 0.0f;
    auto* global = ksys::act::GlobalParameter::instance();
    if (global && global->getGlobalParam()) {
        const HorseBase::Nature nature =
            static_cast<HorseBase*>(RideableBase::mActor)->sub_7100E68298();
        const s32 type = nature;
        if (u32(type) <= 2)
            value = global->getGlobalParam()->mHorseFamiliarityIncreaseEat.ref().e[type];
    }
    return value;
}

}  // namespace uking::act
