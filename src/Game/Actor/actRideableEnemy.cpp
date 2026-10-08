#include "Game/Actor/actRideableEnemy.h"
#include "Game/Actor/actEnemy.h"
#include "Game/Actor/actHorseObject.h"

namespace uking::act {

void RideableEnemy::m24() {}

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
    auto* proc = static_cast<Enemy*>(actor)->_1148._38.getProc(nullptr, nullptr);
    proc = sead::DynamicCast<ksys::act::Actor>(proc);
    return sead::DynamicCast<HorseReins>(proc);
}

}  // namespace uking::act
