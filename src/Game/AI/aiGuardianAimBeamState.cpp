#include "Game/AI/aiGuardianAimBeamState.h"

namespace uking::ai {

GuardianAimBeamState::GuardianAimBeamState() = default;

GuardianAimBeamState::~GuardianAimBeamState() = default;

void GuardianAimBeamState::sub_71006F2D08() {
    _38.fade();
    _28.fade();
    _48.fade();
    _58.fade(0);
    _68.fade(0);
    _d8 = 0;
}

}  // namespace uking::ai
