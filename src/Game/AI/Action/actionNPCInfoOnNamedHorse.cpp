#include "Game/AI/Action/actionNPCInfoOnNamedHorse.h"
#include "Game/UI/uiUtils.h"

namespace uking::action {

NPCInfoOnNamedHorse::NPCInfoOnNamedHorse(const InitArg& arg) : ksys::act::ai::Action(arg) {}

NPCInfoOnNamedHorse::~NPCInfoOnNamedHorse() = default;

bool NPCInfoOnNamedHorse::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

bool NPCInfoOnNamedHorse::oneShot_() {
    if (ui::sub_7100A98FA8())
        return false;
    ui::sub_7100A98BB0();
    return true;
}

void NPCInfoOnNamedHorse::loadParams_() {}

}  // namespace uking::action
