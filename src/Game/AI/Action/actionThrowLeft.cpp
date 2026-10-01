#include "Game/AI/Action/actionThrowLeft.h"

namespace uking::action {

ThrowLeft::ThrowLeft(const InitArg& arg) : Throw(arg) {}

void ThrowLeft::m32() {
    playAS("ThrowLeft", false, 0, 0, -1.0f);
}

}  // namespace uking::action
