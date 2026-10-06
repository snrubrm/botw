#include "Game/AI/aiUnk_710073BB28.h"
#include "Game/UI/uiPauseMenuDataMgr.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "Game/UI/uiUtils.h"

bool sub_710073BB54() {
    if (uking::ui::sub_7100A94AC8())
        return true;
    return !uking::ui::sub_7100A94E08();
}

void sub_710073BADC() {
    uking::ui::playSound("mc_DoUnable", nullptr);
}

void weaponBroken(ksys::act::Actor* actor) {
    uking::ui::PauseMenuDataMgr::instance()->removeWeaponIfEquipped(actor->getName());
    uking::ui::mainScreen3DStuff();
}

void uking::removeFromInventory(const sead::SafeString& name) {
    uking::ui::PauseMenuDataMgr::instance()->removeWeaponIfEquipped(name);
    uking::ui::mainScreen3DStuff();
}

void masterSwordBroken() {
    uking::ui::PauseMenuDataMgr::instance()->breakMasterSword();
    uking::ui::mainScreen3DStuff();
}
