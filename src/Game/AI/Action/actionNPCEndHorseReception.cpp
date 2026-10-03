#include "Game/AI/Action/actionNPCEndHorseReception.h"
#include "Game/UI/uiUtils.h"

namespace uking::action {

NPCEndHorseReception::NPCEndHorseReception(const InitArg& arg) : ksys::act::ai::Action(arg) {}

NPCEndHorseReception::~NPCEndHorseReception() = default;

bool NPCEndHorseReception::oneShot_() {
    if (!ui::sub_7100A98FA8())
        return false;
    ui::sub_7100A98EE4();
    return true;
}

}  // namespace uking::action
