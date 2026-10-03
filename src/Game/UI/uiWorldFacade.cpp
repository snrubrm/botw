#include "KingSystem/World/worldManager.h"

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
