#include "Game/AI/AI/aiOptionalWeaponAI.h"
#include "Game/Actor/actOptionalWeapon.h"

namespace uking::ai {

OptionalWeaponAI::OptionalWeaponAI(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

void OptionalWeaponAI::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* weapon = sead::DynamicCast<act::OptionalWeapon>(mActor);
    if (weapon && weapon->sub_7100EF1B90())
        sub_7100E1A544();
    else
        changeChild("非装備");
}

void OptionalWeaponAI::loadParams_() {}

}  // namespace uking::ai
