#include "Game/AI/Action/actionSetActorNameToGameDataString.h"
#include "KingSystem/GameData/gdtManager.h"

namespace uking::action {

SetActorNameToGameDataString::SetActorNameToGameDataString(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

SetActorNameToGameDataString::~SetActorNameToGameDataString() = default;

bool SetActorNameToGameDataString::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

// NON_MATCHING: the original computes &name (x21) before the cstr() call; scheduling only
bool SetActorNameToGameDataString::oneShot_() {
    return ksys::gdt::Manager::instance()->setStr(mActorName_d.cstr(), mGameDataStringName_d);
}

void SetActorNameToGameDataString::loadParams_() {
    getDynamicParam(&mGameDataStringName_d, "GameDataStringName");
    getDynamicParam(&mActorName_d, "ActorName");
}

}  // namespace uking::action
