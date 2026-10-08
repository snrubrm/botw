#include "Game/Actor/actRideableEnemy.h"
#include "Game/Actor/actEnemy.h"
#include "Game/Actor/actHorseObject.h"

namespace uking::act {

void RideableEnemy::m24() {}

bool RideableEnemy::m44() {
    return m23() > Gear::_1;
}

float RideableEnemy::m45() {
    auto* unk = static_cast<Unk_7100e8b2b8*>(this);
    if (unk->sub_7100E8C03C() == ksys::act::Unk_7100d14598::_8)
        return -0.2f;
    // Qualified in the original (direct branch, not a vtable call).
    return unk->Unk_7100e8b2b8::procLink13();
}

HorseReins* RideableEnemy::m40() {
    auto* actor = RideableBase::mActor;
    if (!sead::IsDerivedFrom<Enemy>(actor))
        return nullptr;
    auto* proc = static_cast<Enemy*>(actor)->_1148._38.getProc(nullptr, nullptr);
    proc = sead::DynamicCast<ksys::act::Actor>(proc);
    return sead::DynamicCast<HorseReins>(proc);
}

}  // namespace uking::act
