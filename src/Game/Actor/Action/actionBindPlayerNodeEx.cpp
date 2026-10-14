#include "Game/Actor/Action/actionBindPlayerNodeEx.h"

namespace uking::action {

BindPlayerNodeEx::BindPlayerNodeEx(const InitArg& arg) : BindPlayerNodeBase(arg) {}

void BindPlayerNodeEx::m32() {
    playAS("Open", false, 0, 0, -1.0f);
}

}  // namespace uking::action
