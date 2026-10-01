#include "Game/AI/Action/actionThrowRight.h"

namespace uking::action {

ThrowRight::ThrowRight(const InitArg& arg) : Throw(arg) {}

void ThrowRight::m32() {
    playAS("ThrowRight", false, 0, 0, -1.0f);
}

}  // namespace uking::action
