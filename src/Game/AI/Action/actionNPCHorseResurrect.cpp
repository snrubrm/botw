#include "Game/AI/Action/actionNPCHorseResurrect.h"
#include "Game/gameHorseMgr.h"
#include "KingSystem/GameData/gdtManager.h"

namespace uking::action {

NPCHorseResurrect::NPCHorseResurrect(const InitArg& arg) : ksys::act::ai::Action(arg) {}

NPCHorseResurrect::~NPCHorseResurrect() = default;

bool NPCHorseResurrect::oneShot_() {
    auto* horse_mgr = HorseMgr::instance();
    auto* gdm = ksys::gdt::Manager::instance();
    if (horse_mgr && gdm) {
        s32 index = -1;
        if (gdm->getParam().get().getS32(&index, "Horse_SelectedIndex") && index >= 0) {
            const s32 new_index = resurrectHorseStuff(horse_mgr, index);
            if (new_index >= 0) {
                if (horse_mgr->_b0.isRegistered())
                    sendMessage(horse_mgr->_b0, ksys::MessageType(0x380001c), nullptr);
                gdm->setS32(new_index, "Horse_SelectedIndex");
            } else {
                gdm->setS32(-1, "Horse_SelectedIndex");
            }
        }
    }
    return true;
}

}  // namespace uking::action
