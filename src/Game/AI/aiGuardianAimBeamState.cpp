#include "Game/AI/aiGuardianAimBeamState.h"

namespace uking::ai {

GuardianAimBeamState::GuardianAimBeamState() = default;

GuardianAimBeamState::~GuardianAimBeamState() = default;

// NON_MATCHING: the original fades the two SLink handles with `Event::fade(0)`; lib/xlink2's
// HandleSLink::fade() has no frame argument (it always passes -1).
void GuardianAimBeamState::sub_71006F2D08() {
    _38.fade();
    _28.fade();
    _48.fade();
    _58.fade();
    _68.fade();
    _d8 = 0;
}

}  // namespace uking::ai
