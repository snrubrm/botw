#include "Game/AI/Action/actionEventSetGameDataIntAction.h"
#include "KingSystem/GameData/gdtManager.h"

namespace uking::action {

EventSetGameDataIntAction::EventSetGameDataIntAction(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

EventSetGameDataIntAction::~EventSetGameDataIntAction() = default;

bool EventSetGameDataIntAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

bool EventSetGameDataIntAction::oneShot_() {
    auto* gdm = ksys::gdt::Manager::instance();
    if (gdm == nullptr)
        return false;
    return gdm->setS32NoCheck(*mValue_d, mGameDataIntName_d);
}

void EventSetGameDataIntAction::loadParams_() {
    getDynamicParam(&mValue_d, "Value");
    getDynamicParam(&mGameDataIntName_d, "GameDataIntName");
}

}  // namespace uking::action
