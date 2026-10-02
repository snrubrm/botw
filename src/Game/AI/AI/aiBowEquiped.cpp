#include "Game/AI/AI/aiBowEquiped.h"
#include "Game/Actor/actWeapon.h"

namespace uking::ai {

BowEquiped::BowEquiped(const InitArg& arg) : ksys::act::ai::Ai(arg) {}


bool BowEquiped::isChangeable() const {
    return !_38.isAllocatedOrFailed();
}

void BowEquiped::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void BowEquiped::leave_() {
    ksys::act::ai::Ai::leave_();
}

bool BowEquiped::sub_710033788C() {
    auto* weapon = sead::DynamicCast<act::Weapon>(mActor);
    if (!weapon || weapon->m188())
        return false;
    if (weapon->_af8._0 == 2)
        return true;
    if (!weapon->isParentPlayer() &&
        !weapon->getActorFlags2().isOn(ksys::act::Actor::ActorFlag2::_200)) {
        return false;
    }
    return weapon->_af8._0 == 3;
}

}  // namespace uking::ai
