#include "Game/AI/Action/actionNPCReceiveHorse.h"
#include "Game/gameHorseMgr.h"

namespace uking::action {

NPCReceiveHorse::NPCReceiveHorse(const InitArg& arg) : ksys::act::ai::Action(arg) {}

NPCReceiveHorse::~NPCReceiveHorse() = default;

bool NPCReceiveHorse::oneShot_() {
    HorseMgr::instance()->sub_7100E85BC0();
    return true;
}

}  // namespace uking::action
