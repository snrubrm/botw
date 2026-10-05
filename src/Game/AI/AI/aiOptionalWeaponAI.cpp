#include "Game/AI/AI/aiOptionalWeaponAI.h"
#include "Game/Actor/actOptionalWeapon.h"
#include "KingSystem/Event/evtManager.h"
#include "KingSystem/GameData/gdtManager.h"

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

void OptionalWeaponAI::calc_() {
    if (isCurrentChild("非装備")) {
        if (auto* weapon = sead::DynamicCast<act::OptionalWeapon>(mActor)) {
            if (weapon->sub_7100EF1B90())
                sub_7100E1A544();
        }
        return;
    }
    if (!isCurrentChild("装備"))
        return;
    if (auto* weapon = sead::DynamicCast<act::OptionalWeapon>(mActor)) {
        if (weapon->sub_7100EF1B70()) {
            mActor->deleteLater(ksys::act::BaseProc::DeleteReason::_0);
            return;
        }
    }
    bool skip = false;
    auto* weapon = sead::DynamicCast<act::OptionalWeapon>(mActor);
    if (ksys::evt::Manager::instance()->hasActiveEvent() && weapon->sub_7100EF1308())
        ksys::gdt::Manager::instance()->getParam().get().getBool(
            &skip, "100enemy_Sheath_BindUpdateSkip");
    if (!skip)
        sub_7100E1A930();
}

}  // namespace uking::ai
