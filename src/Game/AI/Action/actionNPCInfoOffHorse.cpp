#include "Game/AI/Action/actionNPCInfoOffHorse.h"
#include "Game/UI/uiUtils.h"

namespace uking::action {

NPCInfoOffHorse::NPCInfoOffHorse(const InitArg& arg) : ksys::act::ai::Action(arg) {}

NPCInfoOffHorse::~NPCInfoOffHorse() = default;

bool NPCInfoOffHorse::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

bool NPCInfoOffHorse::oneShot_() {
    if (!ui::sub_7100A98FA8())
        return false;
    ui::sub_7100A98EE4();
    return true;
}

void NPCInfoOffHorse::loadParams_() {}

}  // namespace uking::action
