#include "Game/AI/AI/aiBowEquiped.h"
#include "Game/Actor/actWeapon.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

BowEquiped::BowEquiped(const InitArg& arg) : ksys::act::ai::Ai(arg) {}


bool BowEquiped::isChangeable() const {
    return !_38.isAllocatedOrFailed();
}

void BowEquiped::enter_(ksys::act::ai::InlineParamPack* params) {
    if (mActor->getConnectedCalcChild()) {
        sub_7100337E2C(ksys::phys::ContactLayer::EntityHitOnlyWater,
                       ksys::phys::ContactLayer::SensorChemical);
        _48 = false;
        changeChild("射撃");
    } else {
        _48 = false;
        changeChild("装備");
    }
    auto* weapon = sead::DynamicCast<act::Weapon>(mActor);
    _49 = weapon && weapon->m153();
}

void BowEquiped::leave_() {
    if (_38.isAllocatedOrFailed())
        _38.deleteProc();
    if (auto* child = mActor->getConnectedCalcChild())
        child->deleteLater(ksys::act::BaseProc::DeleteReason::_0);
    if (auto* weapon = sead::DynamicCast<act::Weapon>(mActor))
        weapon->_e50 &= ~0xc0;
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
