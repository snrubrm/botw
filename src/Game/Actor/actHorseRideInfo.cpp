#include "KingSystem/ActorSystem/AS/ASList.h"
#include "Game/Actor/actHorseRideInfo.h"
#include <cmath>
#include <math/seadMathCalcCommon.h>
#include "Game/Actor/actRideable.h"
#include "Game/Actor/actHorseBase.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/Resource/Actor/resResourceGParamList.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectHorse.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectHorseUnit.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/Awareness/actAwarenessInstance.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "KingSystem/ActorSystem/actCCAccessor.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/Physics/System/physHavokAI.h"
#include "KingSystem/Physics/System/physInstanceSet.h"
#include "KingSystem/Physics/System/physNavMeshCharacter.h"

namespace uking::act {

HorseRideInfo::~HorseRideInfo() = default;

ksys::act::Actor* getRideActor(ksys::act::Actor* actor) {
    auto* info = actor->getPlayerRideInfo();
    if (!info)
        return nullptr;
    return sead::DynamicCast<ksys::act::Actor>(info->_18.getProc(nullptr, info->mActor));
}

ksys::act::BaseProcLink* sub_7100E811F0(ksys::act::Actor* actor) {
    auto* info = actor->getPlayerRideInfo();
    if (!info)
        return &ksys::act::sUnk_71026505e0;
    return &info->_18;
}

// 0x7100e81260: the ride animation name for `actor` riding `ride_actor`: "RideonRunHorse" while
// the horse is flagged as running, "RideonAboveHorse" when it is above and inside the configured
// height / radius, "RideonWaitHorse" otherwise.
// NON_MATCHING: the two parameter pointers are kept in the opposite callee-saved registers (x20 /
// x21); every other instruction is identical.
sead::SafeString sub_7100E81260(ksys::act::Actor* actor, ksys::act::Actor* ride_actor) {
    if (ride_actor) {
        if (auto* options = ride_actor->getHorseOptionsMaybe()) {
            if (options->RideableBase::_8 & 0x200)
                return "RideonRunHorse";
        }

        const auto* unit = ride_actor->getParam()->getRes().mGParamList->getHorseUnit();
        if (unit) {
            const auto& mtx = actor->getMtx();
            const auto& ride_mtx = ride_actor->getMtx();
            if (mtx(1, 3) - ride_mtx(1, 3) > unit->mRideonAboveASHeight.ref()) {
                const f32 dz = mtx(2, 3) - ride_mtx(2, 3);
                const f32 dx = mtx(0, 3) - ride_mtx(0, 3);
                const f32 radius = unit->mRideonAboveASRadius.ref();
                if (dx * dx + dz * dz < radius * radius)
                    return "RideonAboveHorse";
            }
        }
    }
    return "RideonWaitHorse";
}

// NON_MATCHING: the original loads the ridden actor's x / z before the actor's own
f32 sub_7100E8134C(ksys::act::Actor* actor, ksys::act::Actor* ride_actor) {
    const auto& ride_mtx = ride_actor->getMtx();
    const auto& mtx = actor->getMtx();
    const f32 ride_angle = sead::Mathf::rad2deg(std::atan2(ride_mtx(0, 2), ride_mtx(2, 2)));
    const f32 angle = sead::Mathf::rad2deg(std::atan2(mtx(0, 3) - ride_mtx(0, 3), mtx(2, 3) - ride_mtx(2, 3)));
    return angle - ride_angle;
}

bool HorseRideInfo::sub_7100E7BEC0(ksys::act::BaseProc* proc) {
    if (!proc)
        return false;

    ksys::act::ActorLinkConstDataAccess accessor(proc);
    if (!sub_7100E7BF5C(accessor, _18.hasProcById(proc)))
        return false;
    _18.acquire(proc, false);
    return true;
}

// The original calls isStateCalc() and discards the result (debug code stripped from the release build).
bool HorseRideInfo::sub_7100E7BF5C(ksys::act::ActorLinkConstDataAccess& accessor, bool a2) {
    accessor.isStateCalc();
    if (!accessor.hasProc() || !m5(accessor))
        return false;
    _30 = (_30 & ~0x33) | 1;
    if (a2)
        return true;

    accessor.setThisActorAsParent(mActor, false);
    if (auto* controller = mActor->getCharacterController())
        controller->sub_7100F5F458(ksys::act::MotionType::Hover);
    if (auto* physics = mActor->getPhysics())
        physics->sub_7100FBDFA4(accessor.x(0));
    if (auto* nav = mActor->m45()) {
        _10 = nav->_18;
        if (_10)
            _10->sub_7100F82C88(nav);
    }
    _28 = accessor.sub_7100D0F57C();
    return true;
}

// NON_MATCHING: one load width (the original reads _30 with ldrh for the bit 4 test; ours ldrb)
void HorseRideInfo::sub_7100E7C0EC() {
    m6();
    if (auto* actor = sead::DynamicCast<ksys::act::Actor>(_18.getProc(nullptr, mActor))) {
        if (auto* stuff = actor->getMotorcyclePriorityStuffMaybe()) {
            stuff->m22(Unk_7100e8b2b8::Unk8::_0);
            stuff->sub_7100E8BD6C(nullptr);
        }
    }
    auto* parent = mActor->getConnectedCalcParent();
    if (parent == sead::DynamicCast<ksys::act::Actor>(_18.getProc(nullptr, mActor)))
        mActor->resetConnectedCalcParent(false);
    _18.reset();
    _30 &= ~1;
    if (auto* controller = mActor->getCharacterController()) {
        controller->sub_7100F5F458(ksys::act::MotionType::_1);
        controller->sub_7100F5F6FC(sead::Vector3f::zero);
        controller->sub_7100F5FB24(sead::Vector3f::zero);
    }
    if (auto* physics = mActor->getPhysics()) {
        if (!(_30 & 0x10))
            physics->sub_7100FBDFA4(physics->get178(0));
    }
    if (_10) {
        if (auto* nav = mActor->m45())
            _10->sub_7100F82BCC(nav);
    }
    _28 = nullptr;
}

void HorseRideInfo::sub_7100E7C380() {
    if (_18.hasProc()) {
        if (!(_30 & 2) && !_18.isAccessingSpecifiedProcUnsafe(mActor)) {
            if (auto* actor = sead::DynamicCast<ksys::act::Actor>(_18.getProc(nullptr, mActor))) {
                if (auto* stuff = actor->getMotorcyclePriorityStuffMaybe()) {
                    stuff->sub_7100E8BD6C(mActor);
                    _30 |= 2;
                }
            }
        }
        if (auto* nav = mActor->m45()) {
            if (auto* ai = nav->_18) {
                _10 = ai;
                ai->sub_7100F82C88(nav);
            }
        }
    } else {
        if (_30 & 1) {
            _30 &= ~0x30;
            sub_7100E7C0EC();
        }
        if (_30 & 0x20) {
            if (auto* physics = mActor->getPhysics())
                physics->sub_7100FBDFA4(physics->get178(0));
            _30 &= ~0x30;
        } else if (_30 & 0x10) {
            _30 = (_30 & ~0x30) | 0x20;
        }
    }
    m9();
}

bool HorseRideInfo::sub_7100E7C054(ksys::act::BaseProcLink* link) {
    ksys::act::ActorLinkConstDataAccess accessor;
    if (!ksys::act::acquireActor(link, &accessor))
        return false;
    if (!sub_7100E7BF5C(accessor, _18 == *link))
        return false;
    _18 = *link;
    return true;
}

bool HorseRideInfo::init() {
    m7();
    _30 = 0;
    _18.reset();
    return true;
}

void HorseRideInfo::sub_7100E7C350() {
    m8();
    _30 = 0;
    _18.reset();
}

void HorseRideInfo::sub_7100E7C4F8(ksys::act::Unk117* arg) {
    if (auto* actor = sead::DynamicCast<ksys::act::Actor>(_18.getProc(nullptr, nullptr)))
        actor->x_17(arg);
}

// 0x7100e806a4: whether the horse may eat the actor linked by `link`: the horse's eat rate plus its
// satiation must not exceed 1, and the linked actor must pass its EatActorNames group test.
bool sub_7100E806A4(HorseBase* horse, const ksys::act::BaseProcLink& link) {
    if (!horse)
        return false;
    if (sUnk_7101EC1900 + horse->_b84 <= 1.0f) {
        const auto* param = horse->getParam()->getRes().mGParamList->getHorse();
        if (param)
            return sub_7100E8072C(horse->m45(), param->mEatActorNames.ref(), link);
    }
    return false;
}

// Separate TU from Rideable::sub_7100E7EF1C, which this tail-calls: the original keeps it out of line.
void sub_7100E80D18(ksys::act::Actor* actor) {
    if (!actor)
        return;
    auto* rideable = actor->getHorseOptionsMaybe();
    if (rideable && rideable->_c == 1)
        rideable->sub_7100E7EF1C();
}

bool sub_7100E81568(ksys::as::ASList* list) {
    if (list->x_4(0, 0))
        return false;
    return list->x(22, nullptr, 0, 0, &ksys::as::ASList::Unk2::sub_71011638DC, true);
}

bool sub_7100E813B0(ksys::as::ASList* list) {
    if (list->x_4(1, 0))
        return false;
    const sead::SafeString name = list->x_1(1, 0);
    return name == "RideonHorse" || name == "RideonRunHorse" || name == "RideonAboveHorse" ||
           name == "RideonWaitHorse";
}

bool sub_7100E8160C(ksys::phys::CharacterController* controller, f32* a, f32* b,
                    sead::Vector3f* position) {
    if (controller->sub_7100F63024(a, b, nullptr, nullptr, position, 0))
        return true;

    f32 radius;
    sead::Vector3f vertex_a;
    sead::Vector3f vertex_b;
    if (!controller->sub_7100F62FC0(&radius, &vertex_a, &vertex_b, 0))
        return false;

    if (a)
        *a = radius;
    if (b)
        *b = sead::Mathf::max(vertex_a.y, vertex_b.y) + radius;
    if (position) {
        position->set((vertex_a.x + vertex_b.x) * 0.5f, 0.0f, (vertex_a.z + vertex_b.z) * 0.5f);
    }
    return true;
}

bool sub_7100E815C8(ksys::act::AwarenessInstance* awareness) {
    if (awareness && !awareness->sub_7100D7E964() && awareness->enable())
        return true;
    return false;
}

}  // namespace uking::act
