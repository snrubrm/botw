#include "Game/AI/Action/actionNPCInfoOnHorse.h"
#include "Game/UI/uiUtils.h"

namespace uking::action {

NPCInfoOnHorse::NPCInfoOnHorse(const InitArg& arg) : ksys::act::ai::Action(arg) {}

NPCInfoOnHorse::~NPCInfoOnHorse() = default;

bool NPCInfoOnHorse::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

bool NPCInfoOnHorse::oneShot_() {
    if (ui::sub_7100A98FA8())
        return false;
    ui::sub_7100A98AE4();
    return true;
}

void NPCInfoOnHorse::loadParams_() {}

}  // namespace uking::action
