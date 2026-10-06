#include "Game/gameSaveSystem.h"
#include "KingSystem/GameData/gdtSaveMgr.h"

namespace uking {

bool SaveSystem::isFinishedSavingMaybe() const {
    auto* mgr = ksys::SaveMgr::instance();
    return mgr && mgr->get38() == 0 && _3c == 0;
}

}  // namespace uking
