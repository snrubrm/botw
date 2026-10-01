#include "Game/AI/Action/actionGrabLeft.h"

namespace uking::action {

GrabLeft::GrabLeft(const InitArg& arg) : Grab(arg) {}

void GrabLeft::m32() {
    playAS("GrabLeft", false, 0, 0, -1.0f);
}

}  // namespace uking::action
