#include "Game/AI/AI/aiOptionalWeaponAI.h"
#include "Game/Actor/actOptionalWeapon.h"
#include "KingSystem/Event/evtManager.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
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

void OptionalWeaponAI::sub_7100E1A544() {
    if (auto* weapon = sead::DynamicCast<act::OptionalWeapon>(mActor)) {
        weapon->sub_7100EF1BF4();
        ksys::act::ai::InlineParamPack params;
        params.addString(weapon->sub_7100EF13A4().getStringTop(), "NodeName", -1);
        sead::Vector3f rotation;
        weapon->sub_7100EF13AC(&rotation);
        params.addVec3(rotation, "RotOffset", -1);
        sead::Vector3f translation;
        weapon->sub_7100EF1680(&translation);
        params.addVec3(translation, "TransOffset", -1);
        changeChild("装備", &params);
    }
}

void OptionalWeaponAI::sub_7100E1A930() {
    if (auto* weapon = sead::DynamicCast<act::OptionalWeapon>(mActor)) {
        if (weapon->_83c & 1) {
            sead::Vector3f rotation;
            weapon->sub_7100EF13AC(&rotation);
            getCurrentChild()->setDynamicParam(rotation, "RotOffset");
            sead::Vector3f translation;
            weapon->sub_7100EF1680(&translation);
            getCurrentChild()->setDynamicParam(translation, "TransOffset");
        }
    }
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
