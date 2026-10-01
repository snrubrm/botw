#include "Game/AI/Action/actionGrabRight.h"

namespace uking::action {

GrabRight::GrabRight(const InitArg& arg) : Grab(arg) {}

void GrabRight::m32() {
    playAS("GrabRight", false, 0, 0, -1.0f);
}

}  // namespace uking::action
