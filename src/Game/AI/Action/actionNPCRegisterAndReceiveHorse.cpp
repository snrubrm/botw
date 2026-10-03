#include "Game/AI/Action/actionNPCRegisterAndReceiveHorse.h"
#include "Game/gameHorseMgr.h"
#include "KingSystem/GameData/gdtManager.h"

namespace uking::action {

NPCRegisterAndReceiveHorse::NPCRegisterAndReceiveHorse(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

NPCRegisterAndReceiveHorse::~NPCRegisterAndReceiveHorse() = default;

bool NPCRegisterAndReceiveHorse::oneShot_() {
    auto* link = &HorseMgr::instance()->_30;
    if (link->hasProc()) {
        if (!HorseMgr::instance()->sub_7100E85334(*link)) {
            if (auto* gdm = ksys::gdt::Manager::instance()) {
                const char* name;
                if (gdm->getParamBypassPerm().get().getStr64(&name, "Horse_NewName")) {
                    if (HorseMgr::instance()->sub_7100E8527C(link, name, true))
                        return true;
                }
            }
        }
    }
    return false;
}

}  // namespace uking::action
