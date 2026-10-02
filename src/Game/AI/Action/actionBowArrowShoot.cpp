#include "Game/AI/Action/actionBowArrowShoot.h"
#include "KingSystem/ActorSystem/Profiles/actPlayerBase.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "Game/Actor/actWeapon.h"

namespace uking::action {

BowArrowShoot::BowArrowShoot(const InitArg& arg) : BindAction(arg) {}

void BowArrowShoot::enter_(ksys::act::ai::InlineParamPack* params) {
    BindAction::enter_(params);
    mFlags.reset(Flag::Changeable);
}

void BowArrowShoot::calc_() {
    BindAction::calc_();
    if (isFinishedAS(0, 0))
        setFinished();
}

// NON_MATCHING: the original destroys the player accessor before the x_3 call (block scope)
void BowArrowShoot::m32() {
    auto* actor = mActor;
    auto* as_list = actor->getASList();
    auto* weapon = sead::DynamicCast<act::Weapon>(actor);
    if (weapon && weapon->isParentPlayer()) {
        as_list->x_2(66, 23, true, false);
        playAS("Shoot", false, 0, 0, -1.0f);
        ksys::act::acc::PlayerBase player;
        player.getPlayerFromPlayerInfo();
        const f32 rate = player.m301();
        as_list->x_3(0, 0, &ksys::as::ASList::Unk2::sub_71011631BC, rate);
    } else {
        as_list->x_2(66, 23, false, false);
        playAS("Shoot", false, 0, 0, -1.0f);
    }
}

ksys::act::Actor* BowArrowShoot::m33() {
    auto* weapon = sead::DynamicCast<act::Weapon>(mActor);
    if (!weapon)
        return nullptr;
    return weapon->getParentActor();
}

}  // namespace uking::action
