#include "Game/AI/Action/actionNPCReleaseHorse.h"
#include "Game/gameHorseMgr.h"
#include "KingSystem/GameData/gdtManager.h"

namespace uking::action {

NPCReleaseHorse::NPCReleaseHorse(const InitArg& arg) : ksys::act::ai::Action(arg) {}

NPCReleaseHorse::~NPCReleaseHorse() = default;

bool NPCReleaseHorse::oneShot_() {
    s32 index;
    if (!ksys::gdt::Manager::instance()->getParamBypassPerm().get().getS32(&index, "Horse_SelectedIndex"))
        return false;
    HorseMgr::instance()->sub_7100E857CC(index, true, false, -1);
    return true;
}

}  // namespace uking::action
