#include "Game/AI/Action/actionEventIncreaseGameDataIntAction.h"
#include "KingSystem/GameData/gdtManager.h"

namespace uking::action {

EventIncreaseGameDataIntAction::EventIncreaseGameDataIntAction(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

EventIncreaseGameDataIntAction::~EventIncreaseGameDataIntAction() = default;

bool EventIncreaseGameDataIntAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

bool EventIncreaseGameDataIntAction::oneShot_() {
    ksys::gdt::Manager::instance()->incrementS32NoCheck(*mValue_d, mGameDataIntName_d);
    return true;
}

void EventIncreaseGameDataIntAction::loadParams_() {
    getDynamicParam(&mValue_d, "Value");
    getDynamicParam(&mGameDataIntName_d, "GameDataIntName");
}

}  // namespace uking::action
