#include "Game/AI/Action/actionNPCRegisterHorse.h"
#include "Game/gameHorseMgr.h"
#include "KingSystem/GameData/gdtManager.h"

namespace uking::action {

NPCRegisterHorse::NPCRegisterHorse(const InitArg& arg) : ksys::act::ai::Action(arg) {}

NPCRegisterHorse::~NPCRegisterHorse() = default;

bool NPCRegisterHorse::oneShot_() {
    auto* link = &HorseMgr::instance()->_30;
    if (link->hasProc()) {
        if (!HorseMgr::instance()->sub_7100E85334(*link)) {
            if (auto* gdm = ksys::gdt::Manager::instance()) {
                const char* name;
                if (gdm->getParamBypassPerm().get().getStr64(&name, "Horse_NewName")) {
                    if (HorseMgr::instance()->sub_7100E8527C(link, name, false))
                        return true;
                }
            }
        }
    }
    return false;
}

}  // namespace uking::action
