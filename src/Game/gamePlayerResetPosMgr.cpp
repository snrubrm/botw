#include "Game/gamePlayerResetPosMgr.h"
#include <prim/seadScopedLock.h>
#include "KingSystem/GameData/gdtManager.h"

void PlayerResetPosMgr::resetSmallKeyFlags() {
    auto* manager = ksys::gdt::Manager::instance();
    if (!manager)
        return;

    s32 size = 0;
    manager->getParam().get1().getS32ArraySize(&size, "SmallKey");
    for (s32 i = 0; i < size; ++i)
        manager->resetS32("SmallKey", i);
    manager->resetS32("RemainsWater_SmallKeyNum");
    manager->resetS32("RemainsFire_SmallKeyNum");
    manager->resetS32("RemainsWind_SmallKeyNum");
    manager->resetS32("RemainsElectric_SmallKeyNum");
}

void PlayerResetPosMgr::clearResetPos() {
    {
        sead::ScopedLock<sead::SpinLock> lock(&mLock);
        if (!_428)
            _430 = false;
    }
    _20 = 0;
}
