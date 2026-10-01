#include "Game/AI/Action/actionEventSetGameDataFloatAction.h"
#include "KingSystem/GameData/gdtManager.h"

namespace uking::action {

EventSetGameDataFloatAction::EventSetGameDataFloatAction(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

EventSetGameDataFloatAction::~EventSetGameDataFloatAction() = default;

bool EventSetGameDataFloatAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

bool EventSetGameDataFloatAction::oneShot_() {
    auto* gdm = ksys::gdt::Manager::instance();
    if (gdm == nullptr)
        return false;
    return gdm->setF32NoCheck(*mValue_d, mGameDataFloatName_d);
}

void EventSetGameDataFloatAction::loadParams_() {
    getDynamicParam(&mValue_d, "Value");
    getDynamicParam(&mGameDataFloatName_d, "GameDataFloatName");
}

}  // namespace uking::action
