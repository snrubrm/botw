#include "Game/Actor/actRideableEnemy.h"
#include "Game/Actor/actEnemy.h"
#include "Game/Actor/actHorseObject.h"
#include "Game/gameHorseMgr.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actTag.h"

namespace uking::act {

RideableEnemy* RideableEnemy::make(sead::Heap* heap) {
    return new (heap, std::nothrow) RideableEnemy;
}

// 0x71002cb350 (placeholder name in the CSV): the enemy's gear: 3 for a prey / swarm with gear >= 2, the
// types 4 / 5, or a /prey/swarm that is not a wolf or bear; else Rideable::m23.
// NON_MATCHING: ours folds the type 4 / 5 test into a mask and reloads mActor from `this` instead of keeping
// its address in a callee-saved register.
Rideable::Gear RideableEnemy::m23() {
    const Gear gear(_18._b == 0 ? _18._9 : _18._b);
    const s32 type = _18._a;
    if (int(gear) >= 2 && ksys::act::isPreyOrSwarm(RideableBase::mActor))
        return Gear::_3;
    switch (type) {
    case 4:
    case 5:
        return Gear::_3;
    }
    if (type == 3 && ksys::act::isPreyOrSwarm(RideableBase::mActor) &&
        !ksys::act::isWolfOrBear(RideableBase::mActor))
        return Gear::_3;
    return Rideable::m23();
}

void RideableEnemy::m24() {}

// 0x71002cb428: clears the ridden horse when the actor stops being ridden and marks it as a
// non-vehicle (bit 0x400 of the rideable flags) unless it carries the IsVehicle tag.
// NON_MATCHING: the second-base thunk (0x71002cb4bc) inlines this body with a different callee-saved
// register (it keeps the subobject pointer and re-derives mActor); the override itself matches.
void RideableEnemy::m42(int a1) {
    s32 value;
    {
        const Unk8 state = Unk8(u8(Unk_7100e8b2b8::_8));
        value = state;
    }
    if (a1 == 1 && value == 0) {
        if (auto* mgr = HorseMgr::instance()) {
            if (mgr->isLinkedToActor(RideableBase::mActor))
                mgr->setRiddenHorseMaybe(nullptr);
        }
        if (!ksys::act::hasTag(RideableBase::mActor, ksys::act::tags::IsVehicle))
            RideableBase::_8 |= 0x400;
    }
}

bool RideableEnemy::m44() {
    return m23() > Gear::_1;
}

f32 RideableEnemy::procLink13() {
    if (sub_7100E8C03C() == ksys::act::Unk_7100d14598::_8)
        return -0.2f;
    return Unk_7100e8b2b8::procLink13();
}

HorseReins* RideableEnemy::m40() {
    auto* actor = RideableBase::mActor;
    if (!sead::IsDerivedFrom<Enemy>(actor))
        return nullptr;
    auto* proc = static_cast<Enemy*>(actor)->_1180.getProc(nullptr, nullptr);
    proc = sead::DynamicCast<ksys::act::Actor>(proc);
    return sead::DynamicCast<HorseReins>(proc);
}

}  // namespace uking::act
