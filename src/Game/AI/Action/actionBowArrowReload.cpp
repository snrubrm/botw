#include "Game/AI/Action/actionBowArrowReload.h"
#include "Game/Actor/actWeapon.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/Profiles/actPlayerBase.h"

namespace uking::action {

BowArrowReload::BowArrowReload(const InitArg& arg) : BindAction(arg) {}

void BowArrowReload::enter_(ksys::act::ai::InlineParamPack* params) {
    BindAction::enter_(params);
    mFlags.set(Flag::Changeable);
}

void BowArrowReload::m32() {
    playAS("Equiped", true, 0, 0, -1.0f);
    auto* weapon = sead::DynamicCast<act::Weapon>(mActor);
    if (weapon && weapon->isParentPlayer()) {
        auto* as_list = mActor->getASList();
        f32 rate;
        {
            ksys::act::acc::PlayerBase player;
            player.getPlayerFromPlayerInfo();
            rate = player.getBowSlowRateDiam();
        }
        as_list->x_3(0, 0, &ksys::as::ASList::Unk2::sub_71011631BC, rate);
    }
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
