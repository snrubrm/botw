#include "Game/AI/Action/actionDisableAutoSavePausing.h"
#include "Game/gameSaveSystem.h"

namespace uking::action {

DisableAutoSavePausing::DisableAutoSavePausing(const InitArg& arg) : ksys::act::ai::Action(arg) {}

DisableAutoSavePausing::~DisableAutoSavePausing() = default;

bool DisableAutoSavePausing::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void DisableAutoSavePausing::loadParams_() {}

bool DisableAutoSavePausing::oneShot_() {
    SaveSystem::instance()->_1a50 &= ~4;
    return true;
}

}  // namespace uking::action
