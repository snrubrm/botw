#include "Game/AI/Behavior/behaviorCharacterControllerFormChange.h"

namespace uking::behavior {

CharacterControllerFormChange::CharacterControllerFormChange(const InitArg& arg)
    : ksys::act::ai::Behavior(arg) {}

CharacterControllerFormChange::~CharacterControllerFormChange() = default;

void CharacterControllerFormChange::m7() {}

void CharacterControllerFormChange::loadParams() {
    getStaticParam(&mEnterState_s, "EnterState");
    getStaticParam(&mIsRestoreWhenLeave_s, "IsRestoreWhenLeave");
}

}  // namespace uking::behavior
