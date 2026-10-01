#include "Game/AI/Action/actionEventSetGameDataStringAction.h"
#include "KingSystem/GameData/gdtManager.h"

namespace uking::action {

EventSetGameDataStringAction::EventSetGameDataStringAction(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

EventSetGameDataStringAction::~EventSetGameDataStringAction() = default;

bool EventSetGameDataStringAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

// NON_MATCHING: the original computes &name (x21) before the cstr() call; scheduling only
bool EventSetGameDataStringAction::oneShot_() {
    return ksys::gdt::Manager::instance()->setStrNoCheck(mValue_d.cstr(), mGameDataStringName_d);
}

void EventSetGameDataStringAction::loadParams_() {
    getDynamicParam(&mGameDataStringName_d, "GameDataStringName");
    getDynamicParam(&mValue_d, "Value");
}

}  // namespace uking::action
