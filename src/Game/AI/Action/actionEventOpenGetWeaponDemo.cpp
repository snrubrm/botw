#include "Game/AI/Action/actionEventOpenGetWeaponDemo.h"
#include "Game/Actor/actWeapon.h"

namespace uking::action {

EventOpenGetWeaponDemo::EventOpenGetWeaponDemo(const InitArg& arg) : EventOpenGetDemo(arg) {}

EventOpenGetWeaponDemo::~EventOpenGetWeaponDemo() = default;

void EventOpenGetWeaponDemo::calc_() {
    EventOpenGetDemo::calc_();
    auto* weapon = sead::DynamicCast<uking::act::Weapon>(mActor);
    if (weapon && weapon->m188())
        weapon->deleteLater(ksys::act::BaseProc::DeleteReason::_0);
}

}  // namespace uking::action
