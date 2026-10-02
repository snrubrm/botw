#include "Game/AI/Action/actionBowArrowReload.h"
#include "Game/Actor/actWeapon.h"

namespace uking::action {

BowArrowReload::BowArrowReload(const InitArg& arg) : BindAction(arg) {}

void BowArrowReload::enter_(ksys::act::ai::InlineParamPack* params) {
    BindAction::enter_(params);
    mFlags.set(Flag::Changeable);
}

void BowArrowReload::calc_() {
    BindAction::calc_();
}

ksys::act::Actor* BowArrowReload::m33() {
    auto* weapon = sead::DynamicCast<act::Weapon>(mActor);
    if (!weapon)
        return nullptr;
    return weapon->getParentActor();
}

}  // namespace uking::action
