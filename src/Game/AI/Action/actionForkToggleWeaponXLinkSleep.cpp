#include "Game/AI/Action/actionForkToggleWeaponXLinkSleep.h"
#include "Game/Actor/actEnemy.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/Profiles/actWeaponBase.h"
#include "KingSystem/ActorSystem/actActorWeapons.h"
#include "KingSystem/XLink/xlinkXLink.h"

namespace uking::action {

ForkToggleWeaponXLinkSleep::ForkToggleWeaponXLinkSleep(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

ForkToggleWeaponXLinkSleep::~ForkToggleWeaponXLinkSleep() = default;

void ForkToggleWeaponXLinkSleep::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* enemy = sead::DynamicCast<act::Enemy>(mActor);
    if (enemy && enemy->getWeapons() && enemy->getWeapons()->getEquippedWeapon(0) &&
        enemy->getWeapons()->getEquippedWeapon(0)->getXLink()) {
        switch (*mToggle_s) {
        case 0:
            enemy->getWeapons()->getEquippedWeapon(0)->getXLink()->setMask(1);
            break;
        case 1:
            enemy->getWeapons()->getEquippedWeapon(0)->getXLink()->toggle(true);
            break;
        case 2:
            enemy->getWeapons()->getEquippedWeapon(0)->getXLink()->sleep(1);
            break;
        }
    }
    mFlags.set(Flag::Changeable);
    setFinished();
}

void ForkToggleWeaponXLinkSleep::loadParams_() {
    getStaticParam(&mToggle_s, "Toggle");
}

}  // namespace uking::action
