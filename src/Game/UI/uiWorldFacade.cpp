#include "Game/UI/uiUtils.h"
#include "Game/Actor/Player/actPlayerInfo.h"
#include "KingSystem/World/worldManager.h"
#include <devenv/seadEnvUtil.h>

// World manager wrappers of the 0x7100a94000 UI wrapper TU (CSV names wm::*, not namespaced further).
namespace wm {

// 0x7100a9d854
int getHour() {
    if (auto* manager = ksys::world::Manager::instance()) {
        if (auto* time_mgr = manager->getTimeMgr())
            return time_mgr->getHour();
    }
    return 0;
}

// 0x7100a9d760
f32 getWorldTemperatureForUI() {
    f32 temperature = 0.0f;
    if (auto* manager = ksys::world::Manager::instance()) {
        if (auto* temp_mgr = static_cast<ksys::world::TempMgr*>(manager->getMgrMaybe(4)))
            temperature = temp_mgr->get_3c();
    }
    const sead::RegionLanguageID language = sead::EnvUtil::getRegionLanguage();
    const f32 fahrenheit = temperature * 1.8f + 32.0f;
    return language == sead::RegionLanguageID::USen ? fahrenheit : temperature;
}

// 0x7100a9d7cc: the second temperature (`TempMgr::_40`), without the region conversion
f32 sub_7100A9D7CC() {
    if (auto* manager = ksys::world::Manager::instance()) {
        if (auto* temp_mgr = static_cast<ksys::world::TempMgr*>(manager->getMgrMaybe(4)))
            return temp_mgr->get_40();
    }
    return 0.0f;
}

// 0x7100a9d800
s32 sub_7100A9D800() {
    if (auto* manager = ksys::world::Manager::instance()) {
        if (auto* info = uking::act::PlayerInfo::instance())
            return manager->getIgnitedLevel(info->getPlayerPos());
    }
    return 0;
}

// 0x7100a9d884
int getMinute() {
    if (auto* manager = ksys::world::Manager::instance()) {
        if (auto* time_mgr = manager->getTimeMgr())
            return time_mgr->getMinute();
    }
    return 0;
}

// 0x7100a9d918
bool isFindDungeonActivated() {
    auto* manager = ksys::world::Manager::instance();
    if (!manager)
        return false;
    auto* time_mgr = manager->getTimeMgr();
    if (!time_mgr)
        return false;
    return time_mgr->isFindDungeonActivated();
}

}  // namespace wm
