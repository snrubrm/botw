#include "Game/AI/Action/actionBowArrowHold.h"
#include "KingSystem/ActorSystem/Profiles/actPlayerBase.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "Game/Actor/actWeapon.h"

namespace uking::action {

BowArrowHold::BowArrowHold(const InitArg& arg) : BindAction(arg) {}

// NON_MATCHING: the original destroys the player accessor before the x_3 call (block scope)
void BowArrowHold::m32() {
    auto* actor = mActor;
    auto* as_list = actor->getASList();
    auto* weapon = sead::DynamicCast<act::Weapon>(actor);
    if (weapon && weapon->isParentPlayer()) {
        as_list->x_2(66, 23, true, false);
        playAS("Draw", false, 0, 0, -1.0f);
        ksys::act::acc::PlayerBase player;
        player.getPlayerFromPlayerInfo();
        const f32 rate = player.m301();
        as_list->x_3(0, 0, &ksys::as::ASList::Unk2::sub_71011631BC, rate);
    } else {
        as_list->x_2(66, 23, false, false);
        playAS("Draw", false, 0, 0, -1.0f);
    }
}

ksys::act::Actor* BowArrowHold::m33() {
    auto* weapon = sead::DynamicCast<act::Weapon>(mActor);
    if (!weapon)
        return nullptr;
    return weapon->getParentActor();
}

}  // namespace uking::action
